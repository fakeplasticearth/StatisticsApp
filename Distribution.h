#pragma once

#include "pch.h"
#include <string>

/*!
* \brief �����, ���������� ��������� ����������� �������������.
* \details ��������� �������� � ���� ������� ������������ � ������� ��������. �������� ������ ����� ��� \f$ \frac{k_i}{N} \f$, 
��� N > 0 - ����������� �����, ������ \f$ \sum_{i = 1}^{n}k_i = N\f$, n - �������� ��������� �������� ��������� ��������.
*/
class Distribution {
	/// \brief �������� ��������� �������� ��������� ��������.
	unsigned int size = 0;
	/// \brief ��������� �� ������ ��������, ������ ����� ������ size.
	double* values = nullptr;
	/// \brief ��������� �� ������ ������������, ������ ����� ������ size.
	double *probs = nullptr;
public:
	/// \brief ������ �����������.
	Distribution() {}
	/*!
	* �����������, ������� ���������� ������ �������� � ������ ������������.
	* \param values_ ��������� �� ������ ��������. ������ ����� ����� size_.
	* \param p ��������� �� ������ ������������. ������ ����� ����� size_.
	* \param size_ ����� �������� �������� � ������������.
	*/
	Distribution(double* values_, double* p, int size_);
	/*!
	* ����������� �����������.
	* \param distr ����������� ������ �� ������ ���� Distribution (������ ������ ����� ����).
	*/
	Distribution(const Distribution& distr);
	/*!
	* ����������� �����������.
	*/
	Distribution(Distribution&& distr);
	/*!
	* ����������.
	*/
	~Distribution();
	/*!
	* �������, ������� ������ ���� ������ � ������ �������� ���� Distribution.
	* \param distr ������ �� ������ ���� Distribution (������ ������ ����� ����).
	*/
	void swap(Distribution& distr);
	/*!
	* �������� �������������
	* \param distr ������ ���� Distribution (������ ������ ����� ����).
	*/
	Distribution& operator=(Distribution distr);
	/*!
	* �������, ������������ ������ �������������, ���� size (�������� ��������� ��������).
	*/
	unsigned int get_size() const;
	/*!
	* �������, ������������ �������� �� �������.
	* \param index ������ ������� ��������, ����� ����� � �������� \f$ [0;size) \f$.
	*/
	double get_ith_value(unsigned int index) const;
	/*!
	* �������, ������������ ����������� �� �������.
	* \param index ������ ������� ������������, ����� ����� � �������� \f$ [0;size) \f$.
	*/
	double get_ith_freq(unsigned int index) const;
	/*!
	* \brief �������, ����������� ���� � ������� �������� �������� � ���������� ������.
	* \param values_ ��������� �� ������ ��������, ������ ����� ����� size_.
	* \param abs_freqs_ ��������� �� ������ ���������� ������, ������ ����� ����� size_.
	* \param size_ ������ �������� �������� � ���������� ������.
	* \param sum_freqs_ ����� ���������� ������.
	* \details ����������� ����������� ������ ������ �� ������� \f$ p_i = \frac{k_i}{N}\f$, ��� \f$ k_i\f$ - ���������� �������,
	* \f$ N \f$ - ����� ���������� ������.
	*/
	void set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_);
	/*!
	* �������, ����������� ���� �������� ������������ ����� ������� ������� ���� Distribution.
	* \param distr ����������� ������ �� ������ ���� Distribution (������ ������ ����� ����).
	*/
	void set_parameters(const Distribution& distr);
};
