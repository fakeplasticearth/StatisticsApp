#pragma once
#include "pch.h"
#include "Sample.h"
#include "R64M.hpp"

/*!
* \brief �����-��������� ������ Sample, ������� �������������� ����������� �������, ������������ ��������� ��������. 
	��������� ������������ ������� ��������� �������� ���������� ��������� �������.
*/
class PrimitiveSample : public Sample {
private:
	/*!
	* �������, ������� ��������� ������������ ��������� �������� �� ����������� ���������� ������������� 
	���������� ��������� �������. ���������������� ���� �������.
	* ���������� ������ ��� ������� �������� �������� ��������.
	*/
	unsigned int simulate_rv() override;
	/// \brief ������, ������� ��������� ��� ��������� ��������� ��������. ����������� ���� �������.
	unsigned int* util_arr = nullptr;
	/// \brief ������ �������, ������� ��������� ��� ��������� ��������� ��������. ����������� ���� �������.
	unsigned int util_size = 0;
public:
	/*!
	* ����������� ������.
	* \param distr ����������� ������ �� ������ ���� Distribution (�������������), ������������� ������������ ��� ��������� ��������� ��������.
	* \param freq_sum_ ����� ����������, � ������� ������� ���������� �������������.
	*/
	PrimitiveSample(const Distribution& distr, int freq_sum);
	/*!
	* ����������� �����������.
	* \param other ����������� ������ �� ������ ���� PrimitiveSample (������ ������ ����� ����).
	*/
	PrimitiveSample(const PrimitiveSample& other);
	/*!
	* ����������.
	*/
	~PrimitiveSample() override;
	/*!
	* �����, ����������� ������ ���� ������ � �������� ����� �� ����.
	* \param other ������ �� ������ ���� PrimitiveSample (������ ������ ����� ����).
	*/
	void swap(PrimitiveSample& other);
	/*!
	* �������� �������������.
	* \param other ������ �� ������ ���� PrimitiveSample (������ ������ ����� ����).
	*/
	PrimitiveSample& operator=(PrimitiveSample& other);
	/*!
	* �������, ������������ �������� ���� util_size (������ �������, ������� ��������� ��� ��������� ��������� �������� 
	���������� ��������� �������).
	*/
	unsigned int get_util_size() const;
	/*!
	* �������, ������������ ������� ������� util_arr �� ������� index.
	* \param index ������ ������� util_arr, ����� ����� � �������� \f$ [0;util_size) \f$.
	*/
	unsigned int get_util_arr_ith_value(unsigned int index) const;
};