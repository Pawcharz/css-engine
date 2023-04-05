#include "custom_utlis.h"

bool shouldIgnoreCharacter(char character) {
	int asciiCode = character;
	int spaceAsciiCode = ' ';

	if (character == TABULATOR) {
		return true;
	}

	if (character == EOF || character == NEW_LINE_CHARACTER) {
		return false;
	}

	if (asciiCode >= spaceAsciiCode) {
		return false;
	}

	return true;
}