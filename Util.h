#pragma once
#include "pch.h"

#define NOT_A_NUMBER 0
#define NOT_AN_INT 1
#define EMPTY_BOX 2
#define INVALID_FREQ 3
#define COINCIDING_VALUES 4
#define INVALID_SAMPLE_SIZE 5
#define NOT_AN_INT_SAMPLE_SIZE 6
#define TOO_SMALL_PVALUE_SAMPLE_SIZE 7
#define TOO_BIG_PVALUE_SAMPLE_SIZE 8
#define NOT_AN_INT_PVALUE_SAMPLE_SIZE 9
#define TOO_SMALL_MAX_SAMPLE_SIZE 10
#define NOT_AN_INT_MAX_SAMPLE_SIZE 11
#define SMALL_ALPHA 13
#define BIG_ALPHA 14
#define UNSPECIFIED_VALUE -1

/*!
* Элемент сгруппированной выборки, пара частота и значение.
*/
struct point_emp {
	int freq;
	double value;
};

/*!
* Структура, с помощью которой задается произвольное дискретное распределение, пара вероятность и значение.
*/
struct point_th {
	double freq, value;
};