#include "rshellbase.hpp"

bool Command::Operate()
{
	return this->connector->Operate(exeArgu->Operate());
}
