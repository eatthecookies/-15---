#include "cl_system.h"

cl_system::cl_system(cl_base* p_head_object) : cl_base(p_head_object) // конструктор класса cl_1 вызывает конструктор базового класса
{
};

void cl_system::build_tree_objects()
{
	this->set_name("system");					// установление имени systemObject для корневого объекта

	// Создание объектов 
	cl_base* ob_input = new cl_input(this);		// создание объекта ввода
	cl_base* ob_manage = new cl_manage(this);	// создание объекта управления кабиной
	cl_base* ob_cabin = new cl_cab(ob_manage);	// создание объекта кабины лифта
	cl_base* ob_output = new cl_output(this);	// создание объекта вывода
	set_all_state_on();							// включение всех объектов
	
	// установка связи система -> изменить вместимость кабины лифта
	set_connection(SIGNAL_D(cl_system::signal_to_сhange_cab_capacity), ob_cabin, HANDLER_D(cl_cab::change_capacity));
	
	// установка связи система -> объект ввода комманд
	set_connection(SIGNAL_D(cl_system::signal_to_read_command), ob_input, HANDLER_D(cl_input::read_command));				
	
	// установка связи объект ввода -> система
	ob_input->set_connection(SIGNAL_D(cl_input::signal), this, HANDLER_D(cl_system::handler));								
	
	string command = "";

	// Цикл для обработки вводимых данных 
	while (true)
	{
		emit_signal(SIGNAL_D(cl_system::signal_to_read_command), command);
		if (current_command == "End of settings")
			break;

		stringstream ss(current_command);		// создание строкового потока для команды
		int capacity;							// переменные в которые осуществляется запись
		ss >> num_floors >> capacity;			// присвоение значений данных переменной и полю
		command = to_string(capacity);			// команда для изменения вместимости кабины лифта

		// выдача сигнала на изменение вместимости кабины лифта
		emit_signal(SIGNAL_D(cl_system::signal_to_сhange_cab_capacity), command);	

		// Создание объектов этажей
		for (int i = 0; i < num_floors; i++)
		{
			string name = "floor_" + to_string(i + 1);		// формирование имени для объекта лифта
			cl_base* p_floor = new cl_floor(this, name);	// создание объекта лифта
			p_floor->set_state(1);							// включение нового объекта

			// установка связи менеджер кабины -> загрузить пассажиров
			p_floor->set_connection(SIGNAL_D(cl_floor::signal_to_call_elevator), ob_manage, HANDLER_D(cl_manage::button_on_the_floor_has_been_pushed));
			// установка связи менеджер кабины -> загрузить пассажиров
			p_floor->set_connection(SIGNAL_D(cl_floor::signal_to_push_the_button_on_the_floor_again), ob_manage, HANDLER_D(cl_manage::button_on_the_floor_has_been_pushed_again));
		}
	}
	
	// установка связи менеджер кабины -> система загрузить пассажиров
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_load_passengers), this, HANDLER_D(cl_system::load_passengers));
	
	// установка связи менеджер кабины -> система выгрузить пассажиров
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_unload_passengers), this, HANDLER_D(cl_system::unload_passengers));
	
	// установка связи менеджер кабины -> система 
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_system_handler), this, HANDLER_D(cl_system::handler));

	// установка связи менеджер кабины -> система 
	ob_cabin->set_connection(SIGNAL_D(cl_cab::signal_to_system_handler), this, HANDLER_D(cl_system::handler));
	
	// установка связи кабина -> управление  для нажатий кнопок
	ob_cabin ->set_connection(SIGNAL_D(cl_cab::signal_to_push_the_button_in_cab), ob_manage, HANDLER_D(cl_manage::button_in_the_cab_has_been_pushed));
	
	// установить связь система -> вывод
	set_connection(SIGNAL_D(cl_system::signal_to_output), ob_manage, HANDLER_D(cl_output::console_output));

	// установить связь система -> объект управления кабиной лифта для движения
	set_connection(SIGNAL_D(cl_system::signal_for_elevator_movement), ob_manage, HANDLER_D(cl_manage::elevator_movement));

	// установить связь система -> объект управления кабиной лифта для увеличения количества пассажиров
	set_connection(SIGNAL_D(cl_system::signal_to_increment_num_passengers), ob_manage, HANDLER_D(cl_manage::increment_num_passengers));
	
	// установить связь система -> объект управления кабиной лифта для уменьшения количества пассажиров
	set_connection(SIGNAL_D(cl_system::signal_to_decrement_num_passengers), ob_manage, HANDLER_D(cl_manage::decrement_num_passengers));

	// установить связь система -> объект управления кабиной лифта для уменьшения количества пассажиров
	set_connection(SIGNAL_D(cl_system::signal_to_get_current_floor), ob_manage, HANDLER_D(cl_manage::get_current_floor));

	// установить связь система -> объект управления кабиной лифта для уменьшения количества пассажиров
	set_connection(SIGNAL_D(cl_system::signal_to_get_num_passengers), ob_manage, HANDLER_D(cl_manage::get_num_passengers));

	// установить связь система -> объект управления кабиной лифта для получения направления движения
	set_connection(SIGNAL_D(cl_system::signal_to_get_direction), ob_manage, HANDLER_D(cl_manage::get_direction));
	
	// установить связь система -> объект управления кабиной лифта для получения вместимости
	set_connection(SIGNAL_D(cl_system::signal_to_get_capacity), ob_cabin, HANDLER_D(cl_cab::get_capacity));

	command = "Ready to work";
	
	// выдача сигнала объекту вывода для вывода сообщения  command
	emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
}


int cl_system::exec_app()
{
	int i_tact = 1;	// переменная для хранения тактов

	// Цикл для обработки вводимых команд 
	while (true)
	{
		// выдача сигнала объекту ввода для чтения
		string command = "";
		emit_signal(SIGNAL_D(cl_system::signal_to_read_command), command);	

		// отработка команды
		if (current_command == "Turn off the system")						// команда на выключение системы
		{
			command = "Turn off the system";								// формирование команды на вывод
			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);	// подача сигнала на объект вывода
			return 0;
		}
		else if ((int)current_command.find("Passenger condition") != -1)				// команда вывода состояния пассажира
		{
			string output;																// объявление переменной output для хранения результата вывода
			string fio = current_command.substr(20);									// удаление из строки подстроки "passenger condition"

			cl_passenger* p_passenger = (cl_passenger*)find_object_from_root(fio);
			
			if (p_passenger == nullptr)													// проверка, если указатель p_passenger равен nullptr (такого пассажира нет)
			{
				output = "Passenger " + fio  + " not found";							// формирование сообщения об ошибке
				emit_signal(SIGNAL_D(cl_system::signal_to_output), output);
			}
			else if (p_passenger->get_state() == 1 or p_passenger->get_state() == 2)	// проверка состояния пассажира на этаже
			{
				string floor = (p_passenger->get_head()->get_name()).substr(6);			// извлечение подстроки с номером этажа
				output = "Passenger condition: " + fio + " on the floor " + floor;		// формирование сообщения о состоянии пассажира и этаже, на котором он находится
				emit_signal(SIGNAL_D(cl_system::signal_to_output), output);
			}

			else if (p_passenger->get_state() == 3 or p_passenger->get_state() == 4)	// проверка состояния пассажира в лифте
			{
				output = "Passenger condition: " + fio + " in the elevator";			// формирование сообщения о состоянии пассажира в лифте
				emit_signal(SIGNAL_D(cl_system::signal_to_output), output);
			}
		}
		else if ((int)current_command.find("Passenger") != -1)			// команда вызова лифта (подхода пассажира)
		{
			current_command = current_command.substr(10);				// удаление несмысловой части
			
			stringstream ss(current_command);							// создание потока на основе команды
			string f, io;												// переменные в которые осуществляется запись
			int i_initial_floor, i_destination_floor;
			ss >> i_initial_floor >> i_destination_floor >> f >> io;	// разбиение строки на данные и запись в переменнве
			
			string floor = "/floor_" + to_string(i_initial_floor);		// формирование пути к объекту этажа
			cl_base* p_floor = get_object_pointer(floor);				// получение указателя на объект этажа, на котором будет стоять пассажир
			cl_passenger* pass_obj = new cl_passenger(p_floor);			// создание объекта пассажира с головным объектом этажем
			
			pass_obj->set_name(f + " " + io);							// задание фио пасажира 
			
			if (i_initial_floor < i_destination_floor)					// изменение со стояния объекта в зависимости и от желаемого направления движения
				pass_obj->set_state(1);									// вверх
			else
				pass_obj->set_state(2);									// вниз

			// установка соединения объект пассажир -> система
			set_connection(SIGNAL_D(cl_system::signal_to_set_init_dest_floor), pass_obj, HANDLER_D(cl_passenger::set_init_and_dest_floors));

			command = to_string(i_initial_floor) + " " + to_string(i_destination_floor);	// команда для установки начального и целевого этажа
			emit_signal(SIGNAL_D(cl_system::signal_to_set_init_dest_floor), command);		// выдача сигнала для установки начального и целового этажа

			command = to_string(i_initial_floor) + " " + to_string(pass_obj->get_state());	// формирование сигнала для нажатия кнопеи на этаже (на каком этаже сейчас и направление)
			
			// todo переделать на сигнал и обработчик!
			p_floor->emit_signal(SIGNAL_D(cl_floor::signal_to_call_elevator), command);		// нажатие кнопки на этаже
			
			// удаление соединения объекта и пассажира
			delete_connection(SIGNAL_D(cl_system::signal_to_set_init_dest_floor), pass_obj, HANDLER_D(cl_passenger::set_init_and_dest_floors));
		}
		else if ((int)current_command.find("Elevator condition") != -1)			// вывести состояние в кабине лифта
		{
			cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");	// получение указателя на объект управления кабиной
			
			int curr_direction = p_manage->get_state();
			
			emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
			string floor = current_command;							// номер текущего этажа лифта
			
			emit_signal(SIGNAL_D(cl_system::signal_to_get_num_passengers), command);
			string num_pass = current_command;

			if (curr_direction == 3)		// стоит на этаже 
			{
				command = "Elevator condition: " + floor + " " + num_pass + " stop";
				emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			}
			else if (curr_direction == 1)	// едет вверх
			{
				command = "Elevator condition: " + floor + " " + num_pass + " direction up";
				emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			}
			else if (curr_direction == 2)	// едет вниз
			{
				command = "Elevator condition: " + floor + " " + num_pass + " direction down";
				emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			}

		}
		else if ((int)current_command.find("Condition on the floor") != -1)	// вывести состояние на этаже
		{
			current_command = current_command.substr(23);					// удаление несмысловой части
			cl_base* p_floor = get_object_pointer("/floor_" + current_command);
			
			int floor = stoi(current_command);

			command = "Condition on the floor " + to_string(floor) + " -up-";
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 1)
					command += " " + p_pass->get_name();

			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			
			command = "Condition on the floor " + to_string(floor) + " -down-";
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 2)
					command += " " + p_pass->get_name();
			
			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
		}
		else if (current_command == "System status")						// вывести состояние системы
		{
			int up, down;
			cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
			
			emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
			string floor = current_command;							// номер текущего этажа лифта

			emit_signal(SIGNAL_D(cl_system::signal_to_get_num_passengers), command);
			string num_pass = current_command;

			command = to_string(i_tact) + ": Elevator: " + floor + " " + num_pass + " Floors:";
			
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
					command += " (" + to_string(i) + ": " + to_string(up) + "-" + to_string(down) + ")";
			}

			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
		}
		else if (current_command == "SHOWTREE")								// показать дерево иерархии объектов
		{
			print_tree_with_rns(0);
			return 0;
		}

		i_tact++; // переход на новый такт
		
		// подача сигнала объекту управления кабиной для движения лифта
		emit_signal(SIGNAL_D(cl_system::signal_for_elevator_movement), command);
	}

	return 0;
}


// методы обработчики

void cl_system::load_passengers(string s_message)
{
	string command;
	cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");									// получение указателя на объект управления кабиной
	
	emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
	string curr_floor = current_command;

	emit_signal(SIGNAL_D(cl_system::signal_to_get_capacity), command);
	int capacity = stoi(current_command);

	emit_signal(SIGNAL_D(cl_system::signal_to_get_num_passengers), command);
	int num_passengers = stoi(current_command);
	
	cl_base* p_floor = get_object_pointer("/floor_" + curr_floor);
	cl_cab* p_cab = (cl_cab*) get_object_pointer("/manage/cabin");

	int n = p_floor->get_sub_objects().size();

	for (int i = 0; i < n; i++)
	{
		cl_passenger* p_pass = (cl_passenger*)p_floor->get_sub_objects()[0];
		
		if (num_passengers == capacity)
		{
			// todo переделать на сигнал и обработчик!
			p_floor->emit_signal(SIGNAL_D(cl_floor::signal_to_push_the_button_on_the_floor_again), curr_floor);
			return;
		}
		else
		{
			command = to_string(p_pass->get_destination_floor()) + " " + to_string(p_pass->get_state());
			p_pass->change_head_object(p_cab);

			emit_signal(SIGNAL_D(cl_system::signal_to_increment_num_passengers), command);

			// todo переделать на сигнал и обработчик!
			// нажать кнопку в лифте
			p_cab->emit_signal(SIGNAL_D(cl_cab::signal_to_push_the_button_in_cab), command);
		}	
	}
}

void cl_system::unload_passengers(string s_message)
{
	string command = "";
	cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");			// получение указателя на объект управления кабиной
	
	emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
	
	cl_base* p_floor = get_object_pointer("/floor_" + current_command);
	cl_base* p_cab = get_object_pointer("/manage/cabin");
	
	int n = p_cab->get_sub_objects().size();
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		cl_passenger* p_pass = (cl_passenger*)p_cab->get_sub_objects()[j];
		
		if (p_pass->get_destination_floor() == stoi(current_command))
		{
			p_cab->delete_sub_object(p_pass->get_name());
			emit_signal(SIGNAL_D(cl_system::signal_to_decrement_num_passengers), command);
		}
		else j++;
	}
}

void cl_system::handler(string s_message)
{
	current_command = s_message;
}

// методы сигналы

void cl_system::signal_to_read_command(string& s_message)
{
}

void cl_system::signal_to_сhange_cab_capacity(string& s_message)
{
}

void cl_system::signal_to_push_the_button_in_cab(string& s_message)
{
}

void cl_system::signal_to_push_button_on_the_floor(string& s_message)
{
}

void cl_system::signal_to_output(string& s_message)
{
}

void cl_system::signal_to_set_init_dest_floor(string& s_message)
{
}

void cl_system::signal_for_elevator_movement(string& s_message)
{
}

void cl_system::signal_to_increment_num_passengers(string& s_message)
{
}

void cl_system::signal_to_decrement_num_passengers(string& s_message)
{
}

void cl_system::signal_to_get_current_floor(string& s_message)
{
}

void cl_system::signal_to_get_num_passengers(string& s_message)
{
}

void cl_system::signal_to_get_direction(string& s_message)
{
}

void cl_system::signal_to_get_capacity(string& s_message)
{
}