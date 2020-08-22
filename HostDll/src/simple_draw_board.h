#ifndef simple_draw_board_h_
#define simple_draw_board_h_ 1

#include "base/g_def.h"
#include "souistd.h"
#include <windows.h>

using namespace SOUI;
BEG_NSP_DDM

// 简单画板类
class simple_draw_board : public SOUI::SWindow {
    SOUI_CLASS_NAME(simple_draw_board, L"simple_draw_board")

public:
    simple_draw_board();
    ~simple_draw_board();

    /** 从32位的位图数据初始化IBitmap
    @param    [in] nWid --  图片宽度
    @param    [in] nHei --  图片高度
    @param    [in] pBits --  位图数据,以ARGB形式存储
    Describe
    */
    void draw(int nWid, int nHei, const void* pBits);

protected:
    /**
    * OnPaint
    * @brief    窗口绘制消息响应函数
    * @param    IRenderTarget * pRT --  绘制目标
    * @return   void
    * Describe  注意这里的参数是IRenderTarget *,而不是WTL中使用的HDC，同时消息映射宏也变为MSG_WM_PAINT_EX
    */
    void on_paint(IRenderTarget* pRT);

    //SOUI控件消息映射表
    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(on_paint)    //窗口绘制消息
    SOUI_MSG_MAP_END()

protected:
    SAutoRefPtr<IBitmap> m_spBitmap;
};

END_NSP_DDM

#endif // simple_draw_board
