////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-05-11
//  brief:  xxx
//

#ifndef _PLUGIN_H_
#define _PLUGIN_H_

#include <queue>
#include <shared_mutex>

namespace CallbackUtils
{
    class CallbackParmBase;
    class CallbackBase;
}

class Plugin
{
public:
    template<class T>
    std::shared_ptr<Plugin> cast(std::shared_ptr<T>content)
    {
        return std::dynamic_pointer_cast<Plugin>(content);
    }

    virtual ~Plugin() {}

    /// \brief  基本生命周期
    virtual void init()=0;
    virtual void update()=0;
    virtual void shutdown()=0;

    /// \brief  发送事件
    void emitEvent(const char *eventName, std::shared_ptr<CallbackUtils::CallbackParmBase> param)
    {
        m_EmitEventsQueue.push(std::pair<std::string, std::shared_ptr<CallbackUtils::CallbackParmBase>>(eventName, param));
    }
    std::pair<std::string, std::shared_ptr<CallbackUtils::CallbackParmBase>> getEmitEvent()
    {
        auto it = m_EmitEventsQueue.front();
        m_EmitEventsQueue.pop();
        return it;
    }
    bool hasEmitEvent()
    {
        return m_EmitEventsQueue.empty();
    }

    /// \brief  注册事件
    void registerEvent(const char *eventName, std::shared_ptr<CallbackUtils::CallbackBase> callback)
    {
        m_RegisterEventsQueue.push(std::pair<std::string, std::shared_ptr<CallbackUtils::CallbackBase>>(eventName, callback));
    }
    std::pair<std::string, std::shared_ptr<CallbackUtils::CallbackBase>> getRegisterEvent()
    {
        auto it = m_RegisterEventsQueue.front();
        m_RegisterEventsQueue.pop();
        return it;
    }
    bool hasRegisterEvent()
    {
        return m_RegisterEventsQueue.empty();
    }

protected:
    Plugin() {}
private:
    std::queue<std::pair<std::string, std::shared_ptr<CallbackUtils::CallbackParmBase>>> m_EmitEventsQueue;
    std::queue<std::pair<std::string, std::shared_ptr<CallbackUtils::CallbackBase>>> m_RegisterEventsQueue;
};
typedef std::shared_ptr<Plugin> PluginPtr;

#endif
