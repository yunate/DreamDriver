#ifndef timer_frame_res_provider_gif_h_
#define timer_frame_res_provider_gif_h_ 1

#include "base/g_def.h"
#include "i_timer_frame_res_provider.h"
#include "DogGif/DogGif.h"
#include <vector>

BEG_NSP_DDM

class timer_frame_res_provider_gif : public i_timer_frame_res_provider
{
public:
    /** 从文件初始化，调用者应该保证文件存在
    @param [in] fileFullPath 文件全路径（需要绝对路径）
    @return 是否成功
    */
    virtual bool init(const ddstr& fileFullPath) override;

    /** 获取时延（ms），该函数应当保证返回不为0
    @return 时延长短
    */
    virtual u32 get_time_delay() override;

    /** 获得下一帧
    @param [out] w 图片宽度
    @param [out] h 图片高度
    @return 位图数据，以【GBRA】形式存储，需要保证其大小大于等于w * h，失败返回nullptr
    @note 如果有下一帧的数据和上一帧仅仅部分变化而不需要绘制全部的时候，这里需要返回下一帧全部数据，而不是仅仅变化的部分
          如果下一帧数据长宽小于上一帧，需要居中或者，坐上对齐时候，请在内部计算好返回
    */
    virtual tf_color* get_next_frame(u32& w, u32& h) override;
    virtual tf_color* get_cur_frame(u32& w, u32& h) override;

    /** 设置空白背景颜色
    @param [in] bgColor 【GBRA】形式
    */
    virtual void set_bg_color(const tf_color& bgColor) override;

    /** 向前frameCnt帧，如果超出最大帧取最后一帧（快进）
    @param [in] frameCnt 帧数
    */
    virtual tf_color* forword_by_frame(u64 frameCnt, u32& w, u32& h) override;

    /** 向后frameCnt帧，如果超出最小帧取第一帧（快退）
    @param [in] frameCnt 帧数
    */
    virtual tf_color* backword_by_frame(u64 frameCnt, u32& w, u32& h) override;

protected:
    std::shared_ptr<DogGifNSP::DogGif> m_spGif;
    tf_frame_info m_curFrame;
};


END_NSP_DDM
#endif // timer_frame_res_provider_gif_h_


