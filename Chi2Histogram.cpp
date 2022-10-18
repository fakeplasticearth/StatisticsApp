#include "pch.h"
#include "BPv1Doc.h"

Chi2Histogram::Chi2Histogram() {

}

Chi2Histogram::Chi2Histogram(const Sample& sample, const Distribution& distr) : size(distr.get_size()) {
	emp_points_sorted = new point_emp[distr.get_size()];
	th_points_sorted = new point_th[distr.get_size()];

	for (int i = 0; i < size; ++i) {
		emp_points_sorted[i] = sample.get_point_emp(i);
		th_points_sorted[i] = { distr.get_ith_value(i), distr.get_ith_freq(i) * sample.get_size() };
	}
	std::sort(emp_points_sorted, emp_points_sorted + size, [](const point_emp& lval, const point_emp& rval) {
		return lval.value < rval.value;
		});
	std::sort(th_points_sorted, th_points_sorted + size, [](const point_th& lval, const point_th& rval) {
		return lval.value < rval.value;
		});
}

Chi2Histogram::Chi2Histogram(Chi2Histogram&& other) : emp_points_sorted(other.emp_points_sorted), th_points_sorted(other.th_points_sorted), 
emp_freqs_merged(other.emp_freqs_merged), th_freqs_merged(other.th_freqs_merged), size(other.size), df(other.df), pvalue(other.pvalue),
chi2(other.chi2) {
	
	other.emp_freqs_merged = nullptr;
	other.th_freqs_merged = nullptr;
	other.emp_points_sorted = nullptr;
	other.th_points_sorted = nullptr;
}

Chi2Histogram::Chi2Histogram(const Chi2Histogram& other) : size(other.size), chi2(other.chi2), df(other.df), pvalue(other.pvalue) {
	if (size) {
		emp_points_sorted = new point_emp[size];
		th_points_sorted = new point_th[size];
		for (int i = 0; i < size; ++i) {
			emp_points_sorted[i] = other.emp_points_sorted[i];
			th_points_sorted[i] = other.th_points_sorted[i];
		}
		if (df) {
			emp_freqs_merged = new int[df + 1];
			th_freqs_merged = new double[df + 1];
			for (int i = 0; i <= df; ++i) {
				emp_freqs_merged[i] = other.emp_freqs_merged[i];
				th_freqs_merged[i] = other.th_freqs_merged[i];
			}
		}
	}
}

void Chi2Histogram::SetData(const Sample& sample_, const Distribution& distr) {
	delete[] emp_points_sorted;
	delete[] th_points_sorted;
	delete[] emp_freqs_merged;
	delete[] th_freqs_merged;

	size = distr.get_size();
	df = UNSPECIFIED_VALUE;
	chi2 = UNSPECIFIED_VALUE;
	pvalue = UNSPECIFIED_VALUE;
	hist_max_freq = UNSPECIFIED_VALUE;
	emp_points_sorted = new point_emp[size];
	th_points_sorted = new point_th[size];
	if (size >= 1) {
		hist_min_value = distr.get_ith_value(0);
		hist_max_value = hist_min_value;
	}

	sample_size = sample_.get_size();
	for (int i = 0; i < size; ++i) {
		emp_points_sorted[i] = sample_.get_point_emp(i);
		th_points_sorted[i] = {distr.get_ith_freq(i) * sample_.get_size(), distr.get_ith_value(i) };
		double tmp1 = emp_points_sorted[i].value;
		double tmp2 = th_points_sorted[i].value;
		hist_max_value = max(max(emp_points_sorted[i].value, th_points_sorted[i].value), hist_max_value);
		hist_min_value = min(min(emp_points_sorted[i].value, th_points_sorted[i].value), hist_min_value);
		hist_max_freq = max(max(emp_points_sorted[i].freq, th_points_sorted[i].freq), hist_max_freq);
	}
	std::sort(emp_points_sorted, emp_points_sorted + size, [](const point_emp& lval, const point_emp& rval) {
		return lval.value < rval.value;
		});
	std::sort(th_points_sorted, th_points_sorted + size, [](const point_th& lval, const point_th& rval) {
		return lval.value < rval.value;
		});
	if (size == 1)
		hist_min_dif_module = th_points_sorted[0].value / 2;
	else
		hist_min_dif_module = th_points_sorted[1].value - th_points_sorted[0].value;
	for (int i = 0; i < size - 1; ++i) {
		hist_min_dif_module = min(th_points_sorted[i + 1].value - th_points_sorted[i].value, hist_min_dif_module);
	}

}

point_emp Chi2Histogram::get_emp_point(int index) {
	return emp_points_sorted[index];
}

point_th Chi2Histogram::get_th_point(int index) {
	return th_points_sorted[index];
}

int Chi2Histogram::get_size() {
	return size;
}

void Chi2Histogram::merge_freqs() {
	emp_freqs_merged= new int[size];
	th_freqs_merged = new double[size];
	df = 0;
	for (int i = 0; i < size; ++i) {
		emp_freqs_merged[df] = 0;
		th_freqs_merged[df] = 0;

		for (; (i < size) && (th_freqs_merged[df] < 5); ++i) {
			emp_freqs_merged[df] += emp_points_sorted[i].freq;
			th_freqs_merged[df] += th_points_sorted[i].freq;
		}
		double tmp = th_freqs_merged[df];

		if (th_freqs_merged[df] < 5 && df >= 1) {
			emp_freqs_merged[df - 1] += emp_freqs_merged[df];
			th_freqs_merged[df - 1] += th_freqs_merged[df];
			--df;
		}
		else if (th_freqs_merged[df] < 5) {
			df = -1;
			break;
		}
		--i;
		++df;
	}
	--df;

}

void Chi2Histogram::calc_chi2() {
	chi2 = 0;
	if (df == UNSPECIFIED_VALUE)
		merge_freqs();
	for (int i = 0; i <= df; ++i)
		chi2 += (emp_freqs_merged[i] - th_freqs_merged[i]) * (emp_freqs_merged[i] - th_freqs_merged[i]) / th_freqs_merged[i];
}

double Chi2Histogram::get_chi2() {
	if (chi2 == UNSPECIFIED_VALUE)
		calc_chi2();
	return chi2;
}

int Chi2Histogram::get_df() {
	if (df == UNSPECIFIED_VALUE)
		merge_freqs();
	return df;
}

double Chi2Histogram::get_pvalue() {
	if (pvalue == UNSPECIFIED_VALUE) {
		if (chi2 == UNSPECIFIED_VALUE)
			calc_chi2();
		pvalue = 1 - pChi(chi2, df);
	}
	return pvalue;
}

Chi2Histogram::~Chi2Histogram() {
	delete[]emp_freqs_merged;
	delete[]th_freqs_merged;
	delete[]th_points_sorted;
	delete[]emp_points_sorted;
}



