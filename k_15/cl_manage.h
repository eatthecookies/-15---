#ifndef __CL_MANAGE__H
#define __CL_MANAGE__H

#include "cl_base.h"

class cl_manage : public cl_base
{
	// за состояние отвечает i_state, если 2 - то на этаже, если 3, едет на верх, если 4 - едет вниз, 1 - еще не начинал
	vector <int> queue;
	int i_current_floor = 1;		// номер этажа, на котором находится лифт
	int i_number_of_passengers = 0;
public:
	cl_manage(cl_base* p_head_object, string s_name = "manage"); // параметризованный конструктор класса cl_2
	int get_current_floor();
	int get_num_passengers();
	void signal_meth(string& s_message); 			// метод подачи сигнала
	void elevator_has_been_called(string s_message); 			// метод обработчика
};

#endif
