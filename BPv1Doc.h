
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
#include "ParameterDlg.h"

#define NOT_A_NUMBER 0
#define NOT_AN_INT 1
#define EMPTY_BOX 2
#define INVALID_FREQ 3
#define COINCIDING_VALUES 4
#define INVALID_SAMPLE_SIZE 5
#define NOT_AN_INT_SAMPLE_SIZE 6
#define TOO_SMALL_PVALUE_SAMPLE_SIZE 7
#define TOO_BIG_PVALUE_SAMPLE_SIZE 8
#define NOT_AN_INT_PVALUE_SAMPLE_SIZE 9
#define UNSPECIFIED_VALUE -1

#define BOX_HEIGHT 28 // высота edit box
#define BOX_WIDTH 50 // ширина edit box

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
	Distribution(double* values_, double* p, int size_); // Constructor from two arrays
	Distribution(const Distribution& distr); // Copying constructor
	Distribution(Distribution&& distr); // Move constructor
	~Distribution(); // Destructor
	void swap(Distribution& distr);
	Distribution& operator=(Distribution distr);
	std::string get_name();
	unsigned int get_size() const;
	double get_ith_value(unsigned int index) const;
	double get_ith_freq(unsigned int index) const;
	void set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_); // Set fields for already created distribution (arrays)
	void set_parameters(const Distribution& distr); // Set fields for already created distribution (distribution)
};

class Sample {
protected:
	Distribution distribution; // Distribution that will be used to generate sample values
	double* values = nullptr; // Values of sample
	point_emp* grouped_points; // Grouped values of sample
	unsigned int size = 0; // Size of sample
	virtual unsigned int gen_col_index() = 0; // Virtual function that generates index of distribution value
public:
	Sample();
	Sample(const Distribution& distr);
	Sample(const Sample& other);
	void swap(Sample& other);
	void simulate(unsigned int new_size);
	virtual ~Sample();
	point_emp get_point_emp(int index) const;
	unsigned int get_size() const;
	void set_parameters(const Distribution& distr); // Set fields for already created sample
};

class PrimitiveSample : public Sample {
private:
	unsigned int gen_col_index() override; // Virtual method that generates index of distribution object
	unsigned int* util_arr = nullptr; // Array for index generating
	unsigned int util_size = 0; // Util array size
public:
	PrimitiveSample(const Distribution& distr, int freq_sum); // Constructor with distribution object
	PrimitiveSample(const PrimitiveSample& other); // Copying constructor
	void swap(PrimitiveSample& other);
	PrimitiveSample& operator=(PrimitiveSample& other);
	unsigned int get_util_size() const;
	unsigned int get_util_arr_ith_value(unsigned int index) const;
	~PrimitiveSample() override;
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
	double pvalue;
	double chi2;
	unsigned int df; // degree of freedom
	point_emp* emp_points_sorted = nullptr;
	point_th* th_points_sorted = nullptr;
	int* emp_freqs_merged = nullptr;
	double* th_freqs_merged = nullptr;
public:
	Chi2Histogram();
	Chi2Histogram(const Sample& sample_, const Distribution& distr);
	Chi2Histogram(Chi2Histogram&& other);
	Chi2Histogram(const Chi2Histogram& other);
	~Chi2Histogram();
	void SetData(const Sample& sample_, const Distribution& distr);
	point_emp get_emp_point(int index);
	point_th get_th_point(int index);
	int get_size();
	double hist_max_value = 0.; // 
	double hist_min_value = 0.;
	double hist_min_dif_module = 0.; // Минимальная величина разности значений в Distribution d0
	int hist_max_freq = 0;
	void merge_freqs();
	int get_df();
	double get_pvalue();
	void calc_chi2();
	double get_chi2();
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
	int pvalue_sample_size;
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
