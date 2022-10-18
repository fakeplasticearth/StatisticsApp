#include "pch.h"
#include "BPv1.h"
#include "Distribution.h"

Distribution::Distribution(double* values_, double* p, int size_) : size(size_) {
	values = new double[size];
	probs = new double[size];
	for (int i = 0; i < size; ++i) {
		values[i] = values_[i];
		probs[i] = p[i];
	}
}

Distribution::Distribution(const Distribution& distr) : size(distr.size), name(distr.name) {
	values = new double[size];
	probs = new double[size];
	for (int i = 0; i < size; ++i) {
		values[i] = distr.values[i];
		probs[i] = distr.probs[i];
	}
}

Distribution::Distribution(Distribution&& distr): values(distr.values), probs(distr.probs), size(distr.size), name(distr.name) {
	distr.size = 0;
	distr.values = nullptr;
	distr.probs = nullptr;
	distr.name = "";
}

void Distribution::swap(Distribution& distr) {
	std::swap(values, distr.values);
	std::swap(probs, distr.probs);
	std::swap(size, distr.size);
	std::swap(name, distr.name);
}

Distribution& Distribution::operator=(Distribution distr) {
	this->swap(distr);
	return *this;
}

Distribution::~Distribution() {
	if (size != 0) {
		delete[]values;
		delete[]probs;
		values = nullptr;
		probs = nullptr;
		size = 0;
	}
}

unsigned int Distribution::get_size() const {
	return size;
}

double Distribution::get_ith_value(unsigned int index) const{
	return values[index];
}

double Distribution::get_ith_freq(unsigned int index) const {
	return probs[index];
}

std::string Distribution::get_name() {
	return name;
}

void Distribution::set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_) {
	delete[]values;
	delete[]probs;
	values = new double[size_ + 2];
	probs = new double[size_ + 2];
	size = size_;
	double tmp1;
	double tmp2;
	for (int i = 0; i < size; ++i) {
		values[i] = values_[i];
		probs[i] = 1.0 * abs_freqs_[i] / sum_freqs_;
		tmp2 = probs[i];
		tmp1 = values[i];
	}
}

void Distribution::set_parameters(const Distribution& distr) {
	if (values) {
		delete[]values;
		delete[]probs;
	}
	size = distr.get_size();
	values = new double[size + 2];
	probs = new double[size + 2];
	for (int i = 0; i < size; ++i) {
		values[i] = distr.get_ith_value(i);
		probs[i] = distr.get_ith_freq(i);
	}
}