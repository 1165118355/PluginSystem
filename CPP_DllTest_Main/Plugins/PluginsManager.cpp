#include "PluginsManager.h"
#include "Utils/UtilsString.h"
#include "Core/Event/EventMG.h"

#if defined(SPACE_DOUBLE)
#include <SpaceLog.h>
#endif

#ifdef _WIN64 || _WIN32
#include <Windows.h>
#elif _LINUX

#endif


std::shared_ptr<PluginsManager> PluginsManager::create()
{
    return std::shared_ptr<PluginsManager>(new PluginsManager());
}

void PluginsManager::init()
{

}

void PluginsManager::update()
{
    for(auto &i : m_PluginsList)
    {
        if(!i->hasEmitEvent())
        {
            auto event = i->getEmitEvent();
            EventMG::Instance()->emitEvent(event.first.c_str(), event.second);
        }
        if(!i->hasRegisterEvent())
        {
            auto event = i->getRegisterEvent();
            EventMG::Instance()->registeredEvent(event.first.c_str(), event.second);
        }
        i->update();
    }
}

void PluginsManager::shutdown()
{

}

PluginPtr PluginsManager::addPlugin(const char *pluginPath)
{
    std::string vers = "_x64";
#if defined(DEBUG)
    vers += "d";
#endif

    std::string stdpluginPath = std::string("Plugins/") + std::string(pluginPath) + vers + ".dll";

    Space::Log::message("load plugin %s\n", stdpluginPath.c_str());

    PluginPtr plugin = loadPlugin(stdpluginPath.c_str());
    if(plugin)
    {
        addPlugin(plugin);
    }
    else
    {
#if defined(SPACE_DOUBLE)
        Space::Log::error("load plugins lose \"%s\"\n", stdpluginPath.c_str());
#endif
    }
    return plugin;
}

void PluginsManager::addPlugin(PluginPtr plugin)
{
    plugin->init();
    m_PluginsList.push_back(plugin);
}

void PluginsManager::loadPlugins()
{
    this->addPlugin("RightPanel");
    this->addPlugin("LeftPanel");
    this->addPlugin("MaterialPanel");
    this->addPlugin("MenuPanel");

    for(auto &i : m_PluginsList)
    {
        while(!i->hasEmitEvent())
        {
            auto event = i->getEmitEvent();
            EventMG::Instance()->emitEvent(event.first.c_str(), event.second);
        }
        while(!i->hasRegisterEvent())
        {
            auto event = i->getRegisterEvent();
            EventMG::Instance()->registeredEvent(event.first.c_str(), event.second);
        }
    }
}

PluginPtr PluginsManager::loadPlugin(const char *pluginPath)
{
    PluginPtr plugin ;
    Plugin* (*createPlugin)() = nullptr;
#ifdef _WIN64 || _WIN32

    std::wstring wpluginPath = UtilsString::stringToWstring(pluginPath);
    HMODULE hDLL = LoadLibrary(wpluginPath.c_str());
    createPlugin = (Plugin *(*)())GetProcAddress(hDLL, "CreatePlugin");
#elif _LINUX

#endif

    if (createPlugin)
    {
        plugin = PluginPtr(createPlugin());
    }
    return plugin;
}

PluginsManager::PluginsManager()
{

}
