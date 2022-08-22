#include "pch.h"
#include "BPv1Doc.h"

Sample::Sample() {}

Sample::Sample(const Distribution& distr) : distribution(distr) {
	unsigned int tmp_size = distribution.get_size();
	grouped_freqs = new int[tmp_size];
	grouped_values = new double[tmp_size];
	for (int i = 0; i < tmp_size; ++i) {
		grouped_freqs[i] = 0;
		grouped_values[i] = distribution.get_ith_value(i);
	}
}

Sample::Sample(const Sample& other) noexcept : size(other.size), distribution(other.distribution) {
	values = new double[other.size];
	grouped_freqs = new int[other.distribution.get_size()];
	grouped_values = new double[other.distribution.get_size()];

	for (int i = 0; i < size; ++i) {
		values[i] = other.values[i];
	}

	for (int i = 0; i < distribution.get_size(); ++i) {
		grouped_freqs[i] = other.grouped_freqs[i];
		grouped_values[i] = other.grouped_values[i];
	}
}

void Sample::swap(Sample& other) {
	distribution.swap(other.distribution);
	std::swap(values, other.values);
	std::swap(size, other.size);
	std::swap(grouped_freqs, other.grouped_freqs);
	std::swap(grouped_values, other.grouped_values);
}

Sample::~Sample() {
	if (size != 0)
		delete[]values;
	if (distribution.get_size() != 0) {
		delete[]grouped_freqs;
		delete[]grouped_values;
	}
}

void Sample::simulate(unsigned int new_size) {
	if (size != 0) {
		delete[]values;
		for (int i = 0; i < distribution.get_size(); ++i) {
			grouped_freqs[i] = 0;
		}
	}
	size = new_size;
	values = new double[size];
	for (int i = 0; i < size; ++i) {
		unsigned int index = gen_col_index();
		values[i] = distribution.get_ith_value(index);
		grouped_freqs[index]++;
	}
}

void Sample::print_i() {
	distribution.print_i();
	std::cout << "\n \n Size: " << size << '\n' << "Values:\n";
	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(4) << values[i] << ' ';
	}
	std::cout << "\nGrouped values:\n";
	for (int i = 0; i < distribution.get_size(); ++i) {
		std::cout << std::setw(4) << grouped_values[i] << ' ';
	}
	std::cout << "\nGrouped freqs:\n";
	for (int i = 0; i < distribution.get_size(); ++i) {
		std::cout << std::setw(4) << grouped_freqs[i] << ' ';
	}
}