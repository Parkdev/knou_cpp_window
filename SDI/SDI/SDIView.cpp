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

// SDIView.cpp : CSDIView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "SDI.h"
#endif

#include "SDIDoc.h"
#include "SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//3. �ڵ� ���� ����
#define ID_DECREASE_BUTTON 3000
#define ID_INCREASE_BUTTON 3100
#define ID_LISTBOX 3200
#define ID_PROGBAR 3300


// CSDIView

IMPLEMENT_DYNCREATE(CSDIView, CView)

BEGIN_MESSAGE_MAP(CSDIView, CView) // �޼����� �޾Ƽ� ������ �Լ��� ����
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_DECREASE_BUTTON, OnDecreaseButton) // ���θ��� Ŀ�ǵ�(��ư)�� ���� �޼����� ��������
	ON_COMMAND(ID_INCREASE_BUTTON, OnIncreaseButton) // ������� �Լ����Ǹ� �ؾ� �������� ó��������
END_MESSAGE_MAP()

// CSDIView ����/�Ҹ�

CSDIView::CSDIView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CSDIView::~CSDIView()
{
}

BOOL CSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CSDIView �׸���

void CSDIView::OnDraw(CDC* /*pDC*/)
{
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CSDIView �μ�


void CSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSDIView ����

#ifdef _DEBUG
void CSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDoc* CSDIView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIView �޽��� ó����


int CSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	// CWND�� ��ӹ��� CChildWnd�� ��ӹ��� m_Wnd01���� create�� ���
	m_Wnd01.Create(AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW), //hredraw/vredraw ���μ��ο�������
		_T("ù ��° ���ϵ� ������"), //Ÿ��Ʋ�� �̸�
		WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CHILD, // ��ø������(�����⺻�ɼ�����)|�������� �ʿ����|���ϵ��������̴�
		CRect(50,50,300,200), // ��ǥ ũ��
		this, // �ڱ��� �θ�� this (CSDIView)
		1010); // ���ϵ������� ID
	m_Wnd02.Create(AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW),
		_T("�ι�° ���ϵ� ������"),
		WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CHILD,
		CRect(350,50,600,200),
		this,
		1020);
	
	m_Increase_Btn.Create(
		_T("����"), //��ư �̸�
		WS_VISIBLE, //�������� �ʿ����
		CRect(350,300,500,330), //��ǥ, ũ��
		this, // �θ� ������
		ID_INCREASE_BUTTON); // �ռ� ������ id
	m_Decrease_Btn.Create(_T("����"), WS_VISIBLE, CRect(350,350,500,380), this, ID_DECREASE_BUTTON);
	
	m_ListBox.Create(
		WS_DLGFRAME|WS_VISIBLE, //DLGFRAME �β��� ��輱�� ������ Ÿ��Ʋ �ٸ� ���� �� ����.//�����츦 �������ڸ��� ���
		CRect(50,300,300,500), //��ǥ
		this, ID_LISTBOX); //�θ�������� ID
	m_ListBox.AddString(_T("������ ���α׷���!")); //�̸����ǵ� ���� �Լ��� String(����) �߰� �Լ��� ����Ͽ� �������

	m_ProgressBar.Create(WS_DLGFRAME|WS_VISIBLE, CRect(50,230,300,270),this,ID_PROGBAR);
	m_ProgressBar.SetRange(0,10);
	m_ProgressBar.SetPos(1);
	return 0;
}

void CSDIView::OnDecreaseButton()
{
	int count = m_ListBox.GetCount();
	if(count> 0)
	{
		m_ListBox.DeleteString(count-1);
		m_ProgressBar.SetPos(count-1);
	}
	else
	{
		AfxMessageBox(_T("���� �������� �����ϴ�"));
	}
}

void CSDIView::OnIncreaseButton()
{
	int count = m_ListBox.GetCount();
	if(count < 10)
	{
		m_ListBox.AddString(_T("������ ���α׷���!"));
		m_ProgressBar.SetPos(count+1);
	}
	else
	{
		AfxMessageBox(_T("�� �̻� �߰��� �� �����ϴ�"));
	}
}