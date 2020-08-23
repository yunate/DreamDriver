#ifndef i_timer_frame_res_provider_h_
#define i_timer_frame_res_provider_h_ 1

#include "base\g_def.h"
#include "stream/i_ddstream.h"
#include <memory>

BEG_NSP_DDM

#pragma pack(push, 1)
// ��ʽ��ɫ
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
    /** ���ļ���ʼ����������Ӧ�ñ�֤�ļ�����
    @param [in] fileFullPath �ļ�ȫ·������Ҫ����·����
    @return �Ƿ�ɹ�
    */
    virtual bool init(const ddstr& fileFullPath)
    {
        fileFullPath;
        return false;
    }

    /** ���ڴ��ʼ����������Ӧ�ñ�֤buff��Ϊ�գ�����ʵ����Ӧ����������ڴ棬�����Ҫ�Ļ�
    @param [in] buff �ڴ��
    @param [in] buffLen �ڴ���С
    @return �Ƿ�ɹ�
    */
    virtual bool init(const void* buff, u32 buffLen)
    {
        buff;
        buffLen;
        return false;
    }

    /** ������ʼ����������Ӧ�ñ�֤stream��Ϊ�գ�����ʵ����Ӧ���������������Ҫ�Ļ�
    @param [in] stream ��
    @return �Ƿ�ɹ�
    */
    virtual bool init(const std::shared_ptr<i_ddstream>& stream)
    {
        stream;
        return false;
    }

    /** ���ÿհױ�����ɫ
    @param [in] bgColor ��GBRA����ʽ
    */
    virtual void set_bg_color(const tf_color& bgColor) = 0;

    /** ��ȡʱ�ӣ�ms�����ú���Ӧ����֤���ز�Ϊ0
    @return ʱ�ӳ���
    */
    virtual u32 get_time_delay() = 0;

    /** �����һ֡
    @param [out] w ͼƬ���
    @param [out] h ͼƬ�߶�
    @return λͼ���ݣ��ԡ�GBRA����ʽ�洢����Ҫ��֤���С���ڵ���w * h��ʧ�ܷ���nullptr
    @note �������һ֡�����ݺ���һ֡�������ֱ仯������Ҫ����ȫ����ʱ��������Ҫ������һ֡ȫ�����ݣ������ǽ����仯�Ĳ���
          �����һ֡���ݳ���С����һ֡����Ҫ���л��ߣ����϶���ʱ�������ڲ�����÷���
    */
    virtual tf_color* get_next_frame(u32& w, u32& h) = 0;

    // ��õ�ǰ֡���μ�get_next_frame
    virtual tf_color* get_cur_frame(u32& w, u32& h) = 0;

    /** ��ǰframeCnt֡������������֡ȡ���һ֡�������
    @param [in] frameCnt ֡��
    */
    virtual tf_color* forword_by_frame(u64 frameCnt, u32& w, u32& h) = 0;

    /** ���frameCnt֡�����������С֡ȡ��һ֡�����ˣ�
    @param [in] frameCnt ֡��
    */
    virtual tf_color* backword_by_frame(u64 frameCnt, u32& w, u32& h) = 0;

    /** ��ǰtime ���룬�������ȡ��󣨿����
    @param [in] time ����
    */
    virtual tf_color* forword_by_time(u64 time, u32& w, u32& h)
    {
        u32 timeDelay = get_time_delay();
        DD_ASSERT_FMTW(timeDelay != 0, _DDT("check time delay should not be 0"));
        return forword_by_frame(time / timeDelay, w, h);
    }

    /** ���time ���룬�������ȡ��ǰ�����ˣ�
    @param [in] time ����
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
