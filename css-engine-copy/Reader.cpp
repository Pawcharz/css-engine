#include "Reader.h"
#include "MyString.h"
#include "List.h"
#include "MyString.h"


const char CSS_SECTION_OPEN_CHAR = '{';
const char CSS_SECTION_CLOSE_CHAR = '}';

const char SELECTORS_SEPARATOR = ',';
const char ATTRIBUTE_NAME_VALUE_SEPARATOR = ':';
const char ATTRIBUTE_SEPARATOR = ';';

const MyString SECTIONS_READER_ACTIVATOR_FULL("****", 4); // How to add const here?
const MyString COMMANDS_READER_ACTIVATOR_FULL("????", 4);

const MyString COMMAND_COUNT("?", 1);

Reader::Reader() : mode{ SECTIONS } {

	sectionsTemp = new TemporarySections();

	commandsTemp = new TemporaryCommands();

	currentChar = ' ';

	sectionsList = new List<Section>();
}


void Reader::ReadSelectors() {

	if (currentChar == SELECTORS_SEPARATOR || currentChar == CSS_SECTION_OPEN_CHAR) {
		sectionsTemp->selector->TrimEdgeWhiteSpaces();

		if (sectionsTemp->selector->IsEmpty()) {
			sectionsTemp->selector = new MyString("*", 1);
		}

		sectionsTemp->section->AssignSelector(sectionsTemp->selector);

		sectionsTemp->selector = new MyString();

		if (currentChar == CSS_SECTION_OPEN_CHAR) {

			sectionsTemp->sectionReadingStage = ATTRIBUTES;
		}
	}
	else {
		*(sectionsTemp->selector) += currentChar;

		if (sectionsTemp->selector->IsEqual(COMMANDS_READER_ACTIVATOR_FULL)) {
			mode = COMMANDS;
			return;
		}
	}
}

void Reader::ReadAttributes() {

	if (currentChar == ATTRIBUTE_SEPARATOR) {


		sectionsTemp->attribute->Trim();

		sectionsTemp->section->AssignAttribute(sectionsTemp->attribute);

		sectionsTemp->attribute = new Attribute();

		sectionsTemp->attributeReadingStage = NAME;

	}
	else if (currentChar == CSS_SECTION_CLOSE_CHAR) {
		if (sectionsTemp->attribute->IsEmpty() == false) {
			sectionsTemp->attribute->Trim();

			sectionsTemp->section->AssignAttribute(sectionsTemp->attribute);

			sectionsTemp->attribute = new Attribute();

			sectionsTemp->attributeReadingStage = NAME;
		}

		sectionsTemp->sectionReadingStage = SELECTORS;

		sectionsList->AssignElement(sectionsTemp->section);
		sectionsTemp->section = new Section();
	}
	else if (currentChar == ATTRIBUTE_NAME_VALUE_SEPARATOR) {
		sectionsTemp->attributeReadingStage = VALUE;
	}
	else {
		sectionsTemp->attribute->AddCharacter(currentChar, sectionsTemp->attributeReadingStage);
	}

	/*if (currentChar == ATTRIBUTE_SEPARATOR || currentChar == CSS_SECTION_CLOSE_CHAR) {


		sectionsTemp->attribute->Trim();

		sectionsTemp->section->AssignAttribute(sectionsTemp->attribute);

		sectionsTemp->attribute = new Attribute();

		sectionsTemp->attributeReadingStage = NAME;

		if (currentChar == CSS_SECTION_CLOSE_CHAR) {

			sectionsTemp->sectionReadingStage = SELECTORS;

			sectionsList->AssignElement(sectionsTemp->section);
			sectionsTemp->section = new Section();
		}
	}
	else if (currentChar == ATTRIBUTE_NAME_VALUE_SEPARATOR) {
		sectionsTemp->attributeReadingStage = VALUE;
	}
	else {
		sectionsTemp->attribute->AddCharacter(currentChar, sectionsTemp->attributeReadingStage);
	}*/
}


void Reader::ReadSections() {
	if (currentChar == NEW_LINE_CHARACTER) {
		return;
	}

	if (sectionsTemp->sectionReadingStage == SELECTORS) {
		ReadSelectors();
	}
	else {
		ReadAttributes();
	}
}

void Reader::ReadCommands() {

	if (currentChar == NEW_LINE_CHARACTER) {
		if (commandsTemp->command->IsEqual(COMMAND_COUNT))
		{
			int size = sectionsList->GetElementsCount();

			cout << COMMAND_COUNT << " == " << size << endl;
			CleanCommands();
		}
	}
	else {
		*(commandsTemp->command) += currentChar;
	}
}

void Reader::ReadAll() {
	
	currentChar = getchar();

	while (currentChar != EOF) {


		if (mode == SECTIONS) {
			ReadSections();
		}
		else {
			ReadCommands();
		}

		currentChar = getchar();
	};
}


void Reader::CleanCommands() {
	delete commandsTemp->command;
	commandsTemp->command = new MyString();
}