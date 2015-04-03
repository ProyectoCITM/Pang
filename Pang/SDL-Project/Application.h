#pragma once
#include "List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"

class Application
{
public:

	p2List<Module*> list_modules;  //  ((p2List)) it has to be linked with our List.h

public:

	Application()
	{
		ModuleDummy* pDummy = new ModuleDummy();
		
		AddModule(pDummy);
	}

	bool Init() 
	{ 
	
		p2List_item<Module*>* item = list_modules.start;

		while (item != NULL)
		{
			item->data->Init();
			item = item->next;
		}

		return true; 
	}

	int Update() { return UPDATE_STOP; }
	bool CleanUp() { return true; }

private:

	void AddModule(Module* mod)
	{
		list_modules.add(mod);
	}
};

