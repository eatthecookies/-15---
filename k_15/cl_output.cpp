#include "cl_output.h"

cl_output::cl_output(cl_base* p_head_object, string s_name) : cl_base(p_head_object, s_name) // конструктор класса cl_2 вызывает конструктор базового класса
{
}

// метод обработчик

void cl_output::console_output(string s_message)
{
	cout << s_message;
}
