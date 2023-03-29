#include "Section.h"

Section::Section() {
	selectors = nullptr;
	attributes = nullptr;
}

Section::~Section() {
	delete selectors;
	delete attributes;

	selectors = nullptr;
	attributes = nullptr;
}

void Section::AddSelector(MyString& selector) {
	selectors->AddNode(selector);
}