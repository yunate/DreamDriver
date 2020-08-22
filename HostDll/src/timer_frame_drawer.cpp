#include "timer_frame_drawer.h"
#include "DogGif/DogGif.h"
#include "file/file_reader.h"
#include "g_path.h"

using namespace DogGifNSP;
BEG_NSP_DDM

// TODO: 待删除，测试gif，以后抽象层接口供视频、gif等播放
DogGif* g_dogGif;

timer_frame_drawer::timer_frame_drawer()
{
}

timer_frame_drawer::~timer_frame_drawer()
{
    pause();
    m_pDrawBoard = nullptr;
}

void timer_frame_drawer::init(simple_draw_board* drawBoard)
{
    m_pDrawBoard = drawBoard;

    g_dogGif = new DogGif();
    ddstr runPath = g_path::get_moudle_dir();
    file_reader reader(runPath + _DDT("1.gif"));

    if (!reader.open(nullptr, 0))
    {
        return;
    }

    size_t fileSize = reader.get_file_size();

    if (fileSize > 0)
    {
        u8* pBuff = new u8[fileSize];
        reader.get_buff(pBuff, (u32)fileSize);
        g_dogGif->Init(pBuff, (u32)fileSize);
        delete[] pBuff;
    }

    m_timeDelay = g_dogGif->GetTimeDelay();
}

void timer_frame_drawer::start()
{
    DD_ASSERT_FMTW(m_pDrawBoard != nullptr, L"please set a draw board\r\n");
    if (m_pDrawBoard != nullptr) {
        m_pDrawBoard->GetContainer()->RegisterTimelineHandler(this);
    }
}

void timer_frame_drawer::pause()
{
    DD_ASSERT_FMTW(m_pDrawBoard != nullptr, L"please set a draw board\r\n");
    if (m_pDrawBoard != nullptr) {
        m_pDrawBoard->GetContainer()->UnregisterTimelineHandler(this);
    }
}

void timer_frame_drawer::OnNextFrame()
{
    DD_ASSERT_FMTW(m_pDrawBoard != nullptr, L"please set a draw board\r\n");
    if (m_pDrawBoard == nullptr) {
        return;
    }

    // 先减10，以后换成更加精确的，抽象到接口类中的should draw
    m_timeDelay -= 10;

    if (m_timeDelay > 0) {
        return;
    }

    m_timeDelay = g_dogGif->GetTimeDelay();

    DogGifColor* pBuffData;
    u32 buffLen;
    if (!g_dogGif->GetNextFrame(&pBuffData, buffLen)) {
        return;
    }

    for (u32 i = 0; i < buffLen; ++i) {
        DogGifColor tmp = pBuffData[i];
        pBuffData[i].m_b = tmp.m_r;
        pBuffData[i].m_g = tmp.m_g;
        pBuffData[i].m_r = tmp.m_b;
        pBuffData[i].m_a = tmp.m_a;
    }

    m_pDrawBoard->draw(g_dogGif->GetGolWidth(), g_dogGif->GetGolHeight(), pBuffData);
}

END_NSP_DDM
