#pragma once


// CLinkStatic

class CLinkStatic : public CStatic
{
public:
	CLinkStatic()
    {
        m_hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
    }

	virtual ~CLinkStatic()
    {
        if(m_hCursor != NULL)
        {
            DestroyCursor(m_hCursor);
            m_hCursor = NULL;
        }
    }

    void SetLink(LPCTSTR szLink)
    {
        m_strLink = szLink;
    }

    void Init()
    {
        ModifyStyle(0, SS_NOTIFY, 0);

        HFONT hFont = GetFont();

        LOGFONT LogFont = {0};
        ::GetObject(hFont, sizeof(LogFont), &LogFont);

        LogFont.lfUnderline = TRUE;
        m_Font.CreateFontIndirect(&LogFont);
        SetFont(m_Font);
    }

public:
    BEGIN_MSG_MAP(CLinkStatic)
        MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
        MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
        MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
    END_MSG_MAP()


    CString     m_strLink;
    HCURSOR     m_hCursor;
    CFont       m_Font;

    LRESULT OnSetCursor(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(m_hCursor != NULL)
        {
            ::SetCursor(m_hCursor);
            bHandled = TRUE;
            return TRUE;
        }

        bHandled = FALSE;
        return FALSE;
    }

    LRESULT OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        bHandled = FALSE;

        ::SetTextColor(reinterpret_cast<HDC>(wParam), RGB(0, 0, 255));
        ::SetBkMode(reinterpret_cast<HDC>(wParam), TRANSPARENT);
        return 0;
    }

    LRESULT OnLButtonUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
    {
        if(m_strLink.GetLength() > 0)
            ShellExecute(NULL, _T("open"), m_strLink, NULL, NULL, SW_SHOW);

        bHandled = TRUE;
        return 0;
    }
};


