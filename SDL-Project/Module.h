#pragma once

class Module
{
public:

	virtual bool Init() { return true; }
	virtual int Update() { return 2; }
	virtual bool CleanUp() { return true; }
};