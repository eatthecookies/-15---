#ifndef __CL_PASSENGER__H
#define __CL_PASSENGER__H



#include "cl_base.h"

class cl_passenger : public cl_base
{
	int i_initial_floor;  		// ����� ��������� �����
	int i_destination_floor; 	// ����� �������� �����
	// �� ��������� �������� i_state, 1 - �� ����� � ����� �� ����
	//							  2 - �� ����� � ����� ����
	//							  3 - � ����� ������
	//							  4 - � ����� ����1

	int i_current_floor;

	int i_pushed_button;
	int i_tact;
public:
	cl_passenger(cl_base* p_head_object, string s_name = "passenger"); // ����������������� ����������� ������ cl_2

	int get_current_floor();

	void set_dest_floor(int);
	void set_init_floor(int);

	void signal_meth(string& s_message); 			// ����� ������ �������
	void elevator_has_been_called(string s_message); 			// ����� �����������
};

#endif
	