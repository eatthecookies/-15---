#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, string s_name)
{
	this->p_head_object = p_head_object;
	this->s_name = s_name;

	if (p_head_object != nullptr) 							// если есть родительский объект
		p_head_object->p_sub_objects.push_back(this); 	// добавление в состав подчиненных головного объекта

};

cl_base::~cl_base()
{
	// нахождение указателя на корневой объект
	cl_base* p_root_object = this;
	while (p_root_object->p_head_object != nullptr)				// пока головной объект не станет нулевым указателем
		p_root_object = p_root_object->get_head();				// восхождение вверх по дереву
	
	p_root_object-> delete_links(this);
	for (int i = 0; i < p_sub_objects.size(); i++) 		// поочередное удаление подчиненных объектов
		delete p_sub_objects[i];
}


void cl_base::delete_links(cl_base*p_target)
{
	//Метод удаляет связи, идущие к объекту p_target, из всех друших элементов дерева
	for (int i = 0; i < this->connections.size(); i++)
	{
		if (this->connections[i]->p_target == p_target)
		{
			delete this->connections[i];
			this->connections.erase(connections.begin() + i);
		}
	}
	for (auto p_sub : p_sub_objects)
		p_sub->delete_links(p_target);
}

vector<cl_base*> cl_base::get_sub_objects()
{
	return p_sub_objects;
}

string cl_base::get_name()
{
	return s_name;										// возврат свойства s_name текущего объекта
}

cl_base* cl_base::get_head()
{
	return p_head_object;								// возврат свойства p_head_object текущего объекта
}

cl_base* cl_base::get_sub_object(string s_name)
{
	for (int i = 0; i < p_sub_objects.size(); i++)
		if (p_sub_objects[i]->get_name() == s_name) 	// если имя подчиненного объекта совпадает с именем в параметре
			return p_sub_objects[i];					// возврат ссылки на подчиненный объект с индексом i
	return nullptr;										// если не найдено объекта с данным именем вернуть нулевой указатель
};

bool cl_base::set_name(string s_new_name)
{
	if (p_head_object != nullptr)													// если есть головной объект
		for (int i = 0; i < p_head_object->p_sub_objects.size(); i++)
			if (p_head_object->p_sub_objects[i]->get_name() == s_new_name) 	// если встретился объект с таким же именем как в параметре
				return false;													// возврат false - замена имени не удалась
	s_name = s_new_name;														// изменение свойства s_name текущего объекта на новое имя, переданное в параметре
	return true;																// возврат true - замена имени произведена успешно
};


int cl_base::count_obj(string s_name) 			// подсчитывает количество вхождений объектов 
{											//с определенным именем на ветке подчиненных объектов от текущего
	int c = 0;

	if (this->get_name() == s_name)			// если имя текущего объекта совпадает с искомым
		c++;

	for (auto p_sub_object : p_sub_objects) // цикл по подчиненным объектам текущего объекта
		c += p_sub_object->count_obj(s_name);	// рекурсивный вызов
	return c;
}

cl_base* cl_base::search_object(string s_name) 					// вернёт первый попавшийся объект если имя совпало
{
	if (this->s_name == s_name)							// если имя текущего объекта совпадает с искомым
		return this;
	for (auto p_sub_object : p_sub_objects) 					// цикл по подчиненным объектам
	{
		cl_base* p_found = p_sub_object->search_object(s_name); // рекурсивный вызов
		if (p_found != nullptr)
			return p_found;
	}
	return nullptr;
}

cl_base* cl_base::find_object_from_current(string s_name) // найти указатель на объект среди подчиненных от текущего
{
	if (this->count_obj(s_name) != 1)						  // если количество подчиненных превышает 1 (имя не уникально)
		return nullptr;
	return search_object(s_name);
}

cl_base* cl_base::find_object_from_root(string s_name) // найти указатель на объект среди всего дерева
{
	cl_base* p_root_object = this;
	while (p_root_object->get_head() != nullptr)
		p_root_object = p_root_object->get_head();
	return p_root_object->find_object_from_current(s_name);
}

void cl_base::print_tree(int spaces)
{
	cout << endl;									// переход на новую строку
	for (int i = 0; i < spaces; i++) cout << " "; 	// печать пробелов
	cout << get_name();								// вывод имени текущего объекта
	for (auto p_sub_object : p_sub_objects) 		// цикл по подчиненным объектам
		p_sub_object->print_tree(spaces + 4);		// рекурсивный вызов с переходом на новую ветвь дерева
}

void cl_base::print_tree_with_rns(int spaces)
{
	cout << endl;											// переход на новую строку
	for (int i = 0; i < spaces; i++) cout << " "; 			// печать пробелов
	cout << get_name();										// вывод имени текущего объекта
	if (i_state != 0) 										// вывод состояния
		cout << " is ready";
	else
		cout << " is not ready";
	for (auto p_sub_object : p_sub_objects) 				// цикл по подчиненным объектам
		p_sub_object->print_tree_with_rns(spaces + 4);	// рекурсивный вызов с переходом на новую ветвь дерева
}

void cl_base::set_state(int i_state) 					// задание состояния готовности
{
	if (i_state == 0) 									// отключаем все объекты вниз по ветке
	{
		this->i_state = i_state;
		for (auto p_sub_object : p_sub_objects)			// цикл по подчиненным объектам
			p_sub_object->set_state(i_state);			// рекурсивный вызов
	}
	else
	{
		if (get_head() == nullptr || based_is_stated() == true) // если текущий объект корневой, либо все объекты выше по ветке включены
			this->i_state = i_state;
	}
}

bool cl_base::based_is_stated()
{
	if (get_head() == nullptr) 					// если текущий объект корневой, то вверх идти не надо, просто возврат i_state
		return i_state;
	if (get_head()->i_state == 0) 				// если тек. объект не корневой и головной объект выключен, то возврат false
		return false;
	else return get_head()->based_is_stated(); 	// иначе проверяй все объекты выше по ветке
}

bool cl_base::change_head_object(cl_base* p_new_head_object)
{
	if (p_head_object == nullptr 										// текущий объект – корневой
		|| p_new_head_object == nullptr 								// новый головной объект не ссылается на нулевой указатель
		|| p_new_head_object->get_sub_object(this->s_name) != nullptr)	// у нового головного объекта уже есть подчиненный объект с таким именем
	{
		return false;
	}

	cl_base* p_root_object = p_new_head_object;
	while (p_root_object->p_head_object != nullptr)			// идеи вверх до корня от нового головного объекта
	{
		if (p_root_object == this)							// если среди головных по отношению к новому  головному объекту встретился текущий объект 
			return false;
		p_root_object = p_root_object->get_head();
	}

	int i = 0;
	while (p_head_object->p_sub_objects[i]->s_name != this->s_name) i++;
	p_head_object->p_sub_objects.erase(p_head_object->p_sub_objects.begin() + i);

	this->p_head_object = p_new_head_object;
	p_new_head_object->p_sub_objects.push_back(this); // добавление текущего объекта в список указателей на подчиненные объекты нового головного объекта
	return true;
};

void cl_base::delete_sub_object(string name) 		// метод удаления подчиненного объекта
{
	int i = 0;
	while (p_sub_objects[i]->s_name != name) i++;
	
	delete p_sub_objects[i];
	p_sub_objects.erase(p_sub_objects.begin() + i);	// удаление из списка указателей на подчиненные объекты у текущего указателя на удаляемый объект
	
}

cl_base* cl_base::get_object_pointer(string coordinate)
{
	string s_obj_name = "";
	cl_base* p_object = this;

	// нахождение указателя на корневой объект
	cl_base* p_root_object = this;
	while (p_root_object->p_head_object != nullptr)				// пока головной объект не станет нулевым указателем
		p_root_object = p_root_object->get_head();				// восхождение вверх по дереву


	if (coordinate == "/") 										// корневой объект
	{
		return p_root_object;
	}

	if (coordinate == ".") return this; 						// текущий объект

	if (coordinate[0] == '/' && coordinate[1] == '/') 			// поиск объекта по уникальному имени от корневого
	{
		s_obj_name = coordinate.substr(2, coordinate.size() - 2);	// берем подстроку с именем объекта из строки вида "//name"
		return find_object_from_root(s_obj_name);
	}

	if (coordinate[0] == '.') 									// поиск объекта по уникальному имени от текущего
	{
		s_obj_name = coordinate.substr(1, coordinate.size() - 1); // берем подстроку с именем объекта из строки вида "/name"
		return find_object_from_current(s_obj_name);
	}

	if (coordinate[0] != '/') 									// относительная координата от текущего объекта
	{
		for (int i = 0; i < coordinate.size(); i++) 			// цикл по элементам строки
		{
			if (coordinate[i] != '/') 						// если не встретили "/" постепенно формируем имя объекта
			{
				s_obj_name += coordinate[i];
			}
			else
			{
				p_object = p_object->get_sub_object(s_obj_name);// встретили "/" находим по подчиненным объектам нужный и сохраняем
				if (p_object == nullptr) return nullptr;
				s_obj_name = "";								// сбрасываем строку s_obj_name
			}
		}

		p_object = p_object->get_sub_object(s_obj_name);		// остаточные действия после завершения цикла
		return p_object;										// возврат найденного элемента
	}
	else if (coordinate[0] == '/')
	{
		p_object = p_root_object; 								// абсолютная координата от корневого объекта

		for (int i = 1; i < coordinate.size(); i++) 			// цикл по элементам строки
		{
			if (coordinate[i] != '/') 						// если не встретили "/" постепенно формируем имя объекта
			{
				s_obj_name += coordinate[i];
			}
			else
			{
				p_object = p_object->get_sub_object(s_obj_name);// встретили "/" находим по подчиненным объектам нужный и сохраняем
				if (p_object == nullptr) return nullptr;
				s_obj_name = "";								// сбрасываем строку s_obj_name
			}
		}

		p_object = p_object->get_sub_object(s_obj_name);		// остаточные действия после завершения цикла
		return p_object;										// возврат найденного элемента
	}
	return nullptr;
}


string cl_base::get_absolute_path()						// получение абсолютного пути							
{
	cl_base* p_current_object = this->p_head_object; 	// указатель на текущий объект инициализируется головным
	string path = this->s_name;							// формируем путь начиная с имени текущего объекта

	if (p_current_object == nullptr)					// если текущий объект подчиненный корневого
		return "/";

	// нахождение корня дерева иерархии
	while (p_current_object->p_head_object != nullptr)		// цикл до корня системы
	{
		path = p_current_object->s_name + '/' + path; 		// формирование пути из имен встретившихся объектов
		p_current_object = p_current_object->p_head_object;	// переход дальше
	}

	path = '/' + path;
	return path;
}


void cl_base::set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)
{
	o_sh* p_value;
	for (int i = 0; i < connections.size(); i++)			// цикл для исключения повторного установления связи
		if (connections[i]->p_signal == p_signal &&
			connections[i]->p_target == p_target &&
			connections[i]->p_handler == p_handler)
			return;

	p_value = new o_sh(); 			// создание объекта структуры для 
	// хранения информации о новой связи

	p_value->p_signal = p_signal;	// заполнение полей
	p_value->p_target = p_target;
	p_value->p_handler = p_handler;

	connections.push_back(p_value);	// добавление новой связи
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)
{
	for (int i = 0; i < connections.size(); i++)
		if (connections[i]->p_signal == p_signal &&
			connections[i]->p_target == p_target &&
			connections[i]->p_handler == p_handler)
		{
			delete connections[i];						// удаление объекта структуры из памяти
			connections.erase(connections.begin() + i); // удалеение i-того элемента в ВЕКТОРЕ
		}
}


void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command)
{
	if (i_state == 0) return;							// если обект не включен

	TYPE_HANDLER   p_handler;
	cl_base* p_object;

	(this->*p_signal) (s_command);  					// вызов метода сигнала

	for (int i = 0; i < connections.size(); i++) 		// цикл по всем обработчикам
	{
		if (connections[i]->p_signal == p_signal)  		// определение допустимого обработчика
		{
			p_handler = connections[i]->p_handler;
			p_object = connections[i]->p_target;

			if (p_object->i_state != 0)
				(p_object->*p_handler) (s_command);  	// вызов метода обработчика
		}
	}
}


int cl_base::get_object_class()
{
	return object_class;			//возрат приватного поля
}

void cl_base::set_object_class(int n)
{
	object_class = n;				// определение поля
}

void cl_base::set_all_state_on()
{
	this->i_state = 1;
	for (auto p_sub_object : this->p_sub_objects)	// цикл по подчиненным объектам
	{
		p_sub_object->i_state = 1;				// установка состояния
		p_sub_object->set_all_state_on();		// рекурсивный вызов
	}
}

int cl_base::get_state()
{
	return i_state;
}