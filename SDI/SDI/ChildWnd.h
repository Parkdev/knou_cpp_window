#pragma once


// CChildWnd

class CChildWnd : public CWnd
{
	DECLARE_DYNAMIC(CChildWnd) // 선언

public:
	CChildWnd();
	virtual ~CChildWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint(); // 함수 추가
};


