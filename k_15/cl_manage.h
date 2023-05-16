#ifndef __CL_MANAGE__H
#define __CL_MANAGE__H

#include "cl_base.h"

class cl_manage : public cl_base
{
	int i_current_floor;			// номер этажа, на котором находится лифт
	string s_current_direction;		// направление движения лифта

public:
	cl_manage(cl_base* p_head_object, string s_name = "manageObject"); // параметризованный конструктор класса cl_2

	void signal_meth(string& s_message); 			// метод подачи сигнала
	void handler_meth(string s_message); 			// метод обработчика
};

#endif
