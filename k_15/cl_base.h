#ifndef __CL_BASE__H
#define __CL_BASE__H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

class cl_base;

#define SIGNAL_D(signal_meth) (TYPE_SIGNAL)(&signal_meth) 		// макроопределение для приведения указателя на метод сигнала 
#define HANDLER_D(handler_meth) (TYPE_HANDLER)(&handler_meth)	// макроопределение для приведения указателя на метод обработчика

typedef void (cl_base::* TYPE_SIGNAL) (string& s_message);
typedef void (cl_base::* TYPE_HANDLER) (string s_message);

struct o_sh                 	// Структура задания одной связи
{
	TYPE_SIGNAL  p_signal;   	// Указатель на метод сигнала
	cl_base* p_target;   		// Указатель на целевой объект
	TYPE_HANDLER p_handler;  	// Указатель на метод обработчика
};

class cl_base
{
	string s_name; 							// наименование объекта
	int i_state;							// значение состояния
	cl_base* p_head_object; 				// указатель на головной объект
	vector < cl_base* > p_sub_objects;		// указатели на подчиненные объекты
	vector < o_sh* > connections;			// вектор связей сигналов и обработчиеов
	int object_class;						// номер класса
public:
	cl_base(cl_base* p_head_object, string s_name = "Base_object"); 	// конструктор класса cl_base
	~cl_base();															// деструктор класса cl_base															// деструктор
	bool set_name(string s_new_name); 								   	// метод задания нового имени для объекта
	string get_name();													// метод получения имени объекта
	cl_base* get_head();												// метод получения указателя на головной объект	
	cl_base* get_sub_object(string s_name);							 	// метод получения указателя на подчиненный объект по имени

	int count(string s_name); 							// метод, который подсчитывает количество вхождений объектов с данным именем от текущего.
	cl_base* search_object(string s_name);				// метод поиска объекта на дереве иерархии по имени (вернет первый совпавший по имени)
	cl_base* find_object_from_current(string s_name);	// метод поиска объекта по имени на ветке дерева иерархии от текущего 
	cl_base* find_object_from_root(string s_name);		// метод поиска объекта по имени на всем дереве иерархии от корня 
	void print_tree(int spaces);						// метод вывода дерева иерархии объектов
	void print_tree_with_rns(int spaces);				// метод вывода дерева иерархии объектов
	void set_state(int i_state);						// метод для установки состояния
	bool based_is_stated(); 							// проверка влюченности объектов выше на дереве иерархии

	bool change_head_object(cl_base* new_head_object);  // метод переопределения головного объекта
	void delete_sub_object(string name);				// метод удаления подчиненного объекта по наименованию
	cl_base* get_object_pointer(string coordinate);		// метод получения указателя на любой объект по координатам

	void set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler); 		 // установление связи между объектами
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_object, TYPE_HANDLER p_ob_handler);	 // удаление связи между объектам
	void emit_signal(TYPE_SIGNAL p_signal, string& msg);										 // подача сигнала
	string get_absolute_path();																	 // получение абсолютного пути объекта
	int get_object_class();																		 // получение номера класса объекта
	void set_object_class(int n);																 // задание значения готовности объекта
	void set_all_state_on();																	 // включение вcех объектов
	int get_state();
	void delete_links(cl_base* p_target);
};



#endif