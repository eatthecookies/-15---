#ifndef __CL_MANAGE__H
#define __CL_MANAGE__H

#include "cl_base.h"

class cl_manage : public cl_base
{
	int i_current_floor;			// ����� �����, �� ������� ��������� ����
	string s_current_direction;		// ����������� �������� �����

public:
	cl_manage(cl_base* p_head_object, string s_name = "manageObject"); // ����������������� ����������� ������ cl_2

	void signal_meth(string& s_message); 			// ����� ������ �������
	void handler_meth(string s_message); 			// ����� �����������
};

#endif
