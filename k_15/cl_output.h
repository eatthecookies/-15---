#ifndef __CL_OUTPUT__H
#define __CL_OUTPUT__H



#include "cl_base.h"

class cl_output : public cl_base
{
public:
	cl_output(cl_base* p_head_object, string s_name = "output"); // параметризованный конструктор класса cl_2

	void console_output(string s_message); 			// метод обработчика
};

#endif
