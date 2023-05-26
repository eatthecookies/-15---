#ifndef __CL_SYSTEM__H
#define __CL_SYSTEM__H
#include "cl_base.h"
#include "cl_system.h"
#include "cl_manage.h"
#include "cl_cab.h"
#include "cl_passenger.h"
#include "cl_output.h"
#include "cl_floor.h"
#include "cl_input.h"

class cl_system : public cl_base
{
	string current_command;				// текущая команда
	int num_floors;
public:
	cl_system(cl_base* p_head_object);  // конструктор
	int exec_app();						// метод запуска основного алгоритма приложения  		
	void build_tree_objects();			// метод построения дерева объектов 

	// методы сигнала
	void signal_to_read_command(string& s_message); 			
	void signal_to_сhange_cab_capacity(string& s_message);
	void signal_to_push_the_button_in_cab(string& s_message);
	void signal_to_push_button_on_the_floor(string& s_message);
	void signal_to_output(string& s_message);
	void signal_to_set_init_dest_floor(string& s_message);

	void signal_for_elevator_movement(string& s_message);

	void signal_to_increment_num_passengers(string& s_message);

	void signal_to_decrement_num_passengers(string& s_message);

	void signal_to_get_current_floor(string& s_message);

	void signal_to_get_num_passengers(string& s_message);

	void signal_to_get_direction(string& s_message);

	void signal_to_get_capacity(string& s_message);

	// методы обработчики
	void handler(string s_message); 			
	void load_passengers(string s_message);
	void unload_passengers(string s_message);
};


#endif
