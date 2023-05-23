#ifndef __CL_INPUT__H
#define __CL_INPUT__H

#include "cl_base.h"

class cl_input : public cl_base
{
public:
	cl_input(cl_base* p_head_object, string s_name = "input"); // параметризованный конструктор класса cl_2

	void signal(string& s_message); 			// метод подачи сигнала
	void read_command(string s_message);
	void button_on_the_floor_has_been_pushed(string s_message); 			// метод обработчика

};



#endif
