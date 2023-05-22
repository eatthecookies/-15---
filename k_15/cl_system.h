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
	int num_floors;
public:
	cl_system(cl_base* p_head_object);  // �����������
	int exec_app();						// ����� ������� ��������� ��������� ����������  		
	void build_tree_objects();			// ����� ���������� ������ �������� 

	void signal_to_read_command(string& s_message); 			// ����� ������ �������
	void signal_to_�hange_cab_capacity(string& s_message);
	void signal_to_push_the_button_in_cab(string& s_message);
	void handler(string s_message); 			// ����� �����������
	void signal_to_push_button_on_the_floor(string& s_message);
};


#endif
