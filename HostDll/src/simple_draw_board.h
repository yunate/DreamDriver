#ifndef simple_draw_board_h_
#define simple_draw_board_h_ 1

#include "base/g_def.h"
#include "souistd.h"
#include <windows.h>

using namespace SOUI;
BEG_NSP_DDM

// �򵥻�����
class simple_draw_board : public SOUI::SWindow {
    SOUI_CLASS_NAME(simple_draw_board, L"simple_draw_board")

public:
    simple_draw_board();
    ~simple_draw_board();

    /** ��32λ��λͼ���ݳ�ʼ��IBitmap
    @param    [in] nWid --  ͼƬ���
    @param    [in] nHei --  ͼƬ�߶�
    @param    [in] pBits --  λͼ����,��ARGB��ʽ�洢
    Describe
    */
    void draw(int nWid, int nHei, const void* pBits);

protected:
    /**
    * OnPaint
    * @brief    ���ڻ�����Ϣ��Ӧ����
    * @param    IRenderTarget * pRT --  ����Ŀ��
    * @return   void
    * Describe  ע������Ĳ�����IRenderTarget *,������WTL��ʹ�õ�HDC��ͬʱ��Ϣӳ���Ҳ��ΪMSG_WM_PAINT_EX
    */
    void on_paint(IRenderTarget* pRT);

    //SOUI�ؼ���Ϣӳ���
    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(on_paint)    //���ڻ�����Ϣ
    SOUI_MSG_MAP_END()

protected:
    SAutoRefPtr<IBitmap> m_spBitmap;
};

END_NSP_DDM

#endif // simple_draw_board
