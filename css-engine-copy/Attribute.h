#pragma once
#include "MyString.h"

enum AttributePart {
	NAME,
	VALUE
};

class Attribute
{
private:
	MyString* name;
	MyString* value;

public:
	Attribute();

	Attribute(Attribute& other);

	~Attribute();
	
	void AddCharacter(char character, AttributePart part);

	void Trim();

	void Reset();
};

