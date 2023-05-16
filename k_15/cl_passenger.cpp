#include "cl_passenger.h"

cl_passenger::cl_passenger(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(2);
}

void cl_passenger::signal_meth(string& s_message)
{
	
}

void cl_passenger::handler_meth(string s_message)
{
	
}

void cl_passenger::set_init_floor(int floor)
{
	i_initial_floor = floor;
}

void cl_passenger::set_dest_floor(int floor)
{
	i_destination_floor = floor;
}