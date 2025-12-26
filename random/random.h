#ifndef JUSTINT16_H
#define JUSTINT16_H

#include "dataengineinterface.h"

// 继承 Vofa+ 的数据引擎接口
class JustInt16 : public QObject, public DataEngineInterface
{
    Q_OBJECT
    Q_INTERFACES(DataEngineInterface)
    // 【关键】插件的唯一 ID，Vofa+ 靠这个识别插件
    Q_PLUGIN_METADATA(IID "VOFA+.Plugin.JustInt16")

public:
    explicit JustInt16();
    ~JustInt16();

    // 这是核心处理函数，Vofa+ 会把收到的数据扔进来
    void ProcessingDatas(char *data, int count);
};

#endif // JUSTINT16_H
