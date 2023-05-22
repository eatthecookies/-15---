#ifndef __CL_FLOOR__H
#define __CL_FLOOR__H


#include "cl_base.h"

class cl_floor : public cl_base
{
public:
	cl_floor(cl_base* p_head_object, string s_name = "floor"); // параметризованный конструктор класса cl_2

	void signal_meth(string& s_message); 			// метод подачи сигнала
	void button_has_pushed(string s_message);
	void signal_to_call_elevator(string& s_message);
	void elevator_has_been_called(string s_message); 			// метод обработчика
};

#endif
