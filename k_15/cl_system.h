#ifndef __CL_SYSTEM__H
#define __CL_SYSTEM__H
#include "cl_base.h"
#include "cl_system.h"
#include "cl_manage.h"
#include "cl_cab.h"
#include "cl_passenger.h"
#include "cl_output.h"
#include "cl_floor.h"
#include "cl_input.h"

class cl_system : public cl_base
{
	string current_command;				// ������� �������
public:
	cl_system(cl_base* p_head_object);  // �����������
	int exec_app();						// ����� ������� ��������� ��������� ����������  		
	void build_tree_objects();			// ����� ���������� ������ �������� 

	void signal_meth(string& s_message); 			// ����� ������ �������
	void handler_meth(string s_message); 			// ����� �����������
};


#endif
