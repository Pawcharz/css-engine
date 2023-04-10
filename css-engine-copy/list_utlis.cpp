#include "list_utlis.h"

// FIX - Possible bug/tech debt -> dataPopulated
MyString* FindSelectorByName(MyString& selectorName, List<MyString>::ListNode* node) {

	for (int i = 0; i < node->dataPopulated; i++)
	{
		MyString current = node->data[i];
		if (current.IsEqual(selectorName)) {
			return &node->data[i];
		}
	}

	return nullptr;
}

// FIX - Possible bug/tech debt -> iterator.dataPopulated
MyString* FindSelectorByName(MyString& selectorName, List<MyString>* list) {

	List<MyString>::ListNode* iterator = list->GetHead();
	while (iterator != nullptr)
	{
		MyString* found = FindSelectorByName(selectorName, iterator);

		if (found != nullptr) {
			return found;
		}

		iterator = iterator->next;
	}

	return nullptr;
}

// FIX - Possible bug/tech debt -> dataPopulated
MyString* FindSelectorByName(MyString& selectorName, List<Section>::ListNode* node) {

	for (int i = 0; i < node->dataPopulated; i++)
	{
		Section* current = &node->data[i];
		MyString* foundSelector = current->GetSelector(selectorName);
		if (foundSelector != nullptr) {
			return foundSelector;
		}
	}

	return nullptr;
}


// FIX - Possible bug/tech debt -> dataPopulated
Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>::ListNode* node) {

	for (int i = 0; i < node->dataPopulated; i++)
	{
		Attribute current = node->data[i];
		if (current.DoesMatchName(attributeName)) {
			return &node->data[i];
		}
	}

	return nullptr;
}

// FIX - Possible bug/tech debt -> iterator.dataPopulated
Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>* list) {// Find

	List<Attribute>::ListNode* iterator = list->GetHead();
	while (iterator != nullptr)
	{
		Attribute* found = FindAttributeByName(attributeName, iterator);

		if (found != nullptr) {
			return found;
		}

		iterator = iterator->next;
	}

	return nullptr;
}

// FIX - Possible bug/tech debt -> dataPopulated
Attribute* FindAttributeByName(MyString& attributeName, List<Section>::ListNode* node) {

	for (int i = 0; i < node->dataPopulated; i++)
	{
		Section* current = &node->data[i];
		Attribute* foundAttribute = current->GetAttribute(attributeName);
		if (foundAttribute != nullptr) {
			return foundAttribute;
		}
	}

	return nullptr;
}
