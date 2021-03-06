
#ifndef main_dlg_h_
#define main_dlg_h_ 1

#include "base\g_def.h"
#include "souistd.h"
#include "timer_frame_drawer.h"
#include "timer_frame_res_provider_gif.h"

#include <memory>

BEG_NSP_DDM
using namespace SOUI;

// MainWnd.h : interface of the CMainWnd class
//
class CMainWnd : public SHostWnd
{
public:
    CMainWnd()
        : SHostWnd(_T("LAYOUT:XML_MAINWND"))//这里定义主界面需要使用的布局文件
    {
        m_bLayoutInited = FALSE;
        m_spTimerFrameDrawer.reset(new timer_frame_drawer());

    }

    void OnClose()
    {
        m_spTimerFrameDrawer.reset();
        PostMessage(WM_QUIT);
    }
    void OnMaximize()
    {
        SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
    }
    void OnRestore()
    {
        SendMessage(WM_SYSCOMMAND, SC_RESTORE);
    }
    void OnMinimize()
    {
        SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
    }

    void OnSize(UINT nType, CSize size)
    {
        SetMsgHandled(FALSE);
        if (!m_bLayoutInited) return;
        if (nType == SIZE_MAXIMIZED)
        {
            FindChildByName(L"btn_restore")->SetVisible(TRUE);
            FindChildByName(L"btn_max")->SetVisible(FALSE);
        }
        else if (nType == SIZE_RESTORED)
        {
            FindChildByName(L"btn_restore")->SetVisible(FALSE);
            FindChildByName(L"btn_max")->SetVisible(TRUE);
        }
    }
    void OnBtnMsgBox()
    {
        simple_draw_board* drawBoard = (simple_draw_board*)FindChildByName("player");

        sp_timer_frame_provider spProvider(new timer_frame_res_provider_gif());
        m_spTimerFrameDrawer->init(drawBoard, spProvider);
        m_spTimerFrameDrawer->start();
        return;
        // 
        SMessageBox(NULL, _T("this is a message box"), _T("haha"), MB_OK | MB_ICONEXCLAMATION);
        SMessageBox(NULL, _T("this message box includes two buttons"), _T("haha"), MB_YESNO | MB_ICONQUESTION);
        SMessageBox(NULL, _T("this message box includes three buttons"), NULL, MB_ABORTRETRYIGNORE);
    }

    BOOL OnInitDialog(HWND hWnd, LPARAM lParam)
    {
        m_bLayoutInited = TRUE;

        return 0;
    }
protected:
    //按钮事件处理映射表
    EVENT_MAP_BEGIN()
        EVENT_NAME_COMMAND(L"btn_close", OnClose)
        EVENT_NAME_COMMAND(L"btn_min", OnMinimize)
        EVENT_NAME_COMMAND(L"btn_max", OnMaximize)
        EVENT_NAME_COMMAND(L"btn_restore", OnRestore)
        EVENT_NAME_COMMAND(L"btn_msgbox", OnBtnMsgBox)
    EVENT_MAP_END()

        //窗口消息处理映射表
    BEGIN_MSG_MAP_EX(CMainWnd)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_CLOSE(OnClose)
        MSG_WM_SIZE(OnSize)
        CHAIN_MSG_MAP(SHostWnd)//注意将没有处理的消息交给基类处理
        REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
private:
    BOOL            m_bLayoutInited;
    sp_timer_frame_drawer m_spTimerFrameDrawer;
};
END_NSP_DDM
#endif // main_dlg_h_

