
#include "timer_frame_res_provider_gif.h"
#include "file/file_reader.h"

using namespace DogGifNSP;

BEG_NSP_DDM

bool timer_frame_res_provider_gif::init(const ddstr& fileFullPath)
{
    file_reader reader(fileFullPath);
    if (!reader.open(nullptr, 0))
    {
        return false;
    }

    u64 fileSize = reader.get_file_size();
    if (fileSize == 0) {
        return false;
    }

    u8* pBuff = new(std::nothrow) u8[fileSize];
    if (pBuff == nullptr) {
        return false;
    }

    reader.get_buff(pBuff, (u32)fileSize);
    m_spGif.reset(new(std::nothrow) DogGif());
    if (m_spGif == nullptr) {
        return false;
    }

    bool result = m_spGif->Init(pBuff, (u32)fileSize);
    delete[] pBuff;

    if (!result) {
        m_spGif.reset();
    }

    return result;
}

u32 timer_frame_res_provider_gif::get_time_delay()
{
    DD_ASSERT_FMTW(m_spGif != nullptr, _DDT("m_spGif is nullptr, is init failure?"));
    u32 timeDelay = m_spGif->GetTimeDelay();

    if (timeDelay == 0) {
        timeDelay = 66;
    }

    return timeDelay;
}

tf_color* timer_frame_res_provider_gif::get_next_frame(u32& w, u32& h)
{
    DD_ASSERT_FMTW(m_spGif != nullptr, _DDT("m_spGif is nullptr, is init failure?"));
    DogGifColor* pBuffData;
    u32 buffLen;
    if (!m_spGif->GetNextFrame(&pBuffData, buffLen)) {
        return nullptr;
    }

    m_curFrame.colorBuff.resize(buffLen);
    for (u32 i = 0; i < buffLen; ++i) {
        m_curFrame.colorBuff[i].r = pBuffData[i].m_r;
        m_curFrame.colorBuff[i].g = pBuffData[i].m_g;
        m_curFrame.colorBuff[i].b = pBuffData[i].m_b;
        m_curFrame.colorBuff[i].a = pBuffData[i].m_a;
    }
    m_curFrame.w = m_spGif->GetGolWidth();
    m_curFrame.h = m_spGif->GetGolHeight();
    w = m_curFrame.w;
    h = m_curFrame.h;
    return m_curFrame.colorBuff.data();
}

tf_color* timer_frame_res_provider_gif::get_cur_frame(u32& w, u32& h)
{
    DD_ASSERT_FMTW(m_spGif != nullptr, _DDT("m_spGif is nullptr, is init failure?"));
    
    if (m_curFrame.colorBuff.size() == 0) {
        get_next_frame(w, h);
    }

    w = m_curFrame.w;
    h = m_curFrame.h;
    return m_curFrame.colorBuff.data();
}

void timer_frame_res_provider_gif::set_bg_color(const tf_color& bgColor)
{
    bgColor;
}

tf_color* timer_frame_res_provider_gif::forword_by_frame(u64 frameCnt, u32& w, u32& h)
{
    if (frameCnt == 0) {
        return get_cur_frame(w, h);
    }

    DD_ASSERT_FMTW(m_spGif != nullptr, _DDT("m_spGif is nullptr, is init failure?"));
    u32 curFrameIndex = m_spGif->GetCurFrameIndex();
    u32 allCount = m_spGif->GetFrameCount();
    u32 desIndex = curFrameIndex;

    if (frameCnt > allCount - curFrameIndex) {
        desIndex = allCount - 1;
    } else {
        desIndex += (u32)frameCnt;
    }

    DogGifColor* pBuffData;
    u32 buffLen;
    for (u32 i = curFrameIndex; i < desIndex; ++i) {
        if (!m_spGif->GetNextFrame(&pBuffData, buffLen)) {
            return nullptr;
        }
    }

    return get_next_frame(w, h);
}

tf_color* timer_frame_res_provider_gif::backword_by_frame(u64 frameCnt, u32& w, u32& h)
{
    if (frameCnt == 0) {
        return get_cur_frame(w, h);
    }

    DD_ASSERT_FMTW(m_spGif != nullptr, _DDT("m_spGif is nullptr, is init failure?"));
    u32 curFrameIndex = m_spGif->GetCurFrameIndex();
    u32 allCount = m_spGif->GetFrameCount();
    u32 desIndex = curFrameIndex;

    if (frameCnt > curFrameIndex) {
        desIndex = 0;
    } else {
        desIndex -= (u32)frameCnt;
    }

    DogGifColor* pBuffData;
    u32 buffLen;
    for (u32 i = curFrameIndex; i < allCount; ++i) {
        if (!m_spGif->GetNextFrame(&pBuffData, buffLen)) {
            return nullptr;
        }
    }

    for (u32 i = 0; i < desIndex; ++i) {
        if (!m_spGif->GetNextFrame(&pBuffData, buffLen)) {
            return nullptr;
        }
    }

    return get_next_frame(w, h);
}

END_NSP_DDM
