#include "pch.h"
#include "Sample.h"

Sample::Sample() {}

Sample::Sample(const Distribution& distr) : distribution(distr) {
	unsigned int tmp_size = distribution.get_size();
	grouped_points = new point_emp[tmp_size];
	for (int i = 0; i < tmp_size; ++i) {
		grouped_points[i].freq = 0;
		grouped_points[i].value = distribution.get_ith_value(i);
	}
}

Sample::Sample(const Sample& other): size(other.size), distribution(other.distribution) {
	values = new double[other.size];
	grouped_points = new point_emp[other.distribution.get_size()];

	for (int i = 0; i < size; ++i) {
		values[i] = other.values[i];
	}

	for (int i = 0; i < distribution.get_size(); ++i) {
		grouped_points[i] = other.get_point_emp(i);
	}
}

void Sample::swap(Sample& other) {
	distribution.swap(other.distribution);
	std::swap(values, other.values);
	std::swap(size, other.size);
	std::swap(grouped_points, other.grouped_points);
}

Sample::~Sample() {
	if (size != 0)
		delete[]values;
	if (distribution.get_size() != 0) {
		delete[]grouped_points;
	}
}

void Sample::simulate(unsigned int new_size) {
	delete[]values;
	for (int i = 0; i < distribution.get_size(); ++i) {
		grouped_points[i].freq = 0;
		grouped_points[i].value = distribution.get_ith_value(i);
	}
	size = new_size;
	values = new double[size];
	for (int i = 0; i < size; ++i) {
		unsigned int index = gen_col_index();
		values[i] = distribution.get_ith_value(index);
		grouped_points[index].freq++;
	}
}

point_emp Sample::get_point_emp(int index) const {
	return grouped_points[index];
}

unsigned int Sample::get_size() const {
	return size;
}

void Sample::set_parameters(const Distribution& distr) {
	distribution.set_parameters(distr);
	size = 0;
}