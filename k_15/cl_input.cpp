#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(2);
}

void cl_input::signal(string& s_message) 
{
}


void cl_input::read_command(string s_message)
{
	string s_command;
	getline(cin, s_command); // считать строку

	emit_signal(SIGNAL_D(cl_input::signal), s_command);	// отправить в обработчик системы
}

void cl_input::elevator_has_been_called(string s_message)
{
	
		
}
