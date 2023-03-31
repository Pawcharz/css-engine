#pragma once

template<typename T>
void swapCustom(T* pointerA, T* pointerB) {
	T* temp = pointerA;
	pointerA = pointerB;
	pointerB = temp;

}