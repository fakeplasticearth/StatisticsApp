#include "pch.h"
#include "BPv1Doc.h"

PrimitiveSample::PrimitiveSample(const Distribution& distr) : Sample(distr) {
	//–асчет на то, что частоты вместе со значени€ми отсортированы (по значени€м)
	for (int i = 0; i < distr.get_size(); ++i)
		util_size += distr.get_ith_freq(i);
	util_arr = new unsigned int[util_size];
	for (int j = 0, i = 0; j < distr.get_size(); i += distr.get_ith_freq(j), ++j) {
		for (int z = i; z < i + distr.get_ith_freq(j); ++z)
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

unsigned int PrimitiveSample::gen_col_index() {
	double res = rnunif();
	std::cout << res << ' ';
	return util_arr[(int)(rnunif() * util_size)];
}

unsigned int PrimitiveSample::get_util_size() const {
	return util_size;
}

unsigned int PrimitiveSample::get_util_arr_ith_value(unsigned int index) const {
	return util_arr[index];
}

void PrimitiveSample::check() {
	std::cout << "\nUtil arr size: " << util_size;
	std::cout << "Util values:\n";
	for (int i = 0; i < util_size; ++i) {
		std::cout << std::setw(4) << util_arr[i];
	}
}