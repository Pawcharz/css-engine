#include "Section.h"

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

	attributes->AssignElement(attribute);
}

