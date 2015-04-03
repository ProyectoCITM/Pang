#pragma once
#include "Module.h"
#include "Globals.h"

class ModuleDummy : public Module
{
	bool Init()
	{
		LOG("\nDummy Init");
		return true;
	}

	bool CleanUp()
	{
		LOG("\nDummy CleanUp");
		return true;
	}
};