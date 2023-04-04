#include "list_utlis.h"


MyString* FindSelectorByName(MyString& selectorName, List<MyString>::ListNode* node) {

	for (int i = 0; i <= node->lastNonemptyIndex; i++)
	{
		MyString current = node->data[i];
		if (current.IsEqual(selectorName)) {
			return &node->data[i];
		}
	}

	return nullptr;
}

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

MyString* FindSelectorByName(MyString& selectorName, List<Section>::ListNode* node) {

	for (int i = 0; i <= node->lastNonemptyIndex; i++)
	{
		Section* current = &node->data[i];
		MyString* foundSelector = current->GetSelector(selectorName);
		if (foundSelector != nullptr) {
			return foundSelector;
		}
	}

	return nullptr;
}


Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>::ListNode* node) {

	for (int i = 0; i <= node->lastNonemptyIndex; i++)
	{
		Attribute current = node->data[i];
		if (current.DoesMatchName(attributeName)) {
			return &node->data[i];
		}
	}

	return nullptr;
}

Attribute* FindAttributeByName(MyString& attributeName, List<Attribute>* list) {

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

Attribute* FindAttributeByName(MyString& attributeName, List<Section>::ListNode* node) {

	for (int i = 0; i <= node->lastNonemptyIndex; i++)
	{
		Section* current = &node->data[i];
		Attribute* foundAttribute = current->GetAttribute(attributeName);
		if (foundAttribute != nullptr) {
			return foundAttribute;
		}
	}

	return nullptr;
}

bool RemoveAttributeByName(MyString& attributeName, List<Attribute>* list) {
	int index = 0;
	List<Attribute>::ListNode* iterator = list->GetHead();
	while (iterator != nullptr)
	{
		for (int i = 0; i <= iterator->lastNonemptyIndex; i++)
		{
			if (!iterator->data[i].IsEmpty()) {

				if (iterator->data[i].DoesMatchName(attributeName)) {

					
					//list->RemoveElement(index); // FIX - could be optimised -> repeating the same code 2 times
					return iterator->RemoveElement(i);
				}

				index += 1;
			}
		}

		iterator = iterator->next;
	}

	return false;
}