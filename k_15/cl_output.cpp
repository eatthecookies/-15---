#include "cl_output.h"

cl_output::cl_output(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // ����������� ������ cl_2 �������� ����������� �������� ������
{
}

// ����� ����������

void cl_output::console_output(string s_message)
{
	cout << s_message;
}
