#include "cl_system.h"

cl_system::cl_system(cl_base* p_head_object) : cl_base(p_head_object) // ����������� ������ cl_1 �������� ����������� �������� ������
{
	set_object_class(1);
};


int cl_system::exec_app()
{

	// ���� ��� ��������� �������� ������
	while (true)
	{
		string command = "input";
		emit_signal(SIGNAL_D(cl_system::signal_meth), command);	// ������ ������� ������� ����� ��� ������

		if (current_command == "Turn off the system") // ���������� �������
		{
			return 0;
		}
		else if ((int)current_command.find("Passenger condition") != -1)	// ������� ��������� ���������
		{
			command = command.substr(21);
		}
		else if ((int)current_command.find("Passenger") != -1)				// ������� ������ �����
		{			
			current_command = current_command.substr(10);					// �������� ����������� �����

			stringstream ss(current_command);								// �������� ������ �� ������ �������
			string f, io;
			int i_initial_floor, i_destination_floor;

			ss >> i_initial_floor >> i_destination_floor >> f >> io;		// ��������� ������ �� ������

			string floor = "/floor_" + to_string(i_initial_floor);

			cl_base* pass_obj = new cl_passenger(get_object_pointer(floor));
			pass_obj->set_name(f + " " + io);
			pass_obj->set_state(1);
			 
		}
		else if ((int)current_command.find("Elevator condition") != -1)		// ������� ��������� � ������ �����
		{
			;
		}
		else if ((int)current_command.find("Condition on the floor") != -1)	// ������� ��������� �� �����
		{
			;
		}
		else if (current_command == "System condition")						// ������� ��������� �������
		{
			;
		}
		else if (current_command == "SHOWTREE")								// �������� ������ �������� ��������
		{
			print_tree_with_rns(0);
			return 0;
		}
	}
	return 0;
}


void cl_system::build_tree_objects()
{
	// -----------------------------------
	// ���������� ������ �������� ��������
	// -----------------------------------

	this->set_name("systemObject");				// ������������ ����� systemObject ��� ��������� �������

	cl_base* ob_input = new cl_input(this);		// �������� ������� �����
	cl_base* ob_manage = new cl_manage(this);	// �������� ������� ���������� �������
	cl_base* ob_cabin = new cl_cab(ob_manage);	// �������� ������� ������ �����
	cl_base* ob_output = new cl_output(this);	// �������� ������� ������

	set_all_state_on();							// ��������� ���� ��������


	set_connection(SIGNAL_D(cl_system::signal_meth), ob_cabin, HANDLER_D(cl_cab::handler_meth));		// ������� -> ������
	set_connection(SIGNAL_D(cl_system::signal_meth), ob_input, HANDLER_D(cl_input::handler_meth));		// ������� -> ����
	ob_input->set_connection(SIGNAL_D(cl_input::signal_meth), this, HANDLER_D(cl_system::handler_meth));// ���� -> �������

	string command = "startInput";
	emit_signal(SIGNAL_D(cl_system::signal_meth), command);	// ������ ������� ������� ����� ��� ������
	
	stringstream ss(current_command);
	int num_floors, capacity;

	ss >> num_floors >> capacity;

	command = "capacity: " + to_string(capacity);// ��������� ����������� ������ �����
	
	emit_signal(SIGNAL_D(cl_system::signal_meth), command);

	// �������� �������� ������
	for (int i = 0; i < num_floors; i++)
	{
		
		string name = "floor_" + to_string(i + 1);
		cl_base* obj = new cl_floor(this, name);
		obj->set_state(1);
		// ��������� ������ �������� � ������������ � ����� �������� ???
	}
		
	//1.3.��������� ������ �������� � ������������ ����� ���������
	


}


void cl_system::signal_meth(string& s_message)
{
}

void cl_system::handler_meth(string s_message)
{
	current_command = s_message;
}


