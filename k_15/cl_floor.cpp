#include "cl_floor.h"

cl_floor::cl_floor(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // ����������� ������ cl_2 �������� ����������� �������� ������
{
	set_object_class(3);
}

void cl_floor::signal_meth(string& s_message)
{
}

void cl_floor::handler_meth(string s_message)
{
}
