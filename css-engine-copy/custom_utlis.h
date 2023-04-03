#pragma once

#include "MyString.h"

template<typename T>
void customSwap(T** pointerA, T** pointerB) {
	T* temp = *pointerA;
	*pointerA = *pointerB;
	*pointerB = temp;
}