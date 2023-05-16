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
public:
	cl_system(cl_base* p_head_object);  // конструктор
	int exec_app();						// метод запуска основного алгоритма приложения  		
	void build_tree_objects();			// метод построения дерева объектов 

	void signal_meth(string& s_message); 			// метод подачи сигнала
	void handler_meth(string s_message); 			// метод обработчика
};


#endif
