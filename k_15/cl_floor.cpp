#include "cl_floor.h"

cl_floor::cl_floor(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // ����������� ������ cl_2 �������� ����������� �������� ������
{
}

// ������ �������

void cl_floor::signal_to_call_elevator(string& s_message)
{
}

void cl_floor::signal_to_push_the_button_on_the_floor_again(string& s_message)
{
}

// ������ ������������

void cl_floor::button_on_the_floor_has_been_pushed(string s_message)
{
}

void cl_floor::button_has_pushed_on_the_floor(string s_message)
{
	emit_signal(SIGNAL_D(cl_floor::signal_to_call_elevator), s_message);	// ������ ������� ����� ���������� ����� ��� ����������� � ������ �� �����
}