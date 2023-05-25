#include "cl_floor.h"

cl_floor::cl_floor(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(3);
}

// методы сигнала

void cl_floor::signal_to_call_elevator(string& s_message)
{
}

void cl_floor::signal_to_push_the_button_on_the_floor_again(string& s_message)
{
}

// методы обработчикии

void cl_floor::button_on_the_floor_has_been_pushed(string s_message)
{
}

void cl_floor::button_has_pushed_on_the_floor(string s_message)
{
	int curr_direction, i_init_floor;
	cl_base* p_manage = get_object_pointer("/manage");

	stringstream ss(s_message);
	ss >> i_init_floor >> curr_direction;
	string command;

	emit_signal(SIGNAL_D(cl_floor::signal_to_call_elevator), s_message);
}