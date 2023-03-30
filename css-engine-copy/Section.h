#pragma once
#include "List.h"
#include "MyString.h"
#include "Attribute.h"


class Section
{
private:
	List<MyString>* selectors;
	List<Attribute>* attributes;

public:
	Section();

	Section(Section& other);

	~Section();


	void AddSelector(MyString& selector);

	void AddAttribute(Attribute& attribute);

	void Reset();
};

