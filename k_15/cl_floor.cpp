#include "cl_floor.h"

cl_floor::cl_floor(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(3);
}

void cl_floor::signal_meth(string& s_message)
{
}

void cl_floor::button_has_pushed(string s_message)
{
	int direction, i_init_floor;
	stringstream ss(s_message);
	
	cl_base* p_manage = get_object_pointer("/manage");

	ss >> i_init_floor >> direction;
	string command;


	//todo сделать связь этаж -> менеджер кабины
	
	// достаточно просто вызвать сигнал и все
	emit_signal(SIGNAL_D(signal_to_call_elevator), s_message);
}

void cl_floor::signal_to_call_elevator(string& s_message)
{
}