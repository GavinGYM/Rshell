#include "rshellbase.hpp"

bool Connector::Operate(bool result)
{
	return false;
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
