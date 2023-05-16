#include "cl_system.h"

cl_system::cl_system(cl_base* p_head_object) : cl_base(p_head_object) // конструктор класса cl_1 вызывает конструктор базового класса
{
	set_object_class(1);
};


int cl_system::exec_app()
{

	// Цикл для обработки вводимых команд
	while (true)
	{
		string command = "input";
		emit_signal(SIGNAL_D(cl_system::signal_meth), command);	// выдача сигнала объекту ввода для чтения

		if (current_command == "Turn off the system") // выключение системы
		{
			return 0;
		}
		else if ((int)current_command.find("Passenger condition") != -1)	// вывести состояние пассажира
		{
			command = command.substr(21);
		}
		else if ((int)current_command.find("Passenger") != -1)				// команда вызова лифта
		{			
			current_command = current_command.substr(10);					// удаление несмысловой части

			stringstream ss(current_command);								// создание потока на основе команды
			string f, io;
			int i_initial_floor, i_destination_floor;

			ss >> i_initial_floor >> i_destination_floor >> f >> io;		// разбиение строки на данные

			string floor = "/floor_" + to_string(i_initial_floor);

			cl_base* pass_obj = new cl_passenger(get_object_pointer(floor));
			pass_obj->set_name(f + " " + io);
			pass_obj->set_state(1);
			 
		}
		else if ((int)current_command.find("Elevator condition") != -1)		// вывести состояние в кабине лифта
		{
			;
		}
		else if ((int)current_command.find("Condition on the floor") != -1)	// вывести состояние на этаже
		{
			;
		}
		else if (current_command == "System condition")						// вывести состояние системы
		{
			;
		}
		else if (current_command == "SHOWTREE")								// показать дерево иерархии объектов
		{
			print_tree_with_rns(0);
			return 0;
		}
	}
	return 0;
}


void cl_system::build_tree_objects()
{
	// -----------------------------------
	// Построение дерева иерархии объектов
	// -----------------------------------

	this->set_name("systemObject");				// установление именя systemObject для корневого объекта

	cl_base* ob_input = new cl_input(this);		// создание объекта ввода
	cl_base* ob_manage = new cl_manage(this);	// создание объекта управления кабиной
	cl_base* ob_cabin = new cl_cab(ob_manage);	// создание объекта кабины лифта
	cl_base* ob_output = new cl_output(this);	// создание объекта вывода

	set_all_state_on();							// включение всех объектов


	set_connection(SIGNAL_D(cl_system::signal_meth), ob_cabin, HANDLER_D(cl_cab::handler_meth));		// система -> кабина
	set_connection(SIGNAL_D(cl_system::signal_meth), ob_input, HANDLER_D(cl_input::handler_meth));		// система -> ввод
	ob_input->set_connection(SIGNAL_D(cl_input::signal_meth), this, HANDLER_D(cl_system::handler_meth));// ввод -> система

	string command = "startInput";
	emit_signal(SIGNAL_D(cl_system::signal_meth), command);	// выдача сигнала объекту ввода для чтения
	
	stringstream ss(current_command);
	int num_floors, capacity;

	ss >> num_floors >> capacity;

	command = "capacity: " + to_string(capacity);// изменение вместимости кабины лифта
	
	emit_signal(SIGNAL_D(cl_system::signal_meth), command);

	// создание объектов этажей
	for (int i = 0; i < num_floors; i++)
	{
		
		string name = "floor_" + to_string(i + 1);
		cl_base* obj = new cl_floor(this, name);
		obj->set_state(1);
		// Установка связей сигналов и обработчиков с новым объектом ???
	}
		
	//1.3.Установка связей сигналов и обработчиков между объектами
	


}


void cl_system::signal_meth(string& s_message)
{
}

void cl_system::handler_meth(string s_message)
{
	current_command = s_message;
}


