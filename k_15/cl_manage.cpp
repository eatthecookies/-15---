#include "cl_manage.h"

cl_manage::cl_manage(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // ����������� ������ cl_2 �������� ����������� �������� ������
{
	set_object_class(4);
}

void cl_manage::signal_meth(string& s_message)
{
	
}

void cl_manage::handler_meth(string s_message)
{
}
