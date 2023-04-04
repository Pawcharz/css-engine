#include "Section.h"
#include "custom_utlis.h"
#include "list_utlis.h"

Section::Section() {
	selectors = nullptr;
	attributes = nullptr;
}

//Section::Section(Section& other) {
//	selectors = new List<MyString>(*other.selectors);
//	attributes = new List<Attribute>(*other.attributes);
//}

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

bool Section::IsEmpty() {
	if (selectors == nullptr && attributes == nullptr) {
		return true;
	}
	return false;
}

Section::~Section() {
	Reset();
}

//void Section::AddSelector(MyString& selector) {
//	if (selectors == nullptr) {
//		selectors = new List<MyString>();
//	}
//
//	selectors->AddElement(selector);
//}

//void Section::AddAttribute(Attribute& attribute) {
//	if (attributes == nullptr) {
//		attributes = new List<Attribute>();
//	}
//
//	attributes->AddElement(attribute);
//}

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

int Section::GetSelectorsCount() {
	if (selectors == nullptr) {
		return 0;
	}

	return selectors->GetElementsCount();
}

int Section::GetAttributesCount() {
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