// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// SDIView.h : CSDIView Ŭ������ �������̽�
//

#pragma once

#include "ChildWnd.h" // 1. CWND�κ��� ���; ���ϵ�������Ŭ���� ����


class CSDIView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSDIView();
	DECLARE_DYNCREATE(CSDIView)

// Ư���Դϴ�.
public:
	CSDIDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CChildWnd m_Wnd01; // 1. ���ο� ��ü�� ����
	CChildWnd m_Wnd02; // 2. �߰� ��ü ����

	CButton m_Decrease_Btn; // 3. ���ҹ�ư ����
	CButton	m_Increase_Btn; // 3. ������ư ����

	CListBox m_ListBox; // 4. ����Ʈ �ڽ� ����

	CProgressCtrl m_ProgressBar; // 5. ����� ����

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDecreaseButton(); // 6. �� �Լ������ ������Ͽ��� �̸� �����ؾ���
	afx_msg void OnIncreaseButton(); // 6. ��������
};

#ifndef _DEBUG  // SDIView.cpp�� ����� ����
inline CSDIDoc* CSDIView::GetDocument() const
   { return reinterpret_cast<CSDIDoc*>(m_pDocument); }
#endif
