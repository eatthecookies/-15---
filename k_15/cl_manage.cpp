#include "cl_manage.h"

cl_manage::cl_manage(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
	
}

// методы обработчики

void cl_manage::button_in_the_cab_has_been_pushed(string s_message)
{
	int i_dest_floor, pass_direction;

	stringstream ss(s_message);
	ss >> i_dest_floor >> pass_direction;
	// 1 - верх 
	// 2 - вниз

	if (pass_direction == 2) pass_direction = -1;

	for (int i = pointer; i < queue.size(); i++)
	{
		if (curr_direction == pass_direction && curr_direction == 1) // едет вверх
		{
			if (queue[i - 1] < i_dest_floor < queue[i])
			{
				if (count(queue.begin() + pointer, queue.end(), i_dest_floor) == 0)
					queue.insert(queue.begin() + i, i_dest_floor);
				return;
			}
		}
		else if (curr_direction == pass_direction && curr_direction == -1) // едет вниз
		{
			if (queue[i - 1] > i_dest_floor > queue[i])
			{
				if (count(queue.begin() + pointer, queue.end(), i_dest_floor) == 0)
					queue.insert(queue.begin() + i, i_dest_floor);
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
		return;
	}
	
 	for (int i = pointer; i < queue.size() ; i++)
	{
		if (curr_direction == pass_direction && curr_direction == 1) // играет вверх
		{
			if (queue[i - 1] < i_init_floor < queue[i])
			{
				if (count(queue.begin() + pointer, queue.end(), i_init_floor) == 0)
					queue.insert(queue.begin() + i, i_init_floor);
				return;
			}
		}
		else if (curr_direction == pass_direction && curr_direction == -1)
		{
			if (queue[i - 1] > i_init_floor > queue[i])
			{
				if (count(queue.begin() + pointer, queue.end(), i_init_floor) == 0)
					queue.insert(queue.begin() + i, i_init_floor);
				return;
			}
		}
	}

	queue.push_back(i_init_floor);
}

void cl_manage::button_on_the_floor_has_been_pushed_again(string s_message)
{
	int i_init_floor = stoi(s_message);
	if (count(queue.begin() + pointer, queue.end(), i_init_floor) == 0)
		queue.push_back(stoi(s_message));
}

void cl_manage::moving()
{
	if (queue.empty() or pointer > queue.size() - 1)
	{
		queue.push_back(1);
		moving();
	}
	else
	{
		if (i_current_floor < queue[pointer])
		{
			curr_direction = 1;
			set_state(1);
		}
		else if (i_current_floor > queue[pointer])
		{
			curr_direction = -1;
			set_state(2);
		}

		if (queue[pointer] != i_current_floor)
			i_current_floor += curr_direction;
		else
		{
			set_state(3);
			pointer++;
			stop();	
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
	i_number_of_passengers++;
}

int cl_manage::get_current_floor()
{
	return i_current_floor;
}

int cl_manage::get_num_passengers()
{
	return i_number_of_passengers;
}

int cl_manage::get_direction()
{
	return curr_direction;
}


// методы сигнала

void cl_manage::signal_to_load_passengers(string& s_message)
{
}
void cl_manage::signal_to_unload_passengers(string& s_message)
{
}
