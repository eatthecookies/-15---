#include "cl_manage.h"

cl_manage::cl_manage(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(4);
}

void cl_manage::signal_meth(string& s_message)
{
	
}

void cl_manage::elevator_has_been_called(string s_message)
{
	int direction, i_init_floor;
	stringstream ss(s_message);

	cl_base* p_manage = get_object_pointer("/manage");

	ss >> i_init_floor >> direction;
	string command;

	
}



int cl_manage::get_num_passengers()
{
	return i_number_of_passengers;
}

int cl_manage::get_current_floor()
{
	return i_current_floor;
}