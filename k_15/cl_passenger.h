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

	int i_pushed_button;
	int i_tact;
public:
	cl_passenger(cl_base* p_head_object, string s_name = "passenger"); // ����������������� ����������� ������ cl_2

	void get_destination_floor(string s_message);
	void set_init_and_dest_floors(string s_message);
	
	void button_on_the_floor_has_been_pushed(string s_message); 			// ����� �����������
	void signal_to_system_handler(string& s_message);
};

#endif
	