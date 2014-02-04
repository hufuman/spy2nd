#pragma once

namespace WndStyles
{
    BOOL GetStylesTitle(HWND hWnd, DWORD dwStyles, StringArray& arrTitles);
    BOOL GetExtendedStylesTitle(HWND hWnd, DWORD dwStyles, StringArray& arrTitles);

    BOOL GetClassStylesTitle(DWORD dwStyles, StringArray& arrTitles);
};
