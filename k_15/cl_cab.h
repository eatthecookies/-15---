#ifndef __CL_CAB__H
#define __CL_CAB__H


#include "cl_base.h"

class cl_cab : public cl_base
{
	int i_capacity; 										// ����������� ������ �����
	
public:
	cl_cab(cl_base* p_head_object, string s_name = "cabin"); 	// ����������������� ����������� ������ cl_2
	void signal_meth(string& s_message); 						// ����� ������ �������
	
	void signal_to_push_the_button_in_cab(string& s_message);
	
	void change_capacity(string s_message);						// ���������� ������� ��� ��������� ����������� �����
	int get_capacity();
};

#endif
