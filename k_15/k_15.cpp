#include "cl_base.h"
#include "cl_system.h"


int main()
{
	cl_system ob_cl_application(nullptr); 		// создание корневого объекта
	ob_cl_application.build_tree_objects();   		// конструирование системы, построение дерева объектов
	return ob_cl_application.exec_app();	   		// запуск системы
}