#include "cl_base.h"

cl_base::cl_base(cl_base* p_head_object, string s_name)
{
	this->p_head_object = p_head_object;
	this->s_name = s_name;

	if (p_head_object != nullptr) 							// ���� ���� ������������ ������
		p_head_object->p_sub_objects.push_back(this); 	// ���������� � ������ ����������� ��������� �������

};

cl_base::~cl_base()
{
	// ���������� ��������� �� �������� ������
	cl_base* p_root_object = this;
	while (p_root_object->p_head_object != nullptr)				// ���� �������� ������ �� ������ ������� ����������
		p_root_object = p_root_object->get_head();				// ����������� ����� �� ������
	
	p_root_object-> delete_links(this);
	for (int i = 0; i < p_sub_objects.size(); i++) 		// ����������� �������� ����������� ��������
		delete p_sub_objects[i];
}


void cl_base::delete_links(cl_base*p_target)
{
	//����� ������� �����, ������ � ������� p_target, �� ���� ������ ��������� ������
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
	return s_name;										// ������� �������� s_name �������� �������
}

cl_base* cl_base::get_head()
{
	return p_head_object;								// ������� �������� p_head_object �������� �������
}

cl_base* cl_base::get_sub_object(string s_name)
{
	for (int i = 0; i < p_sub_objects.size(); i++)
		if (p_sub_objects[i]->get_name() == s_name) 	// ���� ��� ������������ ������� ��������� � ������ � ���������
			return p_sub_objects[i];					// ������� ������ �� ����������� ������ � �������� i
	return nullptr;										// ���� �� ������� ������� � ������ ������ ������� ������� ���������
};

bool cl_base::set_name(string s_new_name)
{
	if (p_head_object != nullptr)													// ���� ���� �������� ������
		for (int i = 0; i < p_head_object->p_sub_objects.size(); i++)
			if (p_head_object->p_sub_objects[i]->get_name() == s_new_name) 	// ���� ���������� ������ � ����� �� ������ ��� � ���������
				return false;													// ������� false - ������ ����� �� �������
	s_name = s_new_name;														// ��������� �������� s_name �������� ������� �� ����� ���, ���������� � ���������
	return true;																// ������� true - ������ ����� ����������� �������
};


int cl_base::count_obj(string s_name) 			// ������������ ���������� ��������� �������� 
{											//� ������������ ������ �� ����� ����������� �������� �� ��������
	int c = 0;

	if (this->get_name() == s_name)			// ���� ��� �������� ������� ��������� � �������
		c++;

	for (auto p_sub_object : p_sub_objects) // ���� �� ����������� �������� �������� �������
		c += p_sub_object->count_obj(s_name);	// ����������� �����
	return c;
}

cl_base* cl_base::search_object(string s_name) 					// ����� ������ ���������� ������ ���� ��� �������
{
	if (this->s_name == s_name)							// ���� ��� �������� ������� ��������� � �������
		return this;
	for (auto p_sub_object : p_sub_objects) 					// ���� �� ����������� ��������
	{
		cl_base* p_found = p_sub_object->search_object(s_name); // ����������� �����
		if (p_found != nullptr)
			return p_found;
	}
	return nullptr;
}

cl_base* cl_base::find_object_from_current(string s_name) // ����� ��������� �� ������ ����� ����������� �� ��������
{
	if (this->count_obj(s_name) != 1)						  // ���� ���������� ����������� ��������� 1 (��� �� ���������)
		return nullptr;
	return search_object(s_name);
}

cl_base* cl_base::find_object_from_root(string s_name) // ����� ��������� �� ������ ����� ����� ������
{
	cl_base* p_root_object = this;
	while (p_root_object->get_head() != nullptr)
		p_root_object = p_root_object->get_head();
	return p_root_object->find_object_from_current(s_name);
}

void cl_base::print_tree(int spaces)
{
	cout << endl;									// ������� �� ����� ������
	for (int i = 0; i < spaces; i++) cout << " "; 	// ������ ��������
	cout << get_name();								// ����� ����� �������� �������
	for (auto p_sub_object : p_sub_objects) 		// ���� �� ����������� ��������
		p_sub_object->print_tree(spaces + 4);		// ����������� ����� � ��������� �� ����� ����� ������
}

void cl_base::print_tree_with_rns(int spaces)
{
	cout << endl;											// ������� �� ����� ������
	for (int i = 0; i < spaces; i++) cout << " "; 			// ������ ��������
	cout << get_name();										// ����� ����� �������� �������
	if (i_state != 0) 										// ����� ���������
		cout << " is ready";
	else
		cout << " is not ready";
	for (auto p_sub_object : p_sub_objects) 				// ���� �� ����������� ��������
		p_sub_object->print_tree_with_rns(spaces + 4);	// ����������� ����� � ��������� �� ����� ����� ������
}

void cl_base::set_state(int i_state) 					// ������� ��������� ����������
{
	if (i_state == 0) 									// ��������� ��� ������� ���� �� �����
	{
		this->i_state = i_state;
		for (auto p_sub_object : p_sub_objects)			// ���� �� ����������� ��������
			p_sub_object->set_state(i_state);			// ����������� �����
	}
	else
	{
		if (get_head() == nullptr || based_is_stated() == true) // ���� ������� ������ ��������, ���� ��� ������� ���� �� ����� ��������
			this->i_state = i_state;
	}
}

bool cl_base::based_is_stated()
{
	if (get_head() == nullptr) 					// ���� ������� ������ ��������, �� ����� ���� �� ����, ������ ������� i_state
		return i_state;
	if (get_head()->i_state == 0) 				// ���� ���. ������ �� �������� � �������� ������ ��������, �� ������� false
		return false;
	else return get_head()->based_is_stated(); 	// ����� �������� ��� ������� ���� �� �����
}

bool cl_base::change_head_object(cl_base* p_new_head_object)
{
	if (p_head_object == nullptr 										// ������� ������ � ��������
		|| p_new_head_object == nullptr 								// ����� �������� ������ �� ��������� �� ������� ���������
		|| p_new_head_object->get_sub_object(this->s_name) != nullptr)	// � ������ ��������� ������� ��� ���� ����������� ������ � ����� ������
	{
		return false;
	}

	cl_base* p_root_object = p_new_head_object;
	while (p_root_object->p_head_object != nullptr)			// ���� ����� �� ����� �� ������ ��������� �������
	{
		if (p_root_object == this)							// ���� ����� �������� �� ��������� � ������  ��������� ������� ���������� ������� ������ 
			return false;
		p_root_object = p_root_object->get_head();
	}

	int i = 0;
	while (p_head_object->p_sub_objects[i]->s_name != this->s_name) i++;
	p_head_object->p_sub_objects.erase(p_head_object->p_sub_objects.begin() + i);

	this->p_head_object = p_new_head_object;
	p_new_head_object->p_sub_objects.push_back(this); // ���������� �������� ������� � ������ ���������� �� ����������� ������� ������ ��������� �������
	return true;
};

void cl_base::delete_sub_object(string name) 		// ����� �������� ������������ �������
{
	int i = 0;
	while (p_sub_objects[i]->s_name != name) i++;
	
	delete p_sub_objects[i];
	p_sub_objects.erase(p_sub_objects.begin() + i);	// �������� �� ������ ���������� �� ����������� ������� � �������� ��������� �� ��������� ������
	
}

cl_base* cl_base::get_object_pointer(string coordinate)
{
	string s_obj_name = "";
	cl_base* p_object = this;

	// ���������� ��������� �� �������� ������
	cl_base* p_root_object = this;
	while (p_root_object->p_head_object != nullptr)				// ���� �������� ������ �� ������ ������� ����������
		p_root_object = p_root_object->get_head();				// ����������� ����� �� ������


	if (coordinate == "/") 										// �������� ������
	{
		return p_root_object;
	}

	if (coordinate == ".") return this; 						// ������� ������

	if (coordinate[0] == '/' && coordinate[1] == '/') 			// ����� ������� �� ����������� ����� �� ���������
	{
		s_obj_name = coordinate.substr(2, coordinate.size() - 2);	// ����� ��������� � ������ ������� �� ������ ���� "//name"
		return find_object_from_root(s_obj_name);
	}

	if (coordinate[0] == '.') 									// ����� ������� �� ����������� ����� �� ��������
	{
		s_obj_name = coordinate.substr(1, coordinate.size() - 1); // ����� ��������� � ������ ������� �� ������ ���� "/name"
		return find_object_from_current(s_obj_name);
	}

	if (coordinate[0] != '/') 									// ������������� ���������� �� �������� �������
	{
		for (int i = 0; i < coordinate.size(); i++) 			// ���� �� ��������� ������
		{
			if (coordinate[i] != '/') 						// ���� �� ��������� "/" ���������� ��������� ��� �������
			{
				s_obj_name += coordinate[i];
			}
			else
			{
				p_object = p_object->get_sub_object(s_obj_name);// ��������� "/" ������� �� ����������� �������� ������ � ���������
				if (p_object == nullptr) return nullptr;
				s_obj_name = "";								// ���������� ������ s_obj_name
			}
		}

		p_object = p_object->get_sub_object(s_obj_name);		// ���������� �������� ����� ���������� �����
		return p_object;										// ������� ���������� ��������
	}
	else if (coordinate[0] == '/')
	{
		p_object = p_root_object; 								// ���������� ���������� �� ��������� �������

		for (int i = 1; i < coordinate.size(); i++) 			// ���� �� ��������� ������
		{
			if (coordinate[i] != '/') 						// ���� �� ��������� "/" ���������� ��������� ��� �������
			{
				s_obj_name += coordinate[i];
			}
			else
			{
				p_object = p_object->get_sub_object(s_obj_name);// ��������� "/" ������� �� ����������� �������� ������ � ���������
				if (p_object == nullptr) return nullptr;
				s_obj_name = "";								// ���������� ������ s_obj_name
			}
		}

		p_object = p_object->get_sub_object(s_obj_name);		// ���������� �������� ����� ���������� �����
		return p_object;										// ������� ���������� ��������
	}
	return nullptr;
}


string cl_base::get_absolute_path()						// ��������� ����������� ����							
{
	cl_base* p_current_object = this->p_head_object; 	// ��������� �� ������� ������ ���������������� ��������
	string path = this->s_name;							// ��������� ���� ������� � ����� �������� �������

	if (p_current_object == nullptr)					// ���� ������� ������ ����������� ���������
		return "/";

	// ���������� ����� ������ ��������
	while (p_current_object->p_head_object != nullptr)		// ���� �� ����� �������
	{
		path = p_current_object->s_name + '/' + path; 		// ������������ ���� �� ���� ������������� ��������
		p_current_object = p_current_object->p_head_object;	// ������� ������
	}

	path = '/' + path;
	return path;
}


void cl_base::set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)
{
	o_sh* p_value;
	for (int i = 0; i < connections.size(); i++)			// ���� ��� ���������� ���������� ������������ �����
		if (connections[i]->p_signal == p_signal &&
			connections[i]->p_target == p_target &&
			connections[i]->p_handler == p_handler)
			return;

	p_value = new o_sh(); 			// �������� ������� ��������� ��� 
	// �������� ���������� � ����� �����

	p_value->p_signal = p_signal;	// ���������� �����
	p_value->p_target = p_target;
	p_value->p_handler = p_handler;

	connections.push_back(p_value);	// ���������� ����� �����
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)
{
	for (int i = 0; i < connections.size(); i++)
		if (connections[i]->p_signal == p_signal &&
			connections[i]->p_target == p_target &&
			connections[i]->p_handler == p_handler)
		{
			delete connections[i];						// �������� ������� ��������� �� ������
			connections.erase(connections.begin() + i); // ��������� i-���� �������� � �������
		}
}


void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command)
{
	if (i_state == 0) return;							// ���� ����� �� �������

	TYPE_HANDLER   p_handler;
	cl_base* p_object;

	(this->*p_signal) (s_command);  					// ����� ������ �������

	for (int i = 0; i < connections.size(); i++) 		// ���� �� ���� ������������
	{
		if (connections[i]->p_signal == p_signal)  		// ����������� ����������� �����������
		{
			p_handler = connections[i]->p_handler;
			p_object = connections[i]->p_target;

			if (p_object->i_state != 0)
				(p_object->*p_handler) (s_command);  	// ����� ������ �����������
		}
	}
}


int cl_base::get_object_class()
{
	return object_class;			//������ ���������� ����
}

void cl_base::set_object_class(int n)
{
	object_class = n;				// ����������� ����
}

void cl_base::set_all_state_on()
{
	this->i_state = 1;
	for (auto p_sub_object : this->p_sub_objects)	// ���� �� ����������� ��������
	{
		p_sub_object->i_state = 1;				// ��������� ���������
		p_sub_object->set_all_state_on();		// ����������� �����
	}
}

int cl_base::get_state()
{
	return i_state;
}