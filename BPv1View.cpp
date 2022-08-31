
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
#include "HistogramDlg.h"

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
	ON_COMMAND(ID_HISTOGRAM, &CBPv1View::OnHistogram)
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

void CBPv1View::OnDraw(CDC* pDC)
{
	CBPv1Doc* doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных

	switch (doc->draw_mode) {
	case 0:
		break;
	case 1:
		draw_histogram(pDC);
	default:
		break;
	}
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

void CBPv1View::draw_rectangle(CDC* dc, int x1, int y1, int x2, int y2) {
	CBrush brushBlue(RGB(0, 0, 255));
	CBrush* pOldBrush = dc->SelectObject(&brushBlue);

	// create and select a thick, black pen
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = dc->SelectObject(&penBlack);

	// get our client rectangle
	POINT tmp1 = { x1, y1 }, tmp2 = {x2, y2};
	CRect rect(tmp1, tmp2);
	dc->Rectangle(rect);

	// put back the old objects
	dc->SelectObject(pOldBrush);
	dc->SelectObject(pOldPen);
}

void CBPv1View::draw_histogram(CDC* dc) {
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = dc->SelectObject(&penBlack);

	CRect rc;
	GetClientRect(&rc);
	int rc_width = rc.Width(), rc_height = rc.Height();

	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.95 * rc_width, 0.95 * rc_height);
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.05 * rc_width, 0.05 * rc_height);
	dc->SelectObject(pOldPen);
}

void CBPv1View::OnHistogram()
{
	CBPv1Doc* doc = GetDocument();
	HistogramDlg d;
	d.fill_values(doc);

	if (d.DoModal() == IDOK) {
		doc->draw_mode = 1;
		doc->sum_freqs_h0 = 0;
		for (int i = 0; i < d.box_num + 1; ++i) {
			doc->sum_freqs_h0 += d.abs_freqs[i];
		}

		doc->d0.set_parameters(d.values, d.abs_freqs, d.box_num + 1, doc->sum_freqs_h0);
		doc->method_type = d.m_method_type;
		doc->sample_size = d.m_sample_size;
		if (doc->s)
			doc->s->set_parameters(doc->d0);
		else {
			switch (doc->method_type) {
			case 0:
				doc->s = new PrimitiveSample(doc->d0, doc->sum_freqs_h0);
				break;
			case 1:
				doc->s = new ChenSample(doc->d0);
			}
		}
		doc->s->simulate(doc->sample_size);
		doc->chi2histogram.SetData(*doc->s, doc->d0);

		doc->UpdateAllViews(0);
	}
	// TODO: добавьте свой код обработчика команд
}

