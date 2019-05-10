#include "rshellbase.hpp"

bool Connector::Operate(bool result)
{
	if (this->sign == ';') {
		return true;
	}
	else if (this->sign == '|') {
		if (result) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (this->sign == '&') {
		if (result) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (this->sign == '.') {
		return false;
	}
	return false;
};

char Connector::GetSign()
{
	return this->sign;
};
