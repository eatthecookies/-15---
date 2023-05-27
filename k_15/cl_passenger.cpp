#include "cl_passenger.h"

cl_passenger::cl_passenger(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
}

// методы обработчики

void cl_passenger::get_destination_floor(string s_message)
{
	string command = to_string(i_destination_floor);
	emit_signal(SIGNAL_D(cl_passenger::signal_to_system_handler), command);
}


void cl_passenger::set_init_and_dest_floors(string s_message)
{
	stringstream ss(s_message);
	ss >> i_initial_floor >> i_destination_floor;
}



void cl_passenger::button_on_the_floor_has_been_pushed(string s_message)
{	
}

// методы сигналы

void cl_passenger::signal_to_system_handler(string& s_message)
{
}