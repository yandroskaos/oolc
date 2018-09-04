#include "conversion.h"
#include <stdexcept>

bool to_bool(const string& value)
{
    if(value == "true")
		return true;
	
    if(value == "false")
		return false;

	throw invalid_argument(value + " is not boolean!");
}

char to_char(const string& value)
{
	return value[0];
}

int to_int(const string& value)
{
    return stoi(value);
}

double to_real(const string& value)
{
    return stod(value);
}
