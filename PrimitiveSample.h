#pragma once
#include "pch.h"
#include "Sample.h"
#include "R64M.hpp"

/*!
* \brief Класс-наследник класса Sample, которые переопределяет виртуальную фукнцию, генерирующую случайную величину. 
	Позволяет генерировать выборку случайной величины простейшим табличным методом.
*/
class PrimitiveSample : public Sample {
private:
	/*!
	* Функция, которая позволяет генерировать случайную величину из дискретного табличного распределения 
	простейшим табличным методом. Переопределяется этим классом.
	* Генерирует индекс для массива значений случаной величины.
	*/
	unsigned int simulate_rv() override;
	/// \brief Массив, который необходим для генерации случайной величины. Вычисляется этим классом.
	unsigned int* util_arr = nullptr;
	/// \brief Размер массива, который необходим для генерации случайной величины. Вычисляется этим классом.
	unsigned int util_size = 0;
public:
	/*!
	* Конструктор класса.
	* \param distr Константная ссылка на объект типа Distribution (распределение), распределение используется для генерации случайной величины.
	* \param freq_sum_ Сумма абсолютных, с помощью которых задавалось распределение.
	*/
	PrimitiveSample(const Distribution& distr, int freq_sum);
	/*!
	* Конструктор копирования.
	* \param other Константная ссылка на объект типа PrimitiveSample (другой объект этого типа).
	*/
	PrimitiveSample(const PrimitiveSample& other);
	/*!
	* Деструктор.
	*/
	~PrimitiveSample() override;
	/*!
	* Метод, позволяющий менять этот объект с объектом этого же типа.
	* \param other Ссылка на объект типа PrimitiveSample (другой объект этого типа).
	*/
	void swap(PrimitiveSample& other);
	/*!
	* Оператор приравнивания.
	* \param other Ссылка на объект типа PrimitiveSample (другой объект этого типа).
	*/
	PrimitiveSample& operator=(PrimitiveSample& other);
	/*!
	* Функция, возвращающая значение поля util_size (размер массива, который необходим для генерации случайной величины 
	простейшим табличным методом).
	*/
	unsigned int get_util_size() const;
	/*!
	* Функция, возвращающая элемент массива util_arr по индексу index.
	* \param index Индекс массива util_arr, целое число в пределах \f$ [0;util_size) \f$.
	*/
	unsigned int get_util_arr_ith_value(unsigned int index) const;
};