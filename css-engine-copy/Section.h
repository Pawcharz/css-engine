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


    void AssignSelector(MyString* selectorPtr);

    void AssignAttribute(Attribute* attribute);

    void Reset();

    bool IsEmpty() const;


    int GetSelectorsCount() const;

    int GetAttributesCount() const;


    MyString* GetSelector(int index);

    Attribute* GetAttribute(MyString& attributeName);


    MyString* GetSelector(MyString& selectorName);

    bool RemoveAttribute(MyString& attributeName);
};
