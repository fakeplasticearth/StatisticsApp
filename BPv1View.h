
// BPv1View.h: интерфейс класса CBPv1View
//

#pragma once


class CBPv1View : public CView
{
protected: // создать только из сериализации
	CBPv1View() noexcept;
	DECLARE_DYNCREATE(CBPv1View)

// Атрибуты
public:
	CBPv1Doc* GetDocument() const;

// Операции
public:
	void draw_rectangle(CDC* dc, int x1, int y1, int x2, int y2);
	void draw_histogram(CDC* dc);
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CBPv1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHistogram();
};

#ifndef _DEBUG  // версия отладки в BPv1View.cpp
inline CBPv1Doc* CBPv1View::GetDocument() const
   { return reinterpret_cast<CBPv1Doc*>(m_pDocument); }
#endif

