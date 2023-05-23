#include "cl_manage.h"

cl_manage::cl_manage(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	set_object_class(4);
}

void cl_manage::signal_meth(string& s_message)
{
	
}

void cl_manage::button_in_the_cab_has_been_pushed(string s_message)
{
	//todo вот эта часть надо переписать
	int i_dest_floor;
	int pass_direction;
	stringstream ss(s_message);
	ss >> i_dest_floor >> pass_direction;
	// 1 - верх 
	// 2 - вниз
	if (pass_direction == 2) pass_direction = -1;
	
	if (last_added_ind.empty()) cout << "i am empty((" << endl;

	for (int i = last_added_ind[0]; i < queue.size() - 1; i++)
	{
		if (direction == pass_direction && direction == 1) // играет вверх
		{
			if (queue[i] < i_dest_floor < queue[i + 1])
			{
				queue.insert(queue.begin() + i, i_dest_floor);
				last_added_ind.erase(last_added_ind.begin());
				return;
			}
		}
		else if (direction == pass_direction && direction == -1)
		{
			if (queue[i] > i_dest_floor > queue[i + 1])
			{
				queue.insert(queue.begin() + i, i_dest_floor);
				last_added_ind.erase(last_added_ind.begin());
				return;
			}
		}
	}
	queue.push_back(i_dest_floor);
}

void cl_manage::button_on_the_floor_has_been_pushed(string s_message)
{
	int i_init_floor;
	int pass_direction;
	stringstream ss(s_message);
	ss >> i_init_floor >> pass_direction;
	// 1 - верх 
	// 2 - вниз
	if (pass_direction == 2) pass_direction = -1;
	
	if (queue.empty())
	{
		queue.push_back(i_init_floor);
		last_added_ind.insert(last_added_ind.begin(), last_added_ind.size());
		return;
	}
	
	for (int i = 0; i < queue.size() - 1; i++)
	{
		cout << i << endl;
		if (direction == pass_direction && direction == 1) // играет вверх
		{
			if (i == 0 && i_init_floor < queue[i])
			{
				cout << i_init_floor << "<" << queue[i] << endl;
				queue.insert(queue.begin() + i, i_init_floor);
				last_added_ind.insert(last_added_ind.begin(), i);
				return;
			}
			if (queue[i] < i_init_floor < queue[i + 1])
			{
				queue.insert(queue.begin() + i, i_init_floor);
				last_added_ind.insert(last_added_ind.begin(), i);
				return;
			}
		}
		else if (direction == pass_direction && direction == -1)
		{
			if (i == 0 && i_init_floor > queue[i])
			{
				queue.insert(queue.begin() + i, i_init_floor);
				last_added_ind.insert(last_added_ind.begin(), i);
				return;
			}
			if (queue[i] > i_init_floor > queue[i + 1])
			{
				queue.insert(queue.begin() + i, i_init_floor);
				last_added_ind.insert(last_added_ind.begin(), i);
				return;
			}
		}
	}
	queue.push_back(i_init_floor);
	last_added_ind.insert(last_added_ind.begin(), last_added_ind.size());
	return;
	
	//todo вот эта часть надо переписать
	//queue.push_back(i_init_floor);
}

void cl_manage::moving()
{
	if (queue.empty())
	{
		queue.push_back(1);
		moving();
	}
	else
	{
		if (i_current_floor < queue[0])
			direction = 1;
		else
			direction = -1;

		if (queue[0] != i_current_floor)
			i_current_floor += direction;
		else
		{
			direction = 0;
			stop();
			queue.erase(queue.begin());
		}

	}
}

void cl_manage::stop()
{
	cl_base* p_floor = get_object_pointer("/floor_" + to_string(i_current_floor));
	cl_base* p_cab = get_object_pointer("/manage/cabin");
	string command = "";
	
	if (!p_cab->get_sub_objects().empty())	 // если в кабине есть пассажиры
		emit_signal(SIGNAL_D(cl_manage::signal_to_unload_passengers), command);


	if (!p_floor->get_sub_objects().empty()) // если на этаже есть пассажиры
		emit_signal(SIGNAL_D(cl_manage::signal_to_load_passengers), command);

}

void cl_manage::decrement_num_passengers()
{
	i_number_of_passengers--;
}

void cl_manage::increment_num_passengers()
{
	i_number_of_passengers ++;
}




int cl_manage::get_num_passengers()
{
	return i_number_of_passengers;
}

int cl_manage::get_direction()
{
	return direction;
}

int cl_manage::get_current_floor()
{
	return i_current_floor;
}

void cl_manage::signal_to_load_passengers(string& s_message)
{
}
void cl_manage::signal_to_unload_passengers(string& s_message)
{
}