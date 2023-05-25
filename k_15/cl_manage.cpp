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
	
	int i_dest_floor;
	int pass_direction;
	stringstream ss(s_message);
	ss >> i_dest_floor >> pass_direction;
	// 1 - верх 
	// 2 - вниз
	if (pass_direction == 2) pass_direction = -1;

	//for (int i = pointer; i < queue.size() - 1; i++)
	//{
	//	if (curr_direction == pass_direction && curr_direction == 1) // едет вверх
	//	{
	//		if (queue[i] < i_dest_floor < queue[i + 1])
	//		{
	//			queue.insert(queue.begin() + i, i_dest_floor);
	//			last_added_ind.erase(last_added_ind.begin());
	//			return;
	//		}
	//	}
	//	else if (curr_direction == pass_direction && curr_direction == -1)
	//	{
	//		if (queue[i] > i_dest_floor > queue[i + 1])
	//		{
	//			queue.insert(queue.begin() + i, i_dest_floor);
	//			last_added_ind.erase(last_added_ind.begin());
	//			return;
	//		}
	//	}
	//}
	
	//for (int i = 0; i < queue1.size() - 1; i++)
	//{
	//	if (past_direction == pass_direction && past_direction == 1) // едет вверх
	//	{
	//		
	//		if (queue1[i] < i_dest_floor < queue1[i + 1])
	//		{
	//			queue1.insert(queue1.begin() + i + 1, i_dest_floor);
	//			return;
	//		}
	//	}
	//	else if (past_direction == pass_direction && past_direction == -1)
	//	{
	//		if (queue1[i] > i_dest_floor > queue1[i + 1])
	//		{
	//			queue1.insert(queue1.begin() + i + 1, i_dest_floor);
	//			return;
	//		}
	//	}
	//}
	//queue1.push_back(i_dest_floor);
	Call p;

	for (int i = 0; i < queue.size() - 1; i++)
	{
		cout << i;
		/*if (queue[i].direction != queue[i + 1].direction && queue[i + 1].direction != 0 && queue[i].direction != 0)
		{
			p.floor = i_dest_floor;
			queue.insert(queue.begin() + i + 1, p);
			return;
		}*/
		if (past_direction == pass_direction && past_direction == 1) // едет вверх
		{
			if (queue[i].floor < i_dest_floor < queue[i + 1].floor )
			{
				p.floor = i_dest_floor;
				queue.insert(queue.begin() + i + 1, p);
				return;
			}
		}
		else if (past_direction == pass_direction && past_direction == -1 )
		{
			if (queue[i].floor > i_dest_floor > queue[i + 1].floor)
			{
				
				p.floor = i_dest_floor;
				queue.insert(queue.begin() + i + 1, p);
				return;
			}
		}
	}

	p.floor = i_dest_floor;
	queue.push_back(p);

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
	
	/*if (queue1.empty())
	{
		queue1.push_back(i_init_floor);
		return;
	}*/
	

	Call p;
	p.direction = pass_direction;
	if (queue.empty())
	{
		p.floor = i_init_floor;
		queue.push_back(p);
		return;
	}


	//for (int i = pointer; i < queue.size() - 1; i++)
	//{
	//	cout << "Зашел в цикл" << endl;
	//	cout << curr_direction << " " << pass_direction << endl;
	//	if (curr_direction == pass_direction && curr_direction == 1) // играет вверх
	//	{
	//		cout << "Зашел в условие проезда наверх" << endl;
	//		if (queue[i - 1] < i_init_floor < queue[i])
	//		{
	//			queue.insert(queue.begin() + i, i_init_floor);
	//			last_added_ind.insert(last_added_ind.begin(), i);
	//			return;
	//		}
	//	}
	//	else if (curr_direction == pass_direction && curr_direction == -1)
	//	{
	//		if (queue[i] > i_init_floor > queue[i + 1])
	//		{
	//			queue.insert(queue.begin() + i, i_init_floor);
	//			last_added_ind.insert(last_added_ind.begin(), i);
	//			return;
	//		}
	//	}
	//}

	
	//for (int i = 0; i < queue1.size() - 1; i++)
	//{
	//	if (curr_direction == pass_direction && curr_direction == 1 && i_init_floor > i_current_floor) // едет вверх
	//	{
	//		if (queue1[i] < i_init_floor < queue1[i + 1])
	//		{
	//			queue1.insert(queue1.begin() + i, i_init_floor);
	//			return;
	//		}
	//	} 
	//	else if (curr_direction == pass_direction && curr_direction == -1 && i_init_floor < i_current_floor)
	//	{
	//		if (queue1[i] > i_init_floor > queue1[i + 1])
	//		{
	//			queue1.insert(queue1.begin() + i, i_init_floor);
	//			return;
	//		}
	//	}
	//}

	//queue1.push_back(i_init_floor);
	

	for (int i = 0; i < queue.size() - 1; i++)
	{
		cout << i;
		if (curr_direction == pass_direction && curr_direction == 1 && i_init_floor > i_current_floor) // едет вверх
		{
			if (queue[i].floor < i_init_floor < queue[i + 1].floor)
			{
				
				p.floor = i_init_floor;
				queue.insert(queue.begin() + i, p);
				return;
			}
		}
		else if (curr_direction == pass_direction && curr_direction == -1 && i_init_floor < i_current_floor)
		{
			if (queue[i].floor > i_init_floor > queue[i + 1].floor)
			{
				
				p.floor = i_init_floor;
				queue.insert(queue.begin() + i, p);
				return;
			}
		}
	}
	
	p.floor = i_init_floor;
	queue.push_back(p);

	return;
}

void cl_manage::moving()
{
	/*if (queue1.empty())
	{
		queue1.push_back(1);
		moving();
	}
	else
	{
		if (i_current_floor < queue1[0])
			curr_direction = 1;
		else if (i_current_floor > queue1[0])
			curr_direction = -1;

		if (queue1[0] != i_current_floor)
		{
			i_current_floor += curr_direction;
		}
			
		else
		{
			past_direction = curr_direction;
			curr_direction = 0;
			stop();
			queue1.erase(queue1.begin());
		}

	}*/
	Call p;

	if (queue.empty())
	{
		p.floor = 1;
		queue.push_back(p);
		moving();
	}
	else
	{
		if (i_current_floor < queue[0].floor)
			curr_direction = 1;
		else if (i_current_floor > queue[0].floor)
			curr_direction = -1;

		if (queue[0].floor != i_current_floor)
		{
			i_current_floor += curr_direction;
		}

		else
		{
			past_direction = curr_direction;
			curr_direction = 0;
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
	return curr_direction;
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