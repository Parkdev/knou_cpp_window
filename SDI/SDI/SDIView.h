// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// SDIView.h : CSDIView 클래스의 인터페이스
//

#pragma once

#include "ChildWnd.h" // 1. CWND로부터 상속; 차일드윈도우클래스 포함


class CSDIView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSDIView();
	DECLARE_DYNCREATE(CSDIView)

// 특성입니다.
public:
	CSDIDoc* GetDocument() const;

// 작업입니다.
public:
	CChildWnd m_Wnd01; // 1. 새로운 객체를 생성
	CChildWnd m_Wnd02; // 2. 추가 객체 생성

	CButton m_Decrease_Btn; // 3. 감소버튼 생성
	CButton	m_Increase_Btn; // 3. 증가버튼 생성

	CListBox m_ListBox; // 4. 리스트 박스 생성

	CProgressCtrl m_ProgressBar; // 5. 진행바 생성

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDecreaseButton(); // 6. 새 함수기능은 헤더파일에서 미리 정의해야함
	afx_msg void OnIncreaseButton(); // 6. 마찬가지
};

#ifndef _DEBUG  // SDIView.cpp의 디버그 버전
inline CSDIDoc* CSDIView::GetDocument() const
   { return reinterpret_cast<CSDIDoc*>(m_pDocument); }
#endif

