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
	int curr_direction;
	int past_direction;
	int pointer = 0;
	vector <int> last_added_ind;
	int i_current_floor = 1;		// ����� �����, �� ������� ��������� ����
	int i_number_of_passengers = 0;
public:
	cl_manage(cl_base* p_head_object, string s_name = "manage"); // ����������������� ����������� ������ cl_2
	
	vector <int> queue1;
	vector <Call> queue;
	int get_current_floor();
	int get_num_passengers();
	int get_direction();

	void decrement_num_passengers();
	void increment_num_passengers();
	
	void moving();
	void stop();
	
	void signal_meth(string& s_message); 						// ����� ������ �������
	void signal_to_load_passengers(string& s_message);
	void signal_to_unload_passengers(string& s_message);

	void button_in_the_cab_has_been_pushed(string s_message);
	void button_on_the_floor_has_been_pushed(string s_message); 			// ����� �����������
};

#endif
