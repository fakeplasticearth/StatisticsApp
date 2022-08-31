
// BPv1Doc.cpp: реализация класса CBPv1Doc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "BPv1.h"
#endif

#include "BPv1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBPv1Doc

IMPLEMENT_DYNCREATE(CBPv1Doc, CDocument)

BEGIN_MESSAGE_MAP(CBPv1Doc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CBPv1Doc

CBPv1Doc::CBPv1Doc() noexcept: sum_freqs_h0(100), sum_freqs_h1(100), method_type(0), sample_size(1000)
{
	// TODO: добавьте код для одноразового вызова конструктора
	rninit(442);
	int tmp_freqs_h0[5]={ 10, 30, 40, 5, 15 };
	double tmp_values_h0[5] = {3.0, 3.5, 4.0, 4.5, 5.0};
	d0.set_parameters(tmp_values_h0, tmp_freqs_h0, 5, sum_freqs_h0);
	int tmp_freqs_h1[5] = { 10, 30, 40, 5, 15 };
	double tmp_values_h1[5] = { 3.0, 3.5, 4.0, 4.5, 5.0 };
	d0.set_parameters(tmp_values_h1, tmp_freqs_h1, 5, sum_freqs_h1);

	NONCLIENTMETRICS metrics = {};
	metrics.cbSize = sizeof(metrics);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, metrics.cbSize, &metrics, 0);

	HFONT guiFont = CreateFontIndirect(&metrics.lfCaptionFont);
	box_font = CFont::FromHandle(guiFont);
}

CBPv1Doc::~CBPv1Doc()
{
}

BOOL CBPv1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CBPv1Doc

void CBPv1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CBPv1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CBPv1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CBPv1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CBPv1Doc

#ifdef _DEBUG
void CBPv1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBPv1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CBPv1Doc
