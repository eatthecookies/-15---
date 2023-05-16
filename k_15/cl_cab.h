#ifndef __CL_CAB__H
#define __CL_CAB__H


#include "cl_base.h"

class cl_cab : public cl_base
{
	int i_capacity; 												// вместимость кабины лифта
public:
	cl_cab(cl_base* p_head_object, string s_name = "cabinObject"); 	// параметризованный конструктор класса cl_2
	void signal_meth(string& s_message); 							// метод подачи сигнала
	void handler_meth(string s_message); 							// метод обработчика
};

#endif
