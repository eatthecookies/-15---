#include "cl_output.h"

cl_output::cl_output(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(2);
}

void cl_output::signal_meth(string& s_message)
{
	
}

void cl_output::button_on_the_floor_has_been_pushed(string s_message)
{
}
