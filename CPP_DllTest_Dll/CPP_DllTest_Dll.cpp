
#include <stdio.h>
#include "CPP_DllTest_Dll.h"

DllTest::DllTest()
{
}

DllTest::~DllTest()
{
}

void DllTest::init()
{
	printf("plugin init\n");
}

void DllTest::update()
{
	printf("plugin update\n");
}

void DllTest::shutdown()
{
	printf("plugin shutdown\n");
}



extern "C" _declspec(dllexport) void *CreatePlugin() {
	printf("call create plugin \n");
	return new DllTest();
}

extern "C" _declspec(dllexport) void ReleasePlugin(void *plugin) {
	delete static_cast<DllTest*>(plugin);
}