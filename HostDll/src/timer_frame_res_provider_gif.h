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
    /** ���ļ���ʼ����������Ӧ�ñ�֤�ļ�����
    @param [in] fileFullPath �ļ�ȫ·������Ҫ����·����
    @return �Ƿ�ɹ�
    */
    virtual bool init(const ddstr& fileFullPath) override;

    /** ��ȡʱ�ӣ�ms�����ú���Ӧ����֤���ز�Ϊ0
    @return ʱ�ӳ���
    */
    virtual u32 get_time_delay() override;

    /** �����һ֡
    @param [out] w ͼƬ���
    @param [out] h ͼƬ�߶�
    @return λͼ���ݣ��ԡ�GBRA����ʽ�洢����Ҫ��֤���С���ڵ���w * h��ʧ�ܷ���nullptr
    @note �������һ֡�����ݺ���һ֡�������ֱ仯������Ҫ����ȫ����ʱ��������Ҫ������һ֡ȫ�����ݣ������ǽ����仯�Ĳ���
          �����һ֡���ݳ���С����һ֡����Ҫ���л��ߣ����϶���ʱ�������ڲ�����÷���
    */
    virtual tf_color* get_next_frame(u32& w, u32& h) override;
    virtual tf_color* get_cur_frame(u32& w, u32& h) override;

    /** ���ÿհױ�����ɫ
    @param [in] bgColor ��GBRA����ʽ
    */
    virtual void set_bg_color(const tf_color& bgColor) override;

    /** ��ǰframeCnt֡������������֡ȡ���һ֡�������
    @param [in] frameCnt ֡��
    */
    virtual tf_color* forword_by_frame(u64 frameCnt, u32& w, u32& h) override;

    /** ���frameCnt֡�����������С֡ȡ��һ֡�����ˣ�
    @param [in] frameCnt ֡��
    */
    virtual tf_color* backword_by_frame(u64 frameCnt, u32& w, u32& h) override;

protected:
    std::shared_ptr<DogGifNSP::DogGif> m_spGif;
    tf_frame_info m_curFrame;
};


END_NSP_DDM
#endif // timer_frame_res_provider_gif_h_


