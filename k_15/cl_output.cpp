#include "cl_output.h"

cl_output::cl_output(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // ����������� ������ cl_2 �������� ����������� �������� ������
{
	set_object_class(2);
}

void cl_output::signal_meth(string& s_message)
{
	
}

void cl_output::handler_meth(string s_message)
{
}
