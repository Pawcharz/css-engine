#include "custom_utlis.h";

bool isProperCharacter(char character) {
	int asciiCode = character;
	int spaceAsciiCode = ' ';

	if (character == EOF || character == NEW_LINE_CHARACTER || character == TABULATOR || asciiCode == 13) {
		return true;
	}

	if (asciiCode >= spaceAsciiCode) {
		return true;
	}

	return false;
}