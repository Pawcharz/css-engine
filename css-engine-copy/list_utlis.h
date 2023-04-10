#pragma once

#include "List.h"
#include "MyString.h"
#include "Attribute.h"
#include "Section.h"


// FIX - Possible bug/tech debt -> dataPopulated
MyString* FindSelectorByName(MyString& selectorName, List<MyString>::ListNode* node);

// FIX - Possible bug/tech debt -> iterator.dataPopulated
MyString* FindSelectorByName(MyString& selectorName, List<MyString>* list);

// FIX - Possible bug/tech debt -> iterator.dataPopulated
MyString* FindSelectorByName(MyString& selectorName, List<Section>::ListNode* node);


// FIX - Possible bug/tech debt -> dataPopulated
Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>::ListNode* node);

// FIX - Possible bug/tech debt -> iterator.dataPopulated
Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>* list);

// FIX - Possible bug/tech debt -> iterator.dataPopulated
Attribute* FindAttributeByName(MyString& attributeName, List<Section>::ListNode* node);