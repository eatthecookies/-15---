#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(2);
}

void cl_input::signal_meth(string& s_message)
{
}

void cl_input::handler_meth(string s_message)
{
	if (s_message == "startInput")
	{
		string s_command = "", inp;
		getline(cin, s_command);
		cin.ignore();
		emit_signal(SIGNAL_D(cl_input::signal_meth), s_command);
	}

	if(s_message == "input")
	{
		string s_command;
		getline(cin, s_command);

		emit_signal(SIGNAL_D(cl_input::signal_meth), s_command);
	}
		
}
