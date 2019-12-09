#include <stdlib.h>
#include <string>
#include "Plugin.h"
#include "Utils\StringUtils.h"

#ifdef _WIN64 || _WIN32
#include <Windows.h>
#elif _LINUX 

#endif


Plugin *loadPlugin(const char *pluginPath)
{
	Plugin * plugin = nullptr;
	Plugin* (*createPlugin)() = nullptr;
#ifdef _WIN64 || _WIN32

	std::wstring wpluginPath = StringUtils::stringToWstring(pluginPath);
	HMODULE hDLL = LoadLibrary(wpluginPath.c_str());
	createPlugin = (Plugin *(*)())GetProcAddress(hDLL, "CreatePlugin");
#elif _LINUX 

#endif

	if (createPlugin)
	{
		plugin = createPlugin();
	}
	return plugin;
}

int main()
{
	Plugin *plugin = loadPlugin("CPP_DllTest_Dll.dll");
	if (plugin)
	{
		plugin->init();
	}
	return 0;
}