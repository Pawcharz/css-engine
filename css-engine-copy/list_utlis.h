#pragma once

#include "List.h"
#include "MyString.h"
#include "Attribute.h"
#include "Section.h"


MyString* FindSelectorByName(MyString& selectorName, List<MyString>::ListNode* node);

MyString* FindSelectorByName(MyString& selectorName, List<MyString>* list);

MyString* FindSelectorByName(MyString& selectorName, List<Section>::ListNode* node);


Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>::ListNode* node);

Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>* list);

Attribute* FindAttributeByName(MyString& attributeName, List<Section>::ListNode* node);



bool RemoveAttributeByName(MyString& attributeName, List<Attribute>* list);
