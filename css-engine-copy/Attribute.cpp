#include "Attribute.h"

Attribute::Attribute() {
	name = new MyString();
	value = new MyString();
}

Attribute::Attribute(Attribute& other) {
	name = new MyString(*other.name);
	value = new MyString(*other.value);
}

Attribute& Attribute::operator=(Attribute& other) {
	Attribute tmp = other;

	swap(name, tmp.name);

	swap(value, tmp.value);
	return *this;
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


bool Attribute::IsEmpty() {
	if (name->GetLength() == 0 && value->GetLength() == 0) {
		return true;
	}

	return false;
}

