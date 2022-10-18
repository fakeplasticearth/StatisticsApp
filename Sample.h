#pragma once
#include "pch.h"
#include "Distribution.h"
#include "Util.h"

class Sample {
protected:
	Distribution distribution; // Distribution that will be used to generate sample values
	double* values = nullptr; // Values of sample
	point_emp* grouped_points; // Grouped values of sample
	unsigned int size = 0; // Size of sample
	virtual unsigned int gen_col_index() = 0; // Virtual function that generates index of distribution value
public:
	Sample();
	Sample(const Distribution& distr);
	Sample(const Sample& other);
	void swap(Sample& other);
	void simulate(unsigned int new_size);
	virtual ~Sample();
	point_emp get_point_emp(int index) const;
	unsigned int get_size() const;
	void set_parameters(const Distribution& distr); // Set fields for already created sample
};