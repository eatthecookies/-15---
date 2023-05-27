#include "cl_input.h"

cl_input::cl_input(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
}

// метод сигнала

void cl_input::signal(string& s_message) 
{
}

// методы обработчики

void cl_input::read_command(string s_message)
{
	string s_command;
	getline(cin, s_command);							// считать строку
	emit_signal(SIGNAL_D(cl_input::signal), s_command);	// отправить в обработчик системы
}

void cl_input::button_on_the_floor_has_been_pushed(string s_message)
{
}
