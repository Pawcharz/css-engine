#include "Section.h"
#include "custom_utlis.h"
#include "list_utlis.h"

Section::Section() {
	selectors = nullptr;
	attributes = nullptr;
}

Section::~Section() {
	Reset();
}


void Section::AssignSelector(MyString* selectorPtr) {
	if (selectors == nullptr) {
		selectors = new List<MyString>();
	}

	selectors->AssignElement(selectorPtr);
}

void Section::AssignAttribute(Attribute* attribute) {
	if (attributes == nullptr) {
		attributes = new List<Attribute>();
	}

	//attributes->AssignElement(attribute);
	attributes->AssignAttributeElement(attribute);
}

void Section::Reset() {
	if (selectors != nullptr) {
		delete selectors;
	}
	if (attributes != nullptr) {
		delete attributes;
	}

	selectors = nullptr;
	attributes = nullptr;

}

bool Section::IsEmpty() const {
	if (selectors == nullptr && attributes == nullptr) {
		return true;
	}
	return false;
}


int Section::GetSelectorsCount() const {
	if (selectors == nullptr) {
		return 0;
	}

	return selectors->GetElementsCount();
}

int Section::GetAttributesCount() const {
	if (attributes == nullptr) {
		return 0;
	}

	return attributes->GetElementsCount();
}

MyString* Section::GetSelector(int index) {
	if (selectors == nullptr) {
		return nullptr;
	}

	return selectors->GetElement(index);
}

Attribute* Section::GetAttribute(MyString& attributeName) {
	if (attributes == nullptr) {
		return nullptr;
	}

	return FindAttributeByName(attributeName, attributes);// attributes->FindAttributeWithName(attributeName);
}

MyString* Section::GetSelector(MyString& selectorName) {
	if (selectors == nullptr) {
		return nullptr;
	}

	return FindSelectorByName(selectorName, selectors);
}

bool Section::RemoveAttribute(MyString& attributeName) {
	return RemoveAttributeByName(attributeName, attributes);
}