#include "custom_utlis.h";

int customModulo(int nr1, int nr2) {
	if (nr2 == 0) {
		return 0;
	}

	return nr1 % nr2;
}