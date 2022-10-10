#include "pch.h"
#include "BPv1Doc.h"

ChenSample::ChenSample(const Distribution& distr, int m_) : Sample(distr) {
    m = m_;
    int d_size = distr.get_size();
    s = new double[d_size + 1];
    s[0] = distr.get_ith_freq(0);
    for (int i = 1; i < d_size; ++i)
        s[i] = s[i - 1] + distr.get_ith_freq(i);

    r = new double[m + 1];
    int i = 0, j = 0;
    double t = 0.;
    while ((i < d_size) && (j < m)) {
        if (s[i] - t < 1e-10) {
            ++i;
            continue;
        }
        r[j] = i;
        if (j < m - 1)
            t += 1.0 / m;
        ++j;
    }
}

ChenSample::ChenSample(const ChenSample& other) : Sample(other), m(other.get_m()) {
    s = new double[other.distribution.get_size() + 1];
    r = new double[other.distribution.get_size() + 1];
    for (int i = 0; i < other.distribution.get_size();++i) {
        s[i] = other.get_s_ith_value(i);
        r[i] = other.get_r_ith_value(i);
    }
}

void ChenSample::swap(ChenSample& other) {
	Sample::swap(other);
}

ChenSample& ChenSample::operator=(ChenSample& other) {
	this->swap(other);
	return *this;
}

unsigned int ChenSample::gen_col_index() {
    double prv = rnunif();
    int j = (int)(prv * m);
    int z = r[j];

    while (prv - s[z] >= 1e-10) {
        ++z;
    }
    return z;
}

ChenSample::~ChenSample() {
    if (size != 0)
        delete[]values;
    if (distribution.get_size() != 0) {
        delete[]grouped_points;
    }

    delete[]r;
    delete[]s;
    grouped_points = nullptr;
    values = nullptr;
    size = 0;
    distribution.~Distribution();
}

int ChenSample::get_m() const {
    return m;
}

double ChenSample::get_r_ith_value(int index) const {
    return r[index];
}

double ChenSample::get_s_ith_value(int index) const {
    return s[index];
}