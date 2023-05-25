#ifndef __CL_FLOOR__H
#define __CL_FLOOR__H


#include "cl_base.h"

class cl_floor : public cl_base
{
public:
	cl_floor(cl_base* p_head_object, string s_name = "floor"); // ����������������� ����������� ������ cl_2

	void signal_to_call_elevator(string& s_message);
	void signal_to_push_the_button_on_the_floor_again(string& s_message);

	void button_has_pushed_on_the_floor(string s_message);
	void button_on_the_floor_has_been_pushed(string s_message); 			// ����� �����������
};

#endif
