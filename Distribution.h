#pragma once

#include "pch.h"
#include <string>

/*!
* \brief Класс, содержащий параметры дискретного распределения.
* \details Параметры хранятся в виде массива вероятностей и массива значений. Значения должны иметь вид \f$ \frac{k_i}{N} \f$, 
где N > 0 - натуральное число, причем \f$ \sum_{i = 1}^{n}k_i = N\f$, n - мощность множества значений случайной величины.
*/
class Distribution {
	/// \brief Мощность множества значений случайной величины.
	unsigned int size = 0;
	/// \brief Указатель на массив значений, массив имеет размер size.
	double* values = nullptr;
	/// \brief Указатель на массив вероятностей, массив имеет размер size.
	double *probs = nullptr;
public:
	/// \brief Пустой конструктор.
	Distribution() {}
	/*!
	* Конструктор, который использует массив значений и массив вероятностей.
	* \param values_ Указатель на массив значений. Массив имеет длину size_.
	* \param p Указатель на массив вероятностей. Массив имеет длину size_.
	* \param size_ Длина массивов значений и вероятностей.
	*/
	Distribution(double* values_, double* p, int size_);
	/*!
	* Конструктор копирования.
	* \param distr Константная ссылка на объект типа Distribution (другой объект этого типа).
	*/
	Distribution(const Distribution& distr);
	/*!
	* Конструктор перемещения.
	*/
	Distribution(Distribution&& distr);
	/*!
	* Деструктор.
	*/
	~Distribution();
	/*!
	* Функция, которая меняет этот объект с другим объектом типа Distribution.
	* \param distr Ссылка на объект типа Distribution (другой объект этого типа).
	*/
	void swap(Distribution& distr);
	/*!
	* Оператор приравнивания
	* \param distr Объект типа Distribution (другой объект этого типа).
	*/
	Distribution& operator=(Distribution distr);
	/*!
	* Функция, возвращающая размер распределения, поле size (мощность множества значений).
	*/
	unsigned int get_size() const;
	/*!
	* Функция, возвращающая значение по индексу.
	* \param index Индекс массива значений, целое число в пределах \f$ [0;size) \f$.
	*/
	double get_ith_value(unsigned int index) const;
	/*!
	* Функция, возвращающая вероятность по индексу.
	* \param index Индекс массива вероятностей, целое число в пределах \f$ [0;size) \f$.
	*/
	double get_ith_freq(unsigned int index) const;
	/*!
	* \brief Функция, заполняющая поля с помощью массивов значений и абсолютных частот.
	* \param values_ Указатель на массив значений, массив имеет длину size_.
	* \param abs_freqs_ Указатель на массив абсолютных частот, массив имеет длину size_.
	* \param size_ Размер массивов значений и абсолютных частот.
	* \param sum_freqs_ Сумма абсолютных частот.
	* \details Веростности вычисляются внутри класса по формуле \f$ p_i = \frac{k_i}{N}\f$, где \f$ k_i\f$ - абсолютная частота,
	* \f$ N \f$ - сумма абсолютных частот.
	*/
	void set_parameters(double* values_, int* abs_freqs_, int size_, int sum_freqs_);
	/*!
	* Функция, заполняющая поля глубоким копированием полей другого объекта типа Distribution.
	* \param distr Константная ссылка на объект типа Distribution (другой объект этого типа).
	*/
	void set_parameters(const Distribution& distr);
};
