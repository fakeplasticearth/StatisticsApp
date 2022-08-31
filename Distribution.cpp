#include "pch.h"
#include "BPv1Doc.h"

Distribution::Distribution(double* values_, double* p, int size_) : size(size_) {
	values = new double[size];
	freqs = new double[size];
	for (int i = 0; i < size; ++i) {
		values[i] = values_[i];
		freqs[i] = p[i];
	}
}

Distribution::Distribution(const Distribution& distr) : size(distr.size), name(distr.name) {
	values = new double[size];
	freqs = new double[size];
	for (int i = 0; i < size; ++i) {
		values[i] = distr.values[i];
		freqs[i] = distr.freqs[i];
	}
}

Distribution::Distribution(Distribution&& distr) noexcept : values(distr.values), freqs(distr.freqs), size(distr.size), name(distr.name) {
	distr.size = 0;
	distr.values = nullptr;
	distr.freqs = nullptr;
	distr.name = "";
}

void Distribution::swap(Distribution& distr) noexcept {
	std::swap(values, distr.values);
	std::swap(freqs, distr.freqs);
	std::swap(size, distr.size);
	std::swap(name, distr.name);
}

Distribution& Distribution::operator=(Distribution distr) noexcept {
	this->swap(distr);
	return *this;
}

Distribution::~Distribution() {
	if (size != 0) {
		delete[]values;
		delete[]freqs;
	}
}

unsigned int Distribution::get_size() const {
	return size;
}

double Distribution::get_ith_value(unsigned int index) const{
	return values[index];
}

double Distribution::get_ith_freq(unsigned int index) const {
	return freqs[index];
}

std::string Distribution::get_name() {
	return name;
}

void Distribution::print_i() {
	std::cout << "Distr size: " << size << '\n';
	std::cout << "Distr values: \n";
	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(4) << values[i] << ' ';
	}
	std::cout << "\nDistr freqs: \n";
	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(4) << freqs[i] << ' ';
	}
}

void Distribution::set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_) {
	delete[]values;
	delete[]freqs;
	values = new double[size_ + 2];
	freqs = new double[size_ + 2];
	size = size_;
	for (int i = 0; i < size; ++i) {
		values[i] = values_[i];
		freqs[i] = 1.0 * abs_freqs_[i] / sum_freqs_;
	}
}

void Distribution::set_parameters(const Distribution& distr) {
	if (values) {
		delete[]values;
		delete[]freqs;
	}
	size = distr.get_size();
	values = new double[size + 2];
	freqs = new double[size + 2];
	for (int i = 0; i < size; ++i) {
		values[i] = distr.get_ith_value(i);
		freqs[i] = distr.get_ith_freq(i);
	}
}