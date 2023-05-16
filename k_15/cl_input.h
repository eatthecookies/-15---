#ifndef __CL_INPUT__H
#define __CL_INPUT__H

#include "cl_base.h"

class cl_input : public cl_base
{
public:
	cl_input(cl_base* p_head_object, string s_name = "inputObject"); // ����������������� ����������� ������ cl_2

	void signal_meth(string& s_message); 			// ����� ������ �������
	void handler_meth(string s_message); 			// ����� �����������

};



#endif
