#include "rshellbase.hpp"

bool ExeArgu::Operate()
{
	if (1) {//Execute the command by passing the string exe and string argu
		return true;
	}
	else {
		return false;
	}
}

string ExeArgu::getExe()
{
	return this->exe;
}

string ExeArgu::getArgu()
{
	return this->argu;
}
