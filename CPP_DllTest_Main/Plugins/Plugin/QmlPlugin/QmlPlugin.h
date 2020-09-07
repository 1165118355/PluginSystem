////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-05-11
//  brief:  xxx
//

#ifndef QMLPLUGIN_H
#define QMLPLUGIN_H
#include "../Plugin.h"

class QQmlApplicationEngine;
class QQuickItem;
class QmlPlugin:public Plugin
{
public:
    static std::shared_ptr<QmlPlugin> cast(PluginPtr plugin)
    {
        return std::dynamic_pointer_cast<QmlPlugin>(plugin);
    }

    virtual ~QmlPlugin() {}

    virtual void init()=0;
    virtual void update()=0;
    virtual void shutdown()=0;

    ///////////////////////// 雨女无瓜 /////////////////////////
    void setQml(QQmlApplicationEngine *qmlEngine, QQuickItem *qmlRootItem){m_QmlEngine = qmlEngine; m_QmlRootItem = qmlRootItem;}
protected:
    QmlPlugin() {}

    void setQmlItem(void *qmlItem){m_QmlItem = qmlItem;}

protected:
    QQmlApplicationEngine *m_QmlEngine = nullptr;
    QQuickItem *m_QmlRootItem = nullptr;
private:
    void *m_QmlItem = nullptr;
};
typedef std::shared_ptr<QmlPlugin> QmlPluginPtr;


#endif // QMLPLUGIN_H
