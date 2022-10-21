#pragma once
#include "pch.h"
#include "Sample.h"
#include "R64M.hpp"

/*!
	\brief 
*/
class ChenSample : public Sample {
private:
	unsigned int gen_col_index() override;
	unsigned int m; // специальный параметр
	double* r;
	double* s; // накопленные вероятности
public:
	ChenSample(const Distribution& distr, int m_); //Конструктор с распределением
	ChenSample(const ChenSample& other); // Конструктор копирования
	void swap(ChenSample& other);
	ChenSample& operator=(ChenSample& other);
	~ChenSample() override;
	int get_m() const;
	double get_r_ith_value(int index) const;
	double get_s_ith_value(int index) const;
};
