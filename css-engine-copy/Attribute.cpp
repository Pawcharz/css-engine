#include "Attribute.h"

Attribute::Attribute() {
	name = new MyString();
	value = new MyString();
}

Attribute::Attribute(Attribute& other) {
	name = new MyString(*other.name);
	value = new MyString(*other.value);
}

void Attribute::Reset() {
	name->Reset();
	value->Reset();
}

Attribute::~Attribute() {
	Reset();
}

void Attribute::AddCharacter(char character, AttributePart part) {
	if (part == NAME) {
		*name += character;
	}
	else {
		*value += character;
	}
}

void Attribute::Trim() {
	name->TrimEdgeWhiteSpaces();
	value->TrimEdgeWhiteSpaces();
}

