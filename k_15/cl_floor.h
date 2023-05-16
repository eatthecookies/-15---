#ifndef __CL_FLOOR__H
#define __CL_FLOOR__H


#include "cl_base.h"

class cl_floor : public cl_base
{
public:
	cl_floor(cl_base* p_head_object, string s_name = "floorObject"); // ����������������� ����������� ������ cl_2

	void signal_meth(string& s_message); 			// ����� ������ �������
	void handler_meth(string s_message); 			// ����� �����������
};

#endif
