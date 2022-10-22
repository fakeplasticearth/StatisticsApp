#include "pch.h"
#include "PrimitiveSample.h"
#include "ChenSample.h"
#include "Chi2Histogram.h"

/*!
 *  Пример: вычисление p-value для критерия согласия Хи-квадрат.
*/
int main() {

	//Необходимо задать seed для генерации случайных величин 
	rninit(442);
	// Задаются параметры распределения для нулевой гипотезы (H_0)
	double probs_h0[5] = { 10. / 100, 30. / 100, 40. / 100, 5. / 100, 15. / 100 };
	double values_h0[5] = { 3.0, 3.5, 4.0, 4.5, 5.0 };
	Distribution d0(values_h0, probs_h0, 5);

	//Задаются параметры распределения для проверки гипотезы
	double probs[5] = { 10. / 110, 35. / 110, 40. / 110, 5. / 110, 20. / 110 };
	double values[5] = { 3.0, 3.5, 4.0, 4.5, 5.0 };
	Distribution d(values, probs, 5);

	//Для моделирования используем метод Чена
	int m = 5;
	Sample * s = new ChenSample(d, 5);
	Chi2Histogram chi2(*s, d0);

	//Вычисляем p-value
	double pval = chi2.get_pvalue();
	return 0;
}