#ifndef __CL_MANAGE__H
#define __CL_MANAGE__H

#include "cl_base.h"

class cl_manage : public cl_base
{
	// �� ��������� �������� i_state, ���� 2 - �� �� �����, ���� 3, ���� �� ����, ���� 4 - ���� ����, 1 - ��� �� �������
	vector <int> queue;
	int i_current_floor = 1;		// ����� �����, �� ������� ��������� ����
	int i_number_of_passengers = 0;
public:
	cl_manage(cl_base* p_head_object, string s_name = "manage"); // ����������������� ����������� ������ cl_2
	int get_current_floor();
	int get_num_passengers();
	void signal_meth(string& s_message); 			// ����� ������ �������
	void elevator_has_been_called(string s_message); 			// ����� �����������
};

#endif
