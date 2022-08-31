
// BPv1Doc.h: интерфейс класса CBPv1Doc 
//


#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "R64M.hpp"
#include "PROBDIST.H"

#define NOT_A_NUMBER 0
#define NOT_AN_INT 1
#define EMPTY_BOX 2
#define SUM_MORE_THAN_ONE 3
#define UNSPECIFIED_VALUE -1

struct point_emp {
	int freq;
	double value;
};

struct point_th {
	double freq, value;
};

class Distribution {
	double* values = nullptr, * freqs = nullptr;
	unsigned int size = 0;
	std::string name = "";
public:
	Distribution() {}
	Distribution(double* values_, double* p, int size_);
	Distribution(const Distribution& distr); // Конструктор копирования
	Distribution(Distribution&& distr) noexcept; // Конструктор перемещения
	~Distribution(); // Деструктор
	void swap(Distribution& distr) noexcept;
	Distribution& operator=(Distribution distr) noexcept;
	std::string get_name();
	unsigned int get_size() const;
	double get_ith_value(unsigned int index) const;
	double get_ith_freq(unsigned int index) const;
	void print_i();
	void set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_);
	void set_parameters(const Distribution& distr);
};

class Sample {
protected:
	Distribution distribution;
	double* values = nullptr;
	point_emp* grouped_points;
	unsigned int size = 0;
	virtual unsigned int gen_col_index() = 0;
public:
	Sample();
	Sample(const Distribution& distr);
	Sample(const Sample& other) noexcept;
	void swap(Sample& other);
	void simulate(unsigned int new_size);
	virtual ~Sample();
	void print_i(); // это для дебага
	point_emp get_point_emp(int index) const;
	unsigned int get_size() const;
	void set_parameters(const Distribution& distr);
};

class PrimitiveSample : public Sample {
private:
	unsigned int gen_col_index() override; // Это и есть та виртуальная функция, которая нужна для создания выборки
	unsigned int* util_arr = nullptr;
	unsigned int util_size = 0;
public:
	PrimitiveSample(const Distribution& distr, int freq_sum); //Конструктор с распределением
	PrimitiveSample(const PrimitiveSample& other); // Конструктор копирования
	void swap(PrimitiveSample& other);
	PrimitiveSample& operator=(PrimitiveSample& other);
	unsigned int get_util_size() const;
	unsigned int get_util_arr_ith_value(unsigned int index) const;
	void check();
};

class ChenSample : public Sample {
private:
	unsigned int gen_col_index() override;
	unsigned int m; // специальный параметр
	double* r;
public:
	ChenSample(const Distribution& distr); //Конструктор с распределением
	ChenSample(const ChenSample& other); // Конструктор копирования
	void swap(ChenSample& other);
	ChenSample& operator=(ChenSample& other);
};

class Chi2Histogram
{
private:
	int size;
	point_emp* emp_points_sorted = nullptr;
	point_th* th_points_sorted = nullptr;
	int* emp_freqs_merged = nullptr;
	double* th_freqs_merged = nullptr;
	double pvalue;
	double chi2;
	unsigned int df; // degree of freedom
public:
	Chi2Histogram() {}
	Chi2Histogram(const Sample& sample_, const Distribution& distr);
	Chi2Histogram(Chi2Histogram&& other);
	Chi2Histogram(const Chi2Histogram& other);
	void SetData(const Sample& sample_, const Distribution& distr);
	point_emp get_emp_point(int index);
	point_th get_th_point(int index);
	int get_size();
	double hist_max_value = 0.;
	int hist_max_freq = 0;
	void merge_freqs();
	int get_df();
	double get_pvalue();
	double calc_chi2();
	~Chi2Histogram();
};

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
	int method_type;
	int sample_size;
	int draw_mode = 0;
	CFont* box_font;
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
