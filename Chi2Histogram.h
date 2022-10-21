#pragma once
#include "pch.h"
#include "Util.h"
#include "Sample.h"
#include <algorithm>
#include "PROBDIST.H"
#include "R64M.hpp"
#include <math.h>

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
	double hist_max_value = 0.;
	double hist_min_value = 0.;
	double hist_min_dif_module = 0.; // ћинимальна€ величина разности значений в Distribution d0
	int hist_max_freq = 0.;
	int sample_size = 0;
public:
	Chi2Histogram();
	Chi2Histogram(const Sample& sample_, const Distribution& distr);
	Chi2Histogram(Chi2Histogram&& other);
	Chi2Histogram(const Chi2Histogram& other);
	~Chi2Histogram();
	void SetData(const Sample& sample_, const Distribution& distr);
	point_emp get_emp_point(int index);
	point_th get_th_point(int index);
	void merge_freqs();
	int get_df();
	double get_pvalue();
	void calc_chi2();
	double get_chi2();

	int get_size() const;
	double get_hist_max_value() const;
	double get_hist_min_value() const;
	double get_hist_min_dif_module() const;
	int get_hist_max_freq() const;
	int get_sample_size() const;
};
