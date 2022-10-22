#include "pch.h"
#include "PrimitiveSample.h"

PrimitiveSample::PrimitiveSample(const Distribution& distr, int freq_sum) : Sample(distr) {
	util_size = freq_sum;
	util_arr = new unsigned int[util_size];
	for (int j = 0, i = 0; j < distr.get_size(); i += (int)(distr.get_ith_freq(j) * freq_sum), ++j) {
		for (int z = i; z < i + (int)(distr.get_ith_freq(j) * freq_sum); ++z)
			util_arr[z] = j;
	}
}

PrimitiveSample::PrimitiveSample(const PrimitiveSample& other) : Sample(other), util_size(other.get_util_size()) {
	util_arr = new unsigned int[util_size];
	for (int i = 0; i < util_size; ++i)
		util_arr[i] = other.get_util_arr_ith_value(i);
}

void PrimitiveSample::swap(PrimitiveSample& other) {
	Sample::swap(other);
}

PrimitiveSample& PrimitiveSample::operator=(PrimitiveSample& other) {
	this->swap(other);
	return *this;
}

unsigned int PrimitiveSample::simulate_rv() {
	double res = rnunif();
	return util_arr[(int)(rnunif() * util_size)];
}

unsigned int PrimitiveSample::get_util_size() const {
	return util_size;
}

unsigned int PrimitiveSample::get_util_arr_ith_value(unsigned int index) const {
	return util_arr[index];
}

PrimitiveSample::~PrimitiveSample() {
	if (size != 0)
		delete[]values;
	if (distribution.get_size() != 0) {
		delete[]grouped_points;
	}
	delete[]util_arr;
	util_arr = nullptr;
	grouped_points = nullptr;
	values = nullptr;
	size = 0;
	distribution.~Distribution();
}