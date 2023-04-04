#pragma once

template<typename T>
void customSwap(T** pointerA, T** pointerB) {
	T* temp = *pointerA;
	*pointerA = *pointerB;
	*pointerB = temp;
}

int customModulo(int nr1, int nr2);