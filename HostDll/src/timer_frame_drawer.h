
#ifndef timer_frame_drawer_h_
#define timer_frame_drawer_h_ 1
#include "simple_draw_board.h"

#include <memory>
using namespace SOUI;
BEG_NSP_DDM

// 按帧画bitmap到画板上去 类
class timer_frame_drawer : public ITimelineHandler {
public:
    timer_frame_drawer();
    ~timer_frame_drawer();

    void init(simple_draw_board* drawBoard);

    void start();
    void pause();


private:
    virtual void OnNextFrame() override;

protected:
    simple_draw_board* m_pDrawBoard = nullptr;
    s32 m_timeDelay = 60;
};


using sp_timer_frame_drawer = std::shared_ptr<timer_frame_drawer>;
END_NSP_DDM

#endif // timer_frame_drawer_h_

