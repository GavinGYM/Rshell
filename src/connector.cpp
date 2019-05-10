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

bool Semicolon::Operate(bool result)
{
	// The "Semicolon" class
	return true;
}

bool End::Operate(bool result)
{
	return false;
}

bool Or::Operate(bool result)
{
	// The "Or" class
	if (result) {
		return false;
	}
	else {
		return true;
	}
}

bool And::Operate(bool result)
{
	// The "And" class
	if (result) {
		return true;
	}
	else {
		return false;
	}
}
