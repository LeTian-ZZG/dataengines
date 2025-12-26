#include "justint16.h"
#include <QtEndian> // 用于处理大小端转换

// 构造函数
JustInt16::JustInt16()
{
}

// 析构函数
JustInt16::~JustInt16()
{
}

// 【核心逻辑】处理接收到的字节流
// 协议格式：AA BB [16个 int16] CC DD (共 36 字节)
void JustInt16::ProcessingDatas(char *data, int count)
{
    // 1. 清空上一帧的解析结果
    frame_list_.clear();

    // 2. 遍历缓冲区，寻找帧头 AA BB
    // count - 36 表示如果剩余数据不足 36 字节（一个完整包），就不读了，留给下次
    for (int i = 0; i <= count - 36; i++) {
        
        // 检查帧头: 0xAA 0xBB
        if ((unsigned char)data[i] == 0xAA && (unsigned char)data[i+1] == 0xBB) {
            
            // 检查帧尾: 0xCC 0xDD (位置在 i + 34)
            if ((unsigned char)data[i+34] == 0xCC && (unsigned char)data[i+35] == 0xDD) {
                
                // --- 找到完整一帧，开始解析 ---
                Frame frame;
                frame.start_index_ = i;       // 记录帧头位置
                frame.end_index_ = i + 36;    // 记录帧尾位置
                frame.is_valid_ = true;       // 标记有效
                frame.image_size_ = 0;        // 不是图片

                // 指针跳过帧头(2字节)，指向数据区
                const char* payload = data + i + 2;

                // 循环解析 16 个通道
                for (int ch = 0; ch < 16; ch++) {
                    // 读取 2 字节并组合成 int16
                    // qFromLittleEndian 确保在不同电脑上都能正确解析小端数据
                    int16_t raw_val = qFromLittleEndian<int16_t>(payload + (ch * 2));
                    
                    float real_val = 0.0f;

                    // --- 在这里乘系数 ---
                    if (ch < 8) {
                        // 前8路：电压 (±10V 量程示例)
                        real_val = (float)raw_val * 0.00030517f; 
                    } else {
                        // 后8路：电流
                        real_val = (float)raw_val * 0.001f;
                    }

                    // 添加到数据列表
                    frame.datas_.append(real_val);
                }

                // 将解析好的这一帧加入列表，Vofa+ 会拿去画图
                frame_list_.append(frame);

                // 跳过这 36 个字节，继续找下一帧
                i += 35; 
            }
        }
    }
}
