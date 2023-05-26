#ifndef __CL_MANAGE__H
#define __CL_MANAGE__H

#include "cl_base.h"
struct Call
{
	int floor; 
	int direction; // -1 1
};

class cl_manage : public cl_base
{
	// �� ��������� �������� i_state, ���� 2 - �� �� �����, ���� 3, ���� �� ����, ���� 4 - ���� ����, 1 - ��� �� �������
	int curr_direction = 1;
	int pointer = 0;
	
	int i_current_floor = 1;		// ����� �����, �� ������� ��������� ����
	int i_number_of_passengers = 0;
	
public:
	cl_manage(cl_base* p_head_object, string s_name = "manage"); // ����������������� ����������� ������ cl_2
	vector <int> queue;
	
	void get_current_floor(string s_message);
	void get_num_passengers(string s_message);
	void get_direction(string s_message);

	
	
	// ������ ��������						
	void signal_to_load_passengers(string& s_message);
	void signal_to_unload_passengers(string& s_message);
	void signal_to_system_handler(string& s_message);

	// ������ �����������
	void elevator_movement(string s_message);
	void button_in_the_cab_has_been_pushed(string s_message);
	void button_on_the_floor_has_been_pushed(string s_message);
	void button_on_the_floor_has_been_pushed_again(string s_message);
	void decrement_num_passengers(string s_message);
	void increment_num_passengers(string s_message);
};

#endif
