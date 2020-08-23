#ifndef i_timer_frame_res_provider_h_
#define i_timer_frame_res_provider_h_ 1

#include "base\g_def.h"
#include "stream/i_ddstream.h"
#include <memory>

BEG_NSP_DDM

#pragma pack(push, 1)
// 格式颜色
struct timer_frame_color {
    u8 b = 0;
    u8 g = 0;
    u8 r = 0;
    u8 a = 0xff;
};
using tf_color = timer_frame_color;

struct tf_frame_info {
    u32 w = 0;
    u32 h = 0;
    std::vector<tf_color> colorBuff;
};
#pragma pack(pop)

class i_timer_frame_res_provider {
public:
    /** 从文件初始化，调用者应该保证文件存在
    @param [in] fileFullPath 文件全路径（需要绝对路径）
    @return 是否成功
    */
    virtual bool init(const ddstr& fileFullPath)
    {
        fileFullPath;
        return false;
    }

    /** 从内存初始化，调用者应该保证buff不为空，函数实现者应当拷贝这份内存，如果需要的话
    @param [in] buff 内存块
    @param [in] buffLen 内存块大小
    @return 是否成功
    */
    virtual bool init(const void* buff, u32 buffLen)
    {
        buff;
        buffLen;
        return false;
    }

    /** 从流初始化，调用者应该保证stream不为空，函数实现者应当保存流，如果需要的话
    @param [in] stream 流
    @return 是否成功
    */
    virtual bool init(const std::shared_ptr<i_ddstream>& stream)
    {
        stream;
        return false;
    }

    /** 设置空白背景颜色
    @param [in] bgColor 【GBRA】形式
    */
    virtual void set_bg_color(const tf_color& bgColor) = 0;

    /** 获取时延（ms），该函数应当保证返回不为0
    @return 时延长短
    */
    virtual u32 get_time_delay() = 0;

    /** 获得下一帧
    @param [out] w 图片宽度
    @param [out] h 图片高度
    @return 位图数据，以【GBRA】形式存储，需要保证其大小大于等于w * h，失败返回nullptr
    @note 如果有下一帧的数据和上一帧仅仅部分变化而不需要绘制全部的时候，这里需要返回下一帧全部数据，而不是仅仅变化的部分
          如果下一帧数据长宽小于上一帧，需要居中或者，坐上对齐时候，请在内部计算好返回
    */
    virtual tf_color* get_next_frame(u32& w, u32& h) = 0;

    // 获得当前帧，参见get_next_frame
    virtual tf_color* get_cur_frame(u32& w, u32& h) = 0;

    /** 向前frameCnt帧，如果超出最大帧取最后一帧（快进）
    @param [in] frameCnt 帧数
    */
    virtual tf_color* forword_by_frame(u64 frameCnt, u32& w, u32& h) = 0;

    /** 向后frameCnt帧，如果超出最小帧取第一帧（快退）
    @param [in] frameCnt 帧数
    */
    virtual tf_color* backword_by_frame(u64 frameCnt, u32& w, u32& h) = 0;

    /** 向前time 毫秒，如果超出取最后（快进）
    @param [in] time 毫秒
    */
    virtual tf_color* forword_by_time(u64 time, u32& w, u32& h)
    {
        u32 timeDelay = get_time_delay();
        DD_ASSERT_FMTW(timeDelay != 0, _DDT("check time delay should not be 0"));
        return forword_by_frame(time / timeDelay, w, h);
    }

    /** 向后time 毫秒，如果超出取最前（快退）
    @param [in] time 毫秒
    */
    virtual tf_color* backword_by_time(u64 time, u32& w, u32& h)
    {
        u32 timeDelay = get_time_delay();
        DD_ASSERT_FMTW(timeDelay != 0, _DDT("check time delay should not be 0"));
        return backword_by_frame(time / timeDelay, w, h);
    }
};

using sp_timer_frame_provider = std::shared_ptr<i_timer_frame_res_provider>;
END_NSP_DDM
#endif // i_timer_frame_res_provider_h_
