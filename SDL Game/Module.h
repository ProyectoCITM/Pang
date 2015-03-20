#pragma once

class Application;

class Module
{
public:
	Application* App;

	Module(Application* parent) : App(parent)
	{
	}

	virtual bool Init() 
	{
		return true; 
	}

	// TODO: Crear un nou metode que es cridi una vegada  per tots el moduls despres del Init pero abans del update "Start()"

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}
};