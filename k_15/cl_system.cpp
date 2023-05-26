#include "cl_system.h"

cl_system::cl_system(cl_base* p_head_object) : cl_base(p_head_object) // ����������� ������ cl_1 �������� ����������� �������� ������
{
};

void cl_system::build_tree_objects()
{
	this->set_name("system");					// ������������ ����� systemObject ��� ��������� �������

	// �������� �������� 
	cl_base* ob_input = new cl_input(this);		// �������� ������� �����
	cl_base* ob_manage = new cl_manage(this);	// �������� ������� ���������� �������
	cl_base* ob_cabin = new cl_cab(ob_manage);	// �������� ������� ������ �����
	cl_base* ob_output = new cl_output(this);	// �������� ������� ������
	set_all_state_on();							// ��������� ���� ��������
	
	// ��������� ����� ������� -> �������� ����������� ������ �����
	set_connection(SIGNAL_D(cl_system::signal_to_�hange_cab_capacity), ob_cabin, HANDLER_D(cl_cab::change_capacity));
	
	// ��������� ����� ������� -> ������ ����� �������
	set_connection(SIGNAL_D(cl_system::signal_to_read_command), ob_input, HANDLER_D(cl_input::read_command));				
	
	// ��������� ����� ������ ����� -> �������
	ob_input->set_connection(SIGNAL_D(cl_input::signal), this, HANDLER_D(cl_system::handler));								
	
	string command = "";

	// ���� ��� ��������� �������� ������ 
	while (true)
	{
		emit_signal(SIGNAL_D(cl_system::signal_to_read_command), command);
		if (current_command == "End of settings")
			break;

		stringstream ss(current_command);		// �������� ���������� ������ ��� �������
		int capacity;							// ���������� � ������� �������������� ������
		ss >> num_floors >> capacity;			// ���������� �������� ������ ���������� � ����
		command = to_string(capacity);			// ������� ��� ��������� ����������� ������ �����

		// ������ ������� �� ��������� ����������� ������ �����
		emit_signal(SIGNAL_D(cl_system::signal_to_�hange_cab_capacity), command);	

		// �������� �������� ������
		for (int i = 0; i < num_floors; i++)
		{
			string name = "floor_" + to_string(i + 1);		// ������������ ����� ��� ������� �����
			cl_base* p_floor = new cl_floor(this, name);	// �������� ������� �����
			p_floor->set_state(1);							// ��������� ������ �������

			// ��������� ����� �������� ������ -> ��������� ����������
			p_floor->set_connection(SIGNAL_D(cl_floor::signal_to_call_elevator), ob_manage, HANDLER_D(cl_manage::button_on_the_floor_has_been_pushed));
			// ��������� ����� �������� ������ -> ��������� ����������
			p_floor->set_connection(SIGNAL_D(cl_floor::signal_to_push_the_button_on_the_floor_again), ob_manage, HANDLER_D(cl_manage::button_on_the_floor_has_been_pushed_again));
		}
	}
	
	// ��������� ����� �������� ������ -> ������� ��������� ����������
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_load_passengers), this, HANDLER_D(cl_system::load_passengers));
	
	// ��������� ����� �������� ������ -> ������� ��������� ����������
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_unload_passengers), this, HANDLER_D(cl_system::unload_passengers));
	
	// ��������� ����� �������� ������ -> ������� 
	ob_manage->set_connection(SIGNAL_D(cl_manage::signal_to_system_handler), this, HANDLER_D(cl_system::handler));

	// ��������� ����� �������� ������ -> ������� 
	ob_cabin->set_connection(SIGNAL_D(cl_cab::signal_to_system_handler), this, HANDLER_D(cl_system::handler));
	
	// ��������� ����� ������ -> ����������  ��� ������� ������
	ob_cabin ->set_connection(SIGNAL_D(cl_cab::signal_to_push_the_button_in_cab), ob_manage, HANDLER_D(cl_manage::button_in_the_cab_has_been_pushed));
	
	// ���������� ����� ������� -> �����
	set_connection(SIGNAL_D(cl_system::signal_to_output), ob_manage, HANDLER_D(cl_output::console_output));

	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ��������
	set_connection(SIGNAL_D(cl_system::signal_for_elevator_movement), ob_manage, HANDLER_D(cl_manage::elevator_movement));

	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ���������� ���������� ����������
	set_connection(SIGNAL_D(cl_system::signal_to_increment_num_passengers), ob_manage, HANDLER_D(cl_manage::increment_num_passengers));
	
	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ���������� ���������� ����������
	set_connection(SIGNAL_D(cl_system::signal_to_decrement_num_passengers), ob_manage, HANDLER_D(cl_manage::decrement_num_passengers));

	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ���������� ���������� ����������
	set_connection(SIGNAL_D(cl_system::signal_to_get_current_floor), ob_manage, HANDLER_D(cl_manage::get_current_floor));

	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ���������� ���������� ����������
	set_connection(SIGNAL_D(cl_system::signal_to_get_num_passengers), ob_manage, HANDLER_D(cl_manage::get_num_passengers));

	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ��������� ����������� ��������
	set_connection(SIGNAL_D(cl_system::signal_to_get_direction), ob_manage, HANDLER_D(cl_manage::get_direction));
	
	// ���������� ����� ������� -> ������ ���������� ������� ����� ��� ��������� �����������
	set_connection(SIGNAL_D(cl_system::signal_to_get_capacity), ob_cabin, HANDLER_D(cl_cab::get_capacity));

	command = "Ready to work";
	
	// ������ ������� ������� ������ ��� ������ ���������  command
	emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
}


int cl_system::exec_app()
{
	int i_tact = 1;	// ���������� ��� �������� ������

	// ���� ��� ��������� �������� ������ 
	while (true)
	{
		// ������ ������� ������� ����� ��� ������
		string command = "";
		emit_signal(SIGNAL_D(cl_system::signal_to_read_command), command);	

		// ��������� �������
		if (current_command == "Turn off the system")						// ������� �� ���������� �������
		{
			command = "Turn off the system";								// ������������ ������� �� �����
			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);	// ������ ������� �� ������ ������
			return 0;
		}
		else if ((int)current_command.find("Passenger condition") != -1)				// ������� ������ ��������� ���������
		{
			string output;																// ���������� ���������� output ��� �������� ���������� ������
			string fio = current_command.substr(20);									// �������� �� ������ ��������� "passenger condition"

			cl_passenger* p_passenger = (cl_passenger*)find_object_from_root(fio);
			
			if (p_passenger == nullptr)													// ��������, ���� ��������� p_passenger ����� nullptr (������ ��������� ���)
			{
				output = "Passenger " + fio  + " not found";							// ������������ ��������� �� ������
				emit_signal(SIGNAL_D(cl_system::signal_to_output), output);
			}
			else if (p_passenger->get_state() == 1 or p_passenger->get_state() == 2)	// �������� ��������� ��������� �� �����
			{
				string floor = (p_passenger->get_head()->get_name()).substr(6);			// ���������� ��������� � ������� �����
				output = "Passenger condition: " + fio + " on the floor " + floor;		// ������������ ��������� � ��������� ��������� � �����, �� ������� �� ���������
				emit_signal(SIGNAL_D(cl_system::signal_to_output), output);
			}

			else if (p_passenger->get_state() == 3 or p_passenger->get_state() == 4)	// �������� ��������� ��������� � �����
			{
				output = "Passenger condition: " + fio + " in the elevator";			// ������������ ��������� � ��������� ��������� � �����
				emit_signal(SIGNAL_D(cl_system::signal_to_output), output);
			}
		}
		else if ((int)current_command.find("Passenger") != -1)			// ������� ������ ����� (������� ���������)
		{
			current_command = current_command.substr(10);				// �������� ����������� �����
			
			stringstream ss(current_command);							// �������� ������ �� ������ �������
			string f, io;												// ���������� � ������� �������������� ������
			int i_initial_floor, i_destination_floor;
			ss >> i_initial_floor >> i_destination_floor >> f >> io;	// ��������� ������ �� ������ � ������ � ����������
			
			string floor = "/floor_" + to_string(i_initial_floor);		// ������������ ���� � ������� �����
			cl_base* p_floor = get_object_pointer(floor);				// ��������� ��������� �� ������ �����, �� ������� ����� ������ ��������
			cl_passenger* pass_obj = new cl_passenger(p_floor);			// �������� ������� ��������� � �������� �������� ������
			
			pass_obj->set_name(f + " " + io);							// ������� ��� �������� 
			
			if (i_initial_floor < i_destination_floor)					// ��������� �� ������� ������� � ����������� � �� ��������� ����������� ��������
				pass_obj->set_state(1);									// �����
			else
				pass_obj->set_state(2);									// ����

			// ��������� ���������� ������ �������� -> �������
			set_connection(SIGNAL_D(cl_system::signal_to_set_init_dest_floor), pass_obj, HANDLER_D(cl_passenger::set_init_and_dest_floors));

			command = to_string(i_initial_floor) + " " + to_string(i_destination_floor);	// ������� ��� ��������� ���������� � �������� �����
			emit_signal(SIGNAL_D(cl_system::signal_to_set_init_dest_floor), command);		// ������ ������� ��� ��������� ���������� � �������� �����

			command = to_string(i_initial_floor) + " " + to_string(pass_obj->get_state());	// ������������ ������� ��� ������� ������ �� ����� (�� ����� ����� ������ � �����������)
			
			// todo ���������� �� ������ � ����������!
			p_floor->emit_signal(SIGNAL_D(cl_floor::signal_to_call_elevator), command);		// ������� ������ �� �����
			
			// �������� ���������� ������� � ���������
			delete_connection(SIGNAL_D(cl_system::signal_to_set_init_dest_floor), pass_obj, HANDLER_D(cl_passenger::set_init_and_dest_floors));
		}
		else if ((int)current_command.find("Elevator condition") != -1)			// ������� ��������� � ������ �����
		{
			cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");	// ��������� ��������� �� ������ ���������� �������
			
			int curr_direction = p_manage->get_state();
			
			emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
			string floor = current_command;							// ����� �������� ����� �����
			
			emit_signal(SIGNAL_D(cl_system::signal_to_get_num_passengers), command);
			string num_pass = current_command;

			if (curr_direction == 3)		// ����� �� ����� 
			{
				command = "Elevator condition: " + floor + " " + num_pass + " stop";
				emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			}
			else if (curr_direction == 1)	// ���� �����
			{
				command = "Elevator condition: " + floor + " " + num_pass + " direction up";
				emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			}
			else if (curr_direction == 2)	// ���� ����
			{
				command = "Elevator condition: " + floor + " " + num_pass + " direction down";
				emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			}

		}
		else if ((int)current_command.find("Condition on the floor") != -1)	// ������� ��������� �� �����
		{
			current_command = current_command.substr(23);					// �������� ����������� �����
			cl_base* p_floor = get_object_pointer("/floor_" + current_command);
			
			int floor = stoi(current_command);

			command = "Condition on the floor " + to_string(floor) + " -up-";
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 1)
					command += " " + p_pass->get_name();

			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
			
			command = "Condition on the floor " + to_string(floor) + " -down-";
			for (auto p_pass : p_floor->get_sub_objects())
				if (p_pass->get_state() == 2)
					command += " " + p_pass->get_name();
			
			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
		}
		else if (current_command == "System status")						// ������� ��������� �������
		{
			int up, down;
			cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");
			
			emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
			string floor = current_command;							// ����� �������� ����� �����

			emit_signal(SIGNAL_D(cl_system::signal_to_get_num_passengers), command);
			string num_pass = current_command;

			command = to_string(i_tact) + ": Elevator: " + floor + " " + num_pass + " Floors:";
			
			for (int i = 1; i <= num_floors; i++)
			{
				cl_base* p_floor = get_object_pointer("/floor_" + to_string(i));
				
				up = 0; down = 0;
				for (auto p_pass : p_floor->get_sub_objects())
					if (p_pass->get_state() == 1)
						up++;
				for (auto p_pass : p_floor->get_sub_objects())
					if (p_pass->get_state() == 2)
						down++;
				if ((up + down) != 0)
					command += " (" + to_string(i) + ": " + to_string(up) + "-" + to_string(down) + ")";
			}

			emit_signal(SIGNAL_D(cl_system::signal_to_output), command);
		}
		else if (current_command == "SHOWTREE")								// �������� ������ �������� ��������
		{
			print_tree_with_rns(0);
			return 0;
		}

		i_tact++; // ������� �� ����� ����
		
		// ������ ������� ������� ���������� ������� ��� �������� �����
		emit_signal(SIGNAL_D(cl_system::signal_for_elevator_movement), command);
	}

	return 0;
}


// ������ �����������

void cl_system::load_passengers(string s_message)
{
	string command;
	cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");									// ��������� ��������� �� ������ ���������� �������
	
	emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
	string curr_floor = current_command;

	emit_signal(SIGNAL_D(cl_system::signal_to_get_capacity), command);
	int capacity = stoi(current_command);

	emit_signal(SIGNAL_D(cl_system::signal_to_get_num_passengers), command);
	int num_passengers = stoi(current_command);
	
	cl_base* p_floor = get_object_pointer("/floor_" + curr_floor);
	cl_cab* p_cab = (cl_cab*) get_object_pointer("/manage/cabin");

	int n = p_floor->get_sub_objects().size();

	for (int i = 0; i < n; i++)
	{
		cl_passenger* p_pass = (cl_passenger*)p_floor->get_sub_objects()[0];
		
		if (num_passengers == capacity)
		{
			// todo ���������� �� ������ � ����������!
			p_floor->emit_signal(SIGNAL_D(cl_floor::signal_to_push_the_button_on_the_floor_again), curr_floor);
			return;
		}
		else
		{
			command = to_string(p_pass->get_destination_floor()) + " " + to_string(p_pass->get_state());
			p_pass->change_head_object(p_cab);

			emit_signal(SIGNAL_D(cl_system::signal_to_increment_num_passengers), command);

			// todo ���������� �� ������ � ����������!
			// ������ ������ � �����
			p_cab->emit_signal(SIGNAL_D(cl_cab::signal_to_push_the_button_in_cab), command);
		}	
	}
}

void cl_system::unload_passengers(string s_message)
{
	string command = "";
	cl_manage* p_manage = (cl_manage*)get_object_pointer("/manage");			// ��������� ��������� �� ������ ���������� �������
	
	emit_signal(SIGNAL_D(cl_system::signal_to_get_current_floor), command);
	
	cl_base* p_floor = get_object_pointer("/floor_" + current_command);
	cl_base* p_cab = get_object_pointer("/manage/cabin");
	
	int n = p_cab->get_sub_objects().size();
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		cl_passenger* p_pass = (cl_passenger*)p_cab->get_sub_objects()[j];
		
		if (p_pass->get_destination_floor() == stoi(current_command))
		{
			p_cab->delete_sub_object(p_pass->get_name());
			emit_signal(SIGNAL_D(cl_system::signal_to_decrement_num_passengers), command);
		}
		else j++;
	}
}

void cl_system::handler(string s_message)
{
	current_command = s_message;
}

// ������ �������

void cl_system::signal_to_read_command(string& s_message)
{
}

void cl_system::signal_to_�hange_cab_capacity(string& s_message)
{
}

void cl_system::signal_to_push_the_button_in_cab(string& s_message)
{
}

void cl_system::signal_to_push_button_on_the_floor(string& s_message)
{
}

void cl_system::signal_to_output(string& s_message)
{
}

void cl_system::signal_to_set_init_dest_floor(string& s_message)
{
}

void cl_system::signal_for_elevator_movement(string& s_message)
{
}

void cl_system::signal_to_increment_num_passengers(string& s_message)
{
}

void cl_system::signal_to_decrement_num_passengers(string& s_message)
{
}

void cl_system::signal_to_get_current_floor(string& s_message)
{
}

void cl_system::signal_to_get_num_passengers(string& s_message)
{
}

void cl_system::signal_to_get_direction(string& s_message)
{
}

void cl_system::signal_to_get_capacity(string& s_message)
{
}