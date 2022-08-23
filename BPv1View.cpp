
// BPv1View.cpp: реализация класса CBPv1View
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "BPv1.h"
#endif

#include "BPv1Doc.h"
#include "BPv1View.h"
#include "ParamDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBPv1View

IMPLEMENT_DYNCREATE(CBPv1View, CView)

BEGIN_MESSAGE_MAP(CBPv1View, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBPv1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PARAMETERS, &CBPv1View::OnParameters)
END_MESSAGE_MAP()

// Создание или уничтожение CBPv1View

CBPv1View::CBPv1View() noexcept
{
	// TODO: добавьте код создания

}

CBPv1View::~CBPv1View()
{
}

BOOL CBPv1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CBPv1View

void CBPv1View::OnDraw(CDC* /*pDC*/)
{
	CBPv1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CBPv1View


void CBPv1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBPv1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CBPv1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CBPv1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

void CBPv1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBPv1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Диагностика CBPv1View

#ifdef _DEBUG
void CBPv1View::AssertValid() const
{
	CView::AssertValid();
}

void CBPv1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBPv1Doc* CBPv1View::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBPv1Doc)));
	return (CBPv1Doc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CBPv1View


void CBPv1View::OnParameters()
{
	ParamDlg d;
	d.box_num = 0;
	if (d.DoModal() == IDOK) {

		int check_result = d.check_freqs(d.m_method_type);

		
		CClientDC dc(this);
		/*
		CBrush brushBlue(RGB(0, 0, 255));
		CBrush* pOldBrush = dc.SelectObject(&brushBlue);

		// create and select a thick, black pen
		CPen penBlack;
		penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
		CPen* pOldPen = dc.SelectObject(&penBlack);

		// get our client rectangle
		CRect rect;
		GetClientRect(rect);

		// shrink our rect 20 pixels in each direction
		rect.DeflateRect(20, 20);

		// draw a thick black rectangle filled with blue
		dc.Rectangle(rect);

		// put back the old objects
		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);
		*/
		POINT a = { 10, 10 };
		POINT b = { 40, 40 };
		CRect rect1(a, b);
		CBrush brush(RGB(200, 10, 10));
		dc.FillRect(&rect1, &brush);

		
	}
	// TODO: добавьте свой код обработчика команд
}
