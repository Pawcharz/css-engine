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

	Attribute& operator=(Attribute& other);
	
	void AddCharacter(char character, AttributePart part);

	void Trim();

	void Reset();


	bool IsEmpty();

	bool DoesMatchName(Attribute* name);
	bool DoesMatchName(MyString& name);



	MyString& GetValue();
};

