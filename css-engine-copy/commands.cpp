#include "Reader.h"

void Reader::Command_CountSections() {
	int count = sectionsList->GetElementsCount();

	if (count > 0) {
		cout << COMMAND_COUNT << " == " << count << endl;
	}
}

void Reader::Command_CountSelectors() {
	int sectionNumber = commandsTemp->parts[0].ToInteger();

	Section* found = sectionsList->GetElement(sectionNumber - 1);
	if (found == nullptr) {
		return;
	}

	int selectorCount = found->GetSelectorsCount();
	if (selectorCount > 0) {
		cout << sectionNumber << ",S,? == " << selectorCount << endl;
	}
}

void Reader::Command_CountAttributes() {
	int sectionNumber = commandsTemp->parts[0].ToInteger();

	Section* found = sectionsList->GetElement(sectionNumber - 1);
	if (found == nullptr) {
		return;
	}

	int attributeCount = found->GetAttributesCount();
	if (attributeCount > 0) {
		cout << sectionNumber << ",A,? == " << attributeCount << endl;
	}
}

void Reader::Command_PrintSelector() {
	int sectionNumber = commandsTemp->parts[0].ToInteger();
	int selectorIndex = commandsTemp->parts[2].ToInteger();

	Section* foundSection = sectionsList->GetElement(sectionNumber - 1);
	if (foundSection == nullptr) {
		return;
	}

	MyString* foundSelector = foundSection->GetSelector(selectorIndex - 1);
	if (foundSelector == nullptr) {
		return;
	}

	cout << sectionNumber << ",S," << selectorIndex << " == " << *foundSelector << endl;
}

void Reader::Command_PrintAttributeValue() {
	int sectionNumber = commandsTemp->parts[0].ToInteger();
	MyString attributeName = commandsTemp->parts[2];

	Section* foundSection = sectionsList->GetElement(sectionNumber - 1);
	if (foundSection == nullptr) {
		return;
	}

	Attribute* foundAttribute = foundSection->GetAttribute(attributeName);
	if (foundAttribute == nullptr) {
		return;
	}

	cout << sectionNumber << ",A," << attributeName << " == " << foundAttribute->GetValue() << endl;
}

void Reader::Command_CountAttributeOccurences() {
	MyString selectorName = commandsTemp->parts[0];

	int counter = 0; 

	/*while (iterator != nullptr)
	{
		counter += iterator->dataPopulated;
		iterator = iterator->next;
	}*/

	if (counter > 0) {
		cout << selectorName << ",S,?" << " == " << counter << endl;
	}
}