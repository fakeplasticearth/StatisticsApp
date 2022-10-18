#pragma once

#include "pch.h"
#include <string>

class Distribution {
	double* values = nullptr, * probs = nullptr;
	unsigned int size = 0;
	std::string name = "";
public:
	Distribution() {}
	Distribution(double* values_, double* p, int size_); // Constructor from two arrays
	Distribution(const Distribution& distr); // Copying constructor
	Distribution(Distribution&& distr); // Move constructor
	~Distribution(); // Destructor
	void swap(Distribution& distr);
	Distribution& operator=(Distribution distr);
	std::string get_name();
	unsigned int get_size() const;
	double get_ith_value(unsigned int index) const;
	double get_ith_freq(unsigned int index) const;
	void set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_); // Set fields for already created distribution (arrays)
	void set_parameters(const Distribution& distr); // Set fields for already created distribution (distribution)
};
