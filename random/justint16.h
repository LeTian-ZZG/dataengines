#ifndef JUSTINT16_H
#define JUSTINT16_H

#include <QObject>
#include <QtPlugin> // ✅ 必须显式引用
#include "dataengineinterface.h"

// =========================================================================
// 🚀 暴力修复：强制在这里声明接口，防止 MOC 在 include 文件里找不到
// 即使 dataengineinterface.h 里已经写了，这里再写一次也能确保 MOC 看见
// =========================================================================
Q_DECLARE_INTERFACE(DataEngineInterface, "VOFA+.Plugin.DataEngineInterface")


// 继承 Vofa+ 的数据引擎接口
class JustInt16 : public QObject, public DataEngineInterface
{
    Q_OBJECT
    Q_INTERFACES(DataEngineInterface)
    // 插件的唯一 ID
    Q_PLUGIN_METADATA(IID "VOFA+.Plugin.JustInt16")

public:
    explicit JustInt16();
    ~JustInt16();

    // 核心处理函数
    void ProcessingDatas(char *data, int count);
};

#endif // JUSTINT16_H
