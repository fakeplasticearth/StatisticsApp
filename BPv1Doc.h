
// BPv1Doc.h: интерфейс класса CBPv1Doc 
//


#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include "R64M.hpp"

#define NOT_A_NUMBER 0
#define NOT_AN_INT 1
#define SUM_MORE_THAN_ONE 2



class CBPv1Doc : public CDocument
{
protected: // создать только из сериализации
	CBPv1Doc() noexcept;
	DECLARE_DYNCREATE(CBPv1Doc)

// Атрибуты
public:

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
	double get_ith_value(unsigned int index);
	double get_ith_freq(unsigned int index) const;
	void print_i();
};

class Sample {
protected:
	Distribution distribution;
	double* grouped_values = nullptr, * values = nullptr;
	int* grouped_freqs = nullptr;
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
};

class PrimitiveSample : public Sample {
private:
	unsigned int gen_col_index() override; // Это и есть та виртуальная функция, которая нужна для создания выборки
	unsigned int* util_arr = nullptr;
	unsigned int util_size = 0;
public:
	PrimitiveSample(const Distribution& distr); //Конструктор с распределением
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
