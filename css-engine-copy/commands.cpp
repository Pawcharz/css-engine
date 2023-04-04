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


// Possible bug/tech debt -> dataPopulated
void Reader::Command_CountAttributeOccurences() {
	MyString attributeName = commandsTemp->parts[0];

	int counter = 0; 

	List<Section>::ListNode* iterator = sectionsList->GetHead();

	while (iterator != nullptr)
	{
		//Attribute* foundAttribute = FindAttributeByName(attributeName, iterator); //iterator->FindAttributeByName(attributeName);

		for (int i = 0; i <= iterator->lastNonemptyIndex; i++)
		{
			Section* element = &iterator->data[i];
			Attribute* foundAttribute = element->GetAttribute(attributeName);// FindAttributeByName(attributeName, );

			if (foundAttribute != nullptr) {
				counter += 1;
			}

		}
		
		iterator = iterator->next;
	}

	//if (counter > 0) {
	cout << attributeName << ",A,?" << " == " << counter << endl;
	//}
}

void Reader::Command_CountSelectorOccurences() {
	MyString selectorName = commandsTemp->parts[0];

	int counter = 0;

	List<Section>::ListNode* iterator = sectionsList->GetHead();

	while (iterator != nullptr)
	{
		for (int i = 0; i <= iterator->lastNonemptyIndex; i++)
		{
			Section* element = &iterator->data[i];
			MyString* foundSelector = element->GetSelector(selectorName);// FindAttributeByName(attributeName, );
			//MyString* foundSelector = FindSelectorByName(selectorName, iterator);// iterator->FindSelectorByName(selectorName);

			if (foundSelector != nullptr) {
				counter += 1;
			}
		}

		iterator = iterator->next;
	}

	//if (counter > 0) {
	cout << selectorName << ",S,?" << " == " << counter << endl;
	//}
}


// Possible bug/tech debt -> dataPopulated
void Reader::Command_PrintAttributeValueBySelector() {
	MyString selectorName = commandsTemp->parts[0];
	MyString attributeName = commandsTemp->parts[2];

	List<Section>::ListNode* iterator = sectionsList->GetTail();

	Attribute* foundAttribute = nullptr;

	while (iterator != nullptr)
	{
		for (int i = iterator->lastNonemptyIndex; i >= 0; i--)
		{
			Section* element = &iterator->data[i];
			MyString* foundSelector = element->GetSelector(selectorName);

			if (foundSelector != nullptr) {

				Attribute* foundAttribute = element->GetAttribute(attributeName);

				if (foundAttribute != nullptr) {
					cout << selectorName << ",E," << attributeName << " == " << foundAttribute->GetValue() << endl;
					return;
				}
			}
		}

		iterator = iterator->previous;
	}

	/*if (foundAttribute != nullptr) {
		cout << selectorName << ",A," << attributeName << " == " << foundAttribute->GetValue() << endl;
	}*/
}

void Reader::Command_RemoveSection() {
	int index = commandsTemp->parts[0].ToInteger();

	bool success = sectionsList->RemoveElement(index);

	if (success) {
		cout << index << ",D,*" << " == deleted" << endl;
	}
}