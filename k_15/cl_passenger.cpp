#include "cl_passenger.h"

cl_passenger::cl_passenger(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(2);
}

int cl_passenger::get_destination_floor()
{
	return i_destination_floor;
}

// todo переделать на сигналы и обработчики

void cl_passenger::set_init_and_dest_floors(string s_message)
{
	stringstream ss(s_message);
	ss >> i_initial_floor >> i_destination_floor;
	cout << get_name() << " " << s_message;
}

// метод обработчика

void cl_passenger::button_on_the_floor_has_been_pushed(string s_message)
{	
}


