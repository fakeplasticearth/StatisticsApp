#pragma once
#include "pch.h"
#include "Distribution.h"
#include "Util.h"

/*!
* \brief Класс, содержащий виртуальную функцию, которая должна генерировать индекс для массива значений случайной дискретной величины.
* Этот класс генерирует выборку заданного размера из дискретного распределения.
* \details Виртуальная функция определяется в двух наследниках, PrimitiveSample и ChenSample.
*/
class Sample {
protected:
	/// \brief Распределение, из которого генерируются случайная величина.
	Distribution distribution;
	/// \brief Указатель на массив выборки.
	double* values = nullptr;
	/// \brief Указатель на массив сгруппированной выборки.
	point_emp* grouped_points;
	/// \brief Размер выборки.
	unsigned int size = 0;
	/*!
	* Виртуальная функция, генерирующая индекс для массива значений случайной величины, которая переопределяется в наследниках.
	*/
	virtual unsigned int simulate_rv() = 0;
public:
	/*!
	* Пустой конструктор.
	*/
	Sample();
	/*!
	* Конструктор, использующий объект типа Distribution (распределение).
	* \param distr Константная ссылка на объект типа Distribution (распределение).
	*/
	Sample(const Distribution& distr);
	/*!
	* Конструктор копирования.
	* \param other Константная ссылка на объект типа Sample (другой объект этого типа).
	*/
	Sample(const Sample& other);
	/*!
	* Деструктор.
	*/
	virtual ~Sample();
	/*!
	* Метод, позволяющий менять этот объект с объектом этого же типа.
	* \param other Ссылка на объект типа Sample (другой объект этого типа).
	*/
	void swap(Sample& other);
	/*!
	* Функция, заполняющая массив выборки реализациями случайной величины.
	* \param new_size Размер массива выборки.
	* \warning Функция создает новый массив выборки, то есть в случае, если массив выборки был не пуст, данные теряются.
	*/
	void simulate(unsigned int new_size);
	/*!
	* Функция, возвращающая элемент массива grouped_arr (массива сгруппированной выборки) по индексу index.
	* \param index Индекс массива grouped_arr.
	*/
	point_emp get_point_emp(int index) const;
	/*!
	* Функция, возвращающая поле size (размер выборки).
	*/
	unsigned int get_size() const;
	/*!
	* Функция, заполняющая поля.
	* \param distr Константная ссылка на объект типа Distribution (распределение).
	*/
	void set_parameters(const Distribution& distr);
};