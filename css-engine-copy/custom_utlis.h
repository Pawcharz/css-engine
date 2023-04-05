#pragma once

#include <iostream>

using namespace std;

const char SPACE_CHARACTER = ' ';
const char NEW_LINE_CHARACTER = '\n';
const char TABULATOR = '\t';


const int INVALID_INDEX = -1;

template<typename T>
void customSwap(T** pointerA, T** pointerB) {
	T* temp = *pointerA;
	*pointerA = *pointerB;
	*pointerB = temp;
}

bool shouldIgnoreCharacter(char character);