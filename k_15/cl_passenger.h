#ifndef __CL_PASSENGER__H
#define __CL_PASSENGER__H



#include "cl_base.h"

class cl_passenger : public cl_base
{
	int i_initial_floor;  		// номер исходного этажа
	int i_destination_floor; 	// номер целевого этажа
	// за состояние отвечает i_state, 1 - на этаже и хочет на верх
	//							  2 - на этаже и хочет вниз
	//							  3 - в лифте наверх
	//							  4 - в лифте вниз1

	int i_current_floor;

	int i_pushed_button;
	int i_tact;
public:
	cl_passenger(cl_base* p_head_object, string s_name = "passenger"); // параметризованный конструктор класса cl_2

	int get_current_floor();

	void set_dest_floor(int);
	void set_init_floor(int);

	void signal_meth(string& s_message); 			// метод подачи сигнала
	void elevator_has_been_called(string s_message); 			// метод обработчика
};

#endif
	