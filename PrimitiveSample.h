#pragma once
#include "pch.h"
#include "Sample.h"
#include "R64M.hpp"

class PrimitiveSample : public Sample {
private:
	unsigned int gen_col_index() override; // Virtual method that generates index of distribution object
	unsigned int* util_arr = nullptr; // Array for index generating
	unsigned int util_size = 0; // Util array size
public:
	PrimitiveSample(const Distribution& distr, int freq_sum); // Constructor with distribution object
	PrimitiveSample(const PrimitiveSample& other); // Copying constructor
	void swap(PrimitiveSample& other);
	PrimitiveSample& operator=(PrimitiveSample& other);
	unsigned int get_util_size() const;
	unsigned int get_util_arr_ith_value(unsigned int index) const;
	~PrimitiveSample() override;
};