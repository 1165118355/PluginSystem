////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-05-11
//  brief:  xxx
//

#ifndef PLUGINSMANAGER_H
#define PLUGINSMANAGER_H
#include "Plugin/Plugin.h"
#include <shared_mutex>
#include <vector>

class PluginsManager
{
public:
    static std::shared_ptr<PluginsManager> create();

    /// \brief  基础生命周期
    virtual void init();
    virtual void update();
    virtual void shutdown();

    /// \brief
    PluginPtr addPlugin(const char *pluginPath);
    void addPlugin(PluginPtr plugin);

    void loadPlugins();
protected:
    PluginsManager();

    /// \brief
    virtual PluginPtr loadPlugin(const char *pluginPath);

protected:
    std::vector<PluginPtr> m_PluginsList;
};
typedef std::shared_ptr<PluginsManager> PluginsManagerPtr;

#endif // PLUGINSMANAGER_H
