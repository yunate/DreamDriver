#include "timer_frame_drawer.h"
#include "DogGif/DogGif.h"
#include "file/file_reader.h"
#include "g_path.h"

BEG_NSP_DDM

timer_frame_drawer::timer_frame_drawer()
{
}

timer_frame_drawer::~timer_frame_drawer()
{
    pause();
    m_pDrawBoard = nullptr;
}

bool timer_frame_drawer::init(simple_draw_board* drawBoard, const sp_timer_frame_provider& provider)
{
    if (drawBoard == nullptr || provider == nullptr) {
        return false;
    }

    m_pDrawBoard = drawBoard;
    m_provider = provider;
    ddstr runPath = g_path::get_moudle_dir();

    if (!m_provider->init(runPath + _DDT("1.gif"))) {
        m_pDrawBoard = nullptr;
        m_provider.reset();
        return false;
    }

    m_timeDelay = m_provider->get_time_delay();
    return true;
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

    m_timeDelay = m_provider->get_time_delay();
    u32 w; 
    u32 h;
    auto data = m_provider->get_next_frame(w, h);
    m_pDrawBoard->draw(w, h, data);
}

END_NSP_DDM
