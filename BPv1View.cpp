
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
#include "PvalueDlg.h"

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
	ON_COMMAND(ID_PVALUE, &CBPv1View::OnPvalue)
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
	case 2:
		draw_pvalue_plot(pDC);
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

void CBPv1View::draw_rectangle(CDC* dc, int x1, int y1, int x2, int y2, int mode) {
	//mode - 0 for theoretical bar, 1 for empirical bar, 2 for white rectangle (for legend)
	COLORREF bar_color;
	if (mode == 0)
		bar_color = RGB(0, 0, 255);
	else if (mode == 1)
		bar_color = RGB(255, 0, 0);
	else if (mode == 2)
		bar_color = RGB(0, 0, 0);
	CBrush brush(bar_color);
	CBrush* pOldBrush = dc->SelectObject(&brush);

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
	CBPv1Doc* doc = GetDocument();
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = dc->SelectObject(&penBlack);

	CRect rc;
	GetClientRect(&rc);
	int rc_width = rc.Width(), rc_height = rc.Height();

	//Axis separator
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.03 * rc_width, 0.97 * rc_height);

	//Values axis
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.95 * rc_width, 0.95 * rc_height);

	//Frequencies axis
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.05 * rc_width, 0.05 * rc_height);

	//0 for frequency axis
	dc->TextOut(0.05 * rc_width - 16, 0.95 * rc_height - 14, L"0");

	double max_mark;
	if (doc->chi2histogram.get_size() == 1)
		max_mark = 0.55;
	else
		max_mark = 0.8;

	//Max value mark
	dc->MoveTo(max_mark * rc_width, 0.95 * rc_height - 4);
	dc->LineTo(max_mark * rc_width, 0.95 * rc_height + 4);
	CString tmp;
	tmp.Format(L"%g", doc->chi2histogram.hist_max_value);
	dc->TextOut(max_mark * rc_width - 4, 0.95 * rc_height + 8, tmp);

	//Max frequency mark
	dc->MoveTo(0.05 * rc_width - 4, int(0.2 * rc_height) + 1);
	dc->LineTo(0.05 * rc_width + 4, int(0.2 * rc_height) + 1);
	tmp.Format(L"%d", doc->chi2histogram.hist_max_freq);
	dc->TextOut(0.05 * rc_width - 5 - (long long)tmp.GetLength() * 8, int(0.2 * rc_height) - 6, tmp);

	double prop = ((max_mark - 0.05) * rc_width) / (doc->chi2histogram.hist_max_value - doc->chi2histogram.hist_min_value
		+ doc->chi2histogram.hist_min_dif_module / 2); // Scale (values -> pixels)
	double shift = min(doc->chi2histogram.hist_min_dif_module / 2 * prop, 0.15 * rc_width); // Half of theoretical bar width

	//Min value mark
	dc->MoveTo(int((doc->chi2histogram.hist_min_dif_module / 2) * prop + 0.05 * rc_width), 0.95 * rc_height - 4);
	dc->LineTo(int((doc->chi2histogram.hist_min_dif_module / 2) * prop + 0.05 * rc_width), 0.95 * rc_height + 4);
	tmp.Format(L"%g", doc->chi2histogram.hist_min_value);
	dc->TextOut(int((doc->chi2histogram.hist_min_dif_module / 2) * prop + 0.05 * rc_width) - 4, int(0.95 * rc_height) + 8, tmp);

	for (int i = 0; i < doc->chi2histogram.get_size(); ++i) {
		//Drawing bar for theoretical value
		double bar_center_th = (doc->chi2histogram.get_th_point(i).value - doc->chi2histogram.hist_min_value
			+ doc->chi2histogram.hist_min_dif_module / 2) * prop; // in pixels
		int x1 = int(0.05 * rc_width + bar_center_th - shift);
		int y1 = int((0.95 - doc->chi2histogram.get_th_point(i).freq / doc->chi2histogram.hist_max_freq * 0.75) * rc_height);
		int x2 = int(0.05 * rc_width + bar_center_th + shift);
		int y2 = int(0.95 * rc_height + 1);
		draw_rectangle(dc, x1, y1, x2, y2, 0);

		//Drawing bar for empirical value
		double bar_center_emp = (doc->chi2histogram.get_emp_point(i).value - doc->chi2histogram.hist_min_value
			+ doc->chi2histogram.hist_min_dif_module / 2) * prop; // in pixels
		x1 = int(0.05 * rc_width + bar_center_emp - shift / 2);
		y1 = int((0.95 - 1.0 * doc->chi2histogram.get_emp_point(i).freq / doc->chi2histogram.hist_max_freq * 0.75) * rc_height);
		x2 = int(0.05 * rc_width + bar_center_emp + shift / 2);

		double tmp1 = doc->chi2histogram.get_emp_point(i).freq;
		draw_rectangle(dc, x1, y1, x2, y2, 1);
	}

	bool zero_far_from_max = abs(doc->chi2histogram.hist_max_value * prop) > 4;
	bool zero_far_from_min = abs(doc->chi2histogram.hist_min_value * prop) > 4;
	bool zero_after_start = (-doc->chi2histogram.hist_min_value) * prop + 0.05 * rc_width > 4;
	bool zero_before_end = (-doc->chi2histogram.hist_min_value) * prop < 0.75 * rc_width - 4;
	//Check if we can place zero value mark
	if (zero_far_from_max && zero_far_from_min && zero_after_start && zero_before_end) {
		dc->MoveTo((- doc->chi2histogram.hist_min_value) * prop + 
			doc->chi2histogram.hist_min_dif_module / 2 * prop + 0.05 * rc_width, 0.95 * rc_height - 4);
		dc->LineTo((-doc->chi2histogram.hist_min_value) * prop + 
			doc->chi2histogram.hist_min_dif_module / 2 * prop + 0.05 * rc_width, 0.95 * rc_height + 20);
		tmp.Format(L"%d", 0);
		dc->TextOut((-doc->chi2histogram.hist_min_value) * prop + shift + 0.05 * rc_width - 4, 0.95 * rc_height + 20, tmp);
	}

	//Marks for visibility
	int max_round_mark = 1;
	while (max_round_mark * 10 < doc->chi2histogram.hist_max_freq)
		max_round_mark *= 10;
	if (doc->chi2histogram.hist_max_freq / max_round_mark < 4)
		max_round_mark /= 2;
	for (int i = max_round_mark; i < doc->chi2histogram.hist_max_freq; i += max_round_mark) {
		int y = int((0.95 - 1.0 * i / doc->chi2histogram.hist_max_freq * 0.75) * rc_height);
		if (y > int(0.2 * rc_height) + 10) {
			dc->MoveTo(0.05 * rc_width - 4, y);
			dc->LineTo(0.05 * rc_width + 4, y);
			tmp.Format(L"%d", i);
			dc->TextOut(0.05 * rc_width - 5 - (long long)tmp.GetLength() * 8, y - 8, tmp);
		}
		else
			break;
	}

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
		if (doc->s) {
			delete doc->s;
		}
		switch (doc->method_type) {
		case 0:
			doc->s = new PrimitiveSample(doc->d0, doc->sum_freqs_h0);
			break;
		case 1:
			doc->s = new ChenSample(doc->d0);
			break;
		}
		doc->s->simulate(doc->sample_size);
		doc->chi2histogram.SetData(*doc->s, doc->d0);

		double pval = doc->chi2histogram.get_pvalue();
		double chi = doc->chi2histogram.get_chi2();

		doc->UpdateAllViews(0);
	}
}

void CBPv1View::draw_pvalue_plot(CDC* dc) {
	CBPv1Doc* doc = GetDocument();
	CPen penBlack;
	penBlack.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = dc->SelectObject(&penBlack);

	CRect rc;
	GetClientRect(&rc);
	int rc_width = rc.Width(), rc_height = rc.Height();

	//X axis
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.95 * rc_width, 0.95 * rc_height);

	//Y axis
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	dc->LineTo(0.05 * rc_width, 0.05 * rc_height);

	//"1" mark, X axis
	dc->MoveTo(0.85 * rc_width, 0.95 * rc_height - 4);
	dc->LineTo(0.85 * rc_width, 0.95 * rc_height + 4);
	dc->TextOut(0.85 * rc_width - 2, 0.95 * rc_height + 6, L"1");

	int grid_step = 5;

	//X grid
	dc->MoveTo(0.85 * rc_width, 0.15 * rc_height);
	double y_tmp = 0.;
	while (0.95 * rc_height - y_tmp - 0.15 * rc_height> 10e-10) {
		dc->LineTo(0.85 * rc_width, 0.15 * rc_height + y_tmp + grid_step);
		y_tmp += grid_step * 2;
		dc->MoveTo(0.85 * rc_width, 0.15 * rc_height + y_tmp);
	}

	//Y grid
	dc->MoveTo(0.05 * rc_width, 0.15 * rc_height);
	double x_tmp = 0.;
	while (0.85 * rc_width - x_tmp - 0.05 * rc_width > 10e-10) {
		dc->LineTo(0.05 * rc_width + x_tmp + grid_step, 0.15 * rc_height);
		x_tmp += grid_step * 2;
		dc->MoveTo(0.05 * rc_width + x_tmp, 0.15 * rc_height);
	}

	//"1" mark, Y axis
	dc->MoveTo(0.05 * rc_width - 4, 0.15 * rc_height);
	dc->LineTo(0.05 * rc_width + 4, 0.15 * rc_height);
	dc->TextOut(0.05 * rc_width - 16, 0.15 * rc_height - 6, L"1");

	//"0" mark
	dc->TextOut(0.05 * rc_width - 16, 0.95 * rc_height + 6, L"0");

	CPen penGreen;
	penGreen.CreatePen(PS_SOLID, 3, RGB(0, 200, 0));
	dc->SelectObject(penGreen);
	
	dc->MoveTo(0.05 * rc_width, 0.95 * rc_height);
	for (int i = 0; i < ALPHA_NUM; ++i) {
		dc->LineTo(0.05 * rc_width + (i + 1) * 0.8 * rc_width / ALPHA_NUM, 0.95 * rc_height - doc->pvalues_frac[i] * 0.8 * rc_height);
	}

	dc->SelectObject(pOldPen);
}


void CBPv1View::OnPvalue()
{
	CBPv1Doc* doc = GetDocument();
	PvalueDlg d;
	d.fill_values(doc);
	if (d.DoModal() == IDOK) {
		doc->draw_mode = 2;

		doc->sum_freqs_h0 = 0;
		for (int i = 0; i < d.h0_box_num + 1; ++i) {
			doc->sum_freqs_h0 += d.h0_abs_freqs[i];
		}

		doc->sum_freqs_h1 = 0;
		for (int i = 0; i < d.h1_box_num + 1; ++i) {
			doc->sum_freqs_h1 += d.h1_abs_freqs[i];
		}

		doc->d0.set_parameters(d.h0_values, d.h0_abs_freqs, d.h0_box_num + 1, doc->sum_freqs_h0);
		doc->d1.set_parameters(d.h1_values, d.h1_abs_freqs, d.h1_box_num + 1, doc->sum_freqs_h1);
		doc->method_type = d.m_method_type;
		doc->sample_size = d.m_sample_size;
		doc->pvalue_sample_size = d.m_pvalue_sample_size;

		if (doc->s) {
			delete doc->s;
		}
		switch (doc->method_type) {
		case 0:
			doc->s = new PrimitiveSample(doc->d0, doc->sum_freqs_h0);
			break;
		case 1:
			doc->s = new ChenSample(doc->d0);
			break;
		}
		doc->pvalues_arr = new double[doc->pvalue_sample_size];
		doc->pvalues_frac = new double[ALPHA_NUM];

		for (int i = 0; i < doc->pvalue_sample_size; ++i) {
			doc->s->simulate(doc->sample_size);
			doc->chi2histogram.SetData(*doc->s, doc->d1);
			doc->pvalues_arr[i] = doc->chi2histogram.get_pvalue();
		}

		std::sort(doc->pvalues_arr, doc->pvalues_arr + doc->pvalue_sample_size, [](const double& lval, const double& rval) {
			return lval < rval;
			});

		double alpha_step = 1. / ALPHA_NUM;
		int index = 0;
		for (int i = 0; i < ALPHA_NUM; ++i)
			doc->pvalues_frac[i] = 0;


		for (int i = 0; i < doc->pvalue_sample_size; ++i) {
			if (alpha_step - doc->pvalues_arr[i] > 10e-10) {
				doc->pvalues_frac[index] += 1. / doc->pvalue_sample_size;
			}
			else {
				--i;
				++index;
				doc->pvalues_frac[index] = doc->pvalues_frac[index - 1];
				alpha_step += 1. / ALPHA_NUM;
			}
		}

		doc->UpdateAllViews(0);
	}
}
