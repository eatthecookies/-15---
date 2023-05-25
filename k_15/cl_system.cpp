#include "cl_system.h"


// сделать поле указателя для очережи
// не удалять этаж при приезде на него
// не добавлять этаж если он уже есть в очереди и если направление сохраняется


cl_system::cl_system(cl_base* p_head_object) : cl_base(p_head_object) // конструктор класса cl_1 вызывает конструктор базового класса
{
	set_object_class(1);
};

void cl_system::build_tree_objects()
{
	// -----------------------------------
	// Построение дерева иерархии объектов
	// -----------------------------------

	this->set_name("system");					// установление имени systemObject для корневого объекта

	//! ============ Создание объектов ==============
	cl_base* ob_input = new cl_input(this);		// создание объекта ввода
	cl_base* ob_manage = new cl_manage(this);	// создание объекта управления кабиной
	cl_base* ob_cabin = new cl_cab(ob_manage);	// создание объекта кабины лифта
	cl_base* ob_output = new cl_output(this);	// создание объекта вывода
	//!=============================================

	set_all_state_on();							// включение всех объектов

	set_connection(SIGNAL_D(cl_system::signal_to_сhange_cab_capacity), ob_cabin, HANDLER_D(cl_cab::change_capacity));		// система -> кабина
	
	// соединения для объекта ввода
	set_connection(SIGNAL_D(cl_system::signal_to_read_command), ob_input, HANDLER_D(cl_input::read_command));				// система -> ввод комманд
	ob_input->set_connection(SIGNAL_D(cl_input::signal), this, HANDLER_D(cl_system::handler));								// ввод -> система
	
	string command = "";

	//!=============== Цикл для обработки вводимых данных ================================
	while (true)
	{
		emit_signal(SIGNAL_D(cl_system::signal_to_read_command), command);
		if (current_command == "End of settings")
			break;

		stringstream ss(current_command);		// создание потока для переменной команды
		int capacity;							// составляющие команды
		ss >> num_floors >> capacity;			// присвоение данных к переменным
		command = to_string(capacity);			// изменение вместимости кабины лифта

		emit_signal(SIGNAL_D(cl_system::signal_to_сhange_cab_capacity), command);

		//!============ Создание объектов этажей =============================
		for (int i = 0; i < num_floors; i++)
		{
			string name = "floor_" + to_string(i + 1);	// формирование имени для объекта лифта
			cl_base* p_floor = new cl_floor(this, name);	// создание объекта лифта
			p_floor->set_state(1);							// включение нового объекта

			//этаж -> менеджер кабины
			p_floor->set_connection(SIGNAL_D(cl_floor::signal_to_call_elevator), ob_manage, HANDLER_D(cl_manage::button_on_the_floor_has_been_pushed));
		}
	}
	
	//! ========================= Установка соединений ===================================
	//todo Установка связей сигналов и обработчиков между объектами
	
	// менеджер кабины -> загрузить пассажиров
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_load_passengers), this, HANDLER_D(cl_system::load_passengers));
	
	// менеджер кабины -> выгрузить пассажиров
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_unload_passengers), this, HANDLER_D(cl_system::unload_passengers));
	
	// установить связь кабина -> управление  для нажатий кнопок
	ob_cabin ->set_connection(SIGNAL_D(cl_cab::signal_to_push_the_button_in_cab), ob_manage, HANDLER_D(cl_manage::button_in_the_cab_has_been_pushed));
	
	cout << "Ready to work";
}

int cl_system::exec_app()
{
	int i_tact = 1;

	//! ======================== Цикл для обработки вводимых команд =======================
	while (true)
	{
		// выдача сигнала объекту ввода для чтения
		string command = "";
		emit_signal(SIGNAL_D(cl_system::signal_to_read_command), command);	

		// отработка команды
		if (current_command == "Turn off the system") // выключение системы
		{
			return 0;
		}
		else if ((int)current_command.find("Passenger condition") != -1)	// вывести состояние пассажира
		{
			string fio = current_command.substr(20);	// удаление "passenger condition"

			cl_passenger* p_passenger = (cl_passenger*)find_object_from_root(fio);
			
			if (p_passenger == nullptr)
			{
				cout << "\nPassenger " << fio << " not found";
			}
			else if (p_passenger->get_state() == 1)
			{
				int floor = p_passenger->get_current_floor();;

				cout << "\nPassenger condition: " << fio << " on the floor " << floor;
			}
			else if (p_passenger->get_state() == 2)
			{
				cout << "\nPassenger condition: " << fio << " in the elevator";
			}

		}
		else if ((int)current_command.find("Passenger") != -1)				// команда вызова лифта (подхода пассажира)
		{
			current_command = current_command.substr(10);					// удаление несмысловой части

			stringstream ss(current_command);								// создание потока на основе команды
			string f, io;
			int i_initial_floor, i_destination_floor;

			ss >> i_initial_floor >> i_destination_floor >> f >> io;		// разбиение строки на данные

			string floor = "/floor_" + to_string(i_initial_floor);			// формирование пути к объекту этажа

			cl_base* p_floor = get_object_pointer(floor);			// указатель на объект этажа, на котором стоит пассажир
			cl_passenger* pass_obj = new cl_passenger(p_floor);		// создание объекта пассажира с головным этажем
			
			pass_obj->set_name(f + " " + io);						// переименование пасажира 
			
			if (i_initial_floor < i_destination_floor)			// включение объекта пассажира 1, давая понять, что он на этаже
				pass_obj->set_state(1);									
			else
				pass_obj->set_state(2);

			pass_obj->set_dest_floor(i_destination_floor);			// установка целевого этажа
			pass_obj->set_init_floor(i_initial_floor);				// установка начального этажа

			string command = to_string(i_initial_floor) + " " + to_string(pass_obj->get_state()); // формирование сигнала для этажа
			// на каком этаже сейчас и куда хочет ехать вверх или вниз

			// нажали на кнопку на этаже
			p_floor-> emit_signal(SIGNAL_D(cl_floor::signal_to_call_elevator), command);

		}
		else if ((int)current_command.find("Elevator condition") != -1)		// вывести состояние в кабине лифта
		{
			cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
			int curr_direction = p_manage->get_direction();
			int floor = p_manage->get_current_floor();	// номер текущего этажа лифта
			int num_pass = p_manage->get_num_passengers();

			if (curr_direction == 0)		// стоит на этаже 
			{
				cout << "\nElevator condition: " << floor << " " << num_pass << " stop";
			}
			else if (curr_direction == 1)	// едет вверх
			{
				cout << "\nElevator condition: " << floor << " " << num_pass << " direction up";
			}
			else if (curr_direction == -1)	// едет вниз
			{
				cout << "\nElevator condition: " << floor << " " << num_pass << " direction down";
			}

		}
		else if ((int)current_command.find("Condition on the floor") != -1)	// вывести состояние на этаже
		{
			current_command = current_command.substr(23);					// удаление несмысловой части
			cl_base* p_floor = get_object_pointer("/floor_" + current_command);
			
			int floor = stoi(current_command);

			cout << "\nCondition on the floor " << floor << " -up-";
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 2)
					cout << " " << p_pass->get_name();
			cout << "\nCondition on the floor " << floor << " -down-";
			
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 3)
					cout << " " << p_pass->get_name();
		}
		else if (current_command == "System status")						// вывести состояние системы
		{
			int up, down;
			cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
			
			int floor = p_manage->get_current_floor();						// номер текущего этажа лифта
			int num_pass = p_manage->get_num_passengers();

			cout << i_tact << ": Elevator: " << floor << " " << num_pass << " Floors:";
			for (int i = 1; i <= num_floors; i++)
			{
				cl_base* p_floor = get_object_pointer("/floor_" + to_string(i));
				
				up = 0; down = 0;
				for (auto p_pass : p_floor->get_sub_objects())
					if (p_pass->get_state() == 1)
						up++;
				for (auto p_pass : p_floor->get_sub_objects())
					if (p_pass->get_state() == 2)
						down++;
				if ((up + down) != 0)
					cout << " (" << i << ": " << up << "-" << down << ")";
			}
			
			cout << " (";
			for (auto p : p_manage->queue1)
			{
				cout << p << "  ";
			}
			cout << ")" << endl;

		}
		else if (current_command == "SHOWTREE")								// показать дерево иерархии объектов
		{
			print_tree_with_rns(0);
			return 0;
		}

		int up, down;
		cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");

		int floor = p_manage->get_current_floor();						// номер текущего этажа лифта
		int num_pass = p_manage->get_num_passengers();

		cout << i_tact << ": Elevator: " << floor << " " << num_pass << " Floors:";
		for (int i = 1; i <= num_floors; i++)
		{
			cl_base* p_floor = get_object_pointer("/floor_" + to_string(i));

			up = 0; down = 0;
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 1)
					up++;
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 2)
					down++;
			if ((up + down) != 0)
				cout << " (" << i << ": " << up << "-" << down << ")";
		}

		cout << " (";
		for (auto p : p_manage->queue)
		{
			cout << p.floor << "  ";
		}
		cout << ")" ;


		i_tact++;
		
		// Отработка действий согласно такту
		//cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
		p_manage->moving();
	}

	return 0;
}

void cl_system::signal_to_read_command(string& s_message)
{
}

void cl_system::signal_to_сhange_cab_capacity(string& s_message)
{
}

void cl_system::signal_to_push_the_button_in_cab(string& s_message)
{
}

void cl_system::handler(string s_message)
{
	current_command = s_message;
}


void cl_system::signal_to_push_button_on_the_floor(string& s_message)
{
}

void cl_system::load_passengers(string s_message)
{
	string command;
	cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
	int curr_floor = p_manage->get_current_floor();

	cl_base* p_floor = get_object_pointer("/floor_" + to_string(curr_floor));
	cl_cab* p_cab = (cl_cab*) get_object_pointer("/manage/cabin");

	if (p_manage->get_num_passengers() == p_cab->get_capacity())
		return;

	for (int i = 0; i < p_floor->get_sub_objects().size(); i++)
	{

		cl_passenger* p_pass = (cl_passenger*)p_floor->get_sub_objects()[i];
		command = to_string(p_pass->get_destination_floor()) + " " + to_string(p_pass->get_state());
		
		p_pass->change_head_object(p_cab);
		p_manage->increment_num_passengers();
		
		// нажать кнопку в лифте
		p_cab->emit_signal(SIGNAL_D(cl_cab::signal_to_push_the_button_in_cab), command);
		
		
	}

}

void cl_system::unload_passengers(string s_message)
{
	cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
	int curr_floor = p_manage->get_current_floor();
	
	cl_base* p_floor = get_object_pointer("/floor_" + to_string(curr_floor));
	cl_base* p_cab = get_object_pointer("/manage/cabin");

	for (int i = 0; i < p_cab->get_sub_objects().size(); i++)
	{
		cl_passenger* p_pass = (cl_passenger*) p_cab->get_sub_objects()[i];
		
		if (p_pass->get_destination_floor() == curr_floor)
		{
			p_cab->delete_sub_object(p_pass->get_name());
			p_manage->decrement_num_passengers();
		}
	}

}
