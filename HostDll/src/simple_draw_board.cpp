#include "simple_draw_board.h"

BEG_NSP_DDM

simple_draw_board::simple_draw_board()
{
    GETRENDERFACTORY->CreateBitmap((IBitmap**)&m_spBitmap);
}

simple_draw_board::~simple_draw_board()
{
}

void simple_draw_board::draw(int nWid, int nHei, const void* pBits)
{
    m_spBitmap->Init(nWid, nHei, (LPVOID)pBits);
    Invalidate();
}

void simple_draw_board::on_paint(IRenderTarget* pRT)
{
    // if (m_bEnableScale)
    // pRT->DrawBitmapEx(rcDraw, m_pCurFrameBmp, rcSrc, m_bTile ? EM_TILE : EM_STRETCH, byAlpha);
    // byAlpha
    __super::OnPaint(pRT);
    CRect rcSrc(0, 0, m_spBitmap->Width(), m_spBitmap->Height());

    if (rcSrc.Height() == 0 || rcSrc.Width() == 0) {
        return;
    }
    pRT->DrawBitmapEx(GetWindowRect(), m_spBitmap, rcSrc, EM_NULL);
}

END_NSP_DDM
