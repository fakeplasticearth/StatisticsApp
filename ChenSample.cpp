#include "pch.h"
#include "BPv1Doc.h"

ChenSample::ChenSample(const Distribution& distr) : Sample(distr) {
}

ChenSample::ChenSample(const ChenSample& other) : Sample(other) {
}

void ChenSample::swap(ChenSample& other) {
	Sample::swap(other);
}

ChenSample& ChenSample::operator=(ChenSample& other) {
	this->swap(other);
	return *this;
}

unsigned int ChenSample::gen_col_index() {

	return 0;
}