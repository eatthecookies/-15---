#include "cl_cab.h"

cl_cab::cl_cab(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(2);
}

void cl_cab::signal_meth(string& s_message)
{
}

int cl_cab::get_capacity()
{
	return i_capacity;
}

void cl_cab::signal_to_push_the_button_in_cab(string& s_message)
{

}

void cl_cab::change_capacity(string s_message)
{
	i_capacity = stoi(s_message);
}

