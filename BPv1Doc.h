
// BPv1Doc.h: интерфейс класса CBPv1Doc 
//


#pragma once
#include <iostream>
#include <iomanip>

#include "Chi2Histogram.h"
#include "R64M.hpp"
#include "PrimitiveSample.h"
#include "ChenSample.h"

#define BOX_HEIGHT 28 // высота edit box
#define BOX_WIDTH 50 // ширина edit box

#define ALPHA_NUM 100
#define eps 10e-10;

class CBPv1Doc : public CDocument
{
protected: // создать только из сериализации
	CBPv1Doc() noexcept;
	DECLARE_DYNCREATE(CBPv1Doc)

// Атрибуты
public:
	Sample* s = nullptr;
	Distribution d0, d1;
	Chi2Histogram chi2histogram;
	int sum_freqs_h0, sum_freqs_h1;
	int pvalue_sample_size;
	int method_type;
	int sample_size;
	int draw_mode = 0;
	int chen_parameter;
	CFont* box_font;
	double* pvalues_arr = nullptr;
	double* pvalues_frac = nullptr;
	double* slevel_arr = nullptr;
	int max_sample_size;
	int min_sample_size;
	double alpha;
// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CBPv1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
