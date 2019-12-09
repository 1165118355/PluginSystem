#pragma once
class Plugin
{
public:
	Plugin() {}
	virtual ~Plugin() {}

	virtual void init()=0;
	virtual void update()=0;
	virtual void shutdown()=0;
};

