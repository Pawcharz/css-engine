#pragma once
#include "List.h"
#include "MyString.h"
#include "Attribute.h"
#include "custom_utlis.h"


class Section
{
private:
	List<MyString>* selectors;
	List<Attribute>* attributes;

public:
	Section();

	~Section();


	//void AddSelector(MyString& selector);

	//void AddAttribute(Attribute& attribute);


	void AssignSelector(MyString* selectorPtr);

	void AssignAttribute(Attribute* attribute);

	void Reset();


	int GetSelectorsCount();

	int GetAttributesCount();


	MyString* GetSelector(int index);

	Attribute* GetAttribute(MyString& attributeName);



	MyString* GetSelector(MyString& selectorName);
};

