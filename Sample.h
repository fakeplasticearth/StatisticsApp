#pragma once
#include "pch.h"
#include "Distribution.h"
#include "Util.h"

/*!
* \brief �����, ���������� ����������� �������, ������� ������ ������������ ������ ��� ������� �������� ��������� ���������� ��������.
* ���� ����� ���������� ������� ��������� ������� �� ����������� �������������.
* \details ����������� ������� ������������ � ���� �����������, PrimitiveSample � ChenSample.
*/
class Sample {
protected:
	/// \brief �������������, �� �������� ������������ ��������� ��������.
	Distribution distribution;
	/// \brief ��������� �� ������ �������.
	double* values = nullptr;
	/// \brief ��������� �� ������ ��������������� �������.
	point_emp* grouped_points;
	/// \brief ������ �������.
	unsigned int size = 0;
	/*!
	* ����������� �������, ������������ ������ ��� ������� �������� ��������� ��������, ������� ���������������� � �����������.
	*/
	virtual unsigned int simulate_rv() = 0;
public:
	/*!
	* ������ �����������.
	*/
	Sample();
	/*!
	* �����������, ������������ ������ ���� Distribution (�������������).
	* \param distr ����������� ������ �� ������ ���� Distribution (�������������).
	*/
	Sample(const Distribution& distr);
	/*!
	* ����������� �����������.
	* \param other ����������� ������ �� ������ ���� Sample (������ ������ ����� ����).
	*/
	Sample(const Sample& other);
	/*!
	* ����������.
	*/
	virtual ~Sample();
	/*!
	* �����, ����������� ������ ���� ������ � �������� ����� �� ����.
	* \param other ������ �� ������ ���� Sample (������ ������ ����� ����).
	*/
	void swap(Sample& other);
	/*!
	* �������, ����������� ������ ������� ������������ ��������� ��������.
	* \param new_size ������ ������� �������.
	* \warning ������� ������� ����� ������ �������, �� ���� � ������, ���� ������ ������� ��� �� ����, ������ ��������.
	*/
	void simulate(unsigned int new_size);
	/*!
	* �������, ������������ ������� ������� grouped_arr (������� ��������������� �������) �� ������� index.
	* \param index ������ ������� grouped_arr.
	*/
	point_emp get_point_emp(int index) const;
	/*!
	* �������, ������������ ���� size (������ �������).
	*/
	unsigned int get_size() const;
	/*!
	* �������, ����������� ����.
	* \param distr ����������� ������ �� ������ ���� Distribution (�������������).
	*/
	void set_parameters(const Distribution& distr);
};