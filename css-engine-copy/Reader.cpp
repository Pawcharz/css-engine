#include "Reader.h"
//#include "CssSectionListNode.h"
//#include "CssSelectorNode.h"
#include "MyString.h"
#include "List.h"
#include "MyString.h"


const char CSS_SECTION_OPEN_CHAR = '{';
const char CSS_SECTION_CLOSE_CHAR = '}';

const char SELECTORS_SEPARATOR = ',';
const char ATTRIBUTE_NAME_VALUE_SEPARATOR = ':';
const char ATTRIBUTE_SEPARATOR = ';';

//MyString SECTIONS_READER_ACTIVATOR_FULL("****", 4); // How to add const here?
const MyString COMMANDS_READER_ACTIVATOR_FULL("????", 4);

//MyString COMMAND_COUNT('?');

// Probably can be written shorter
Reader::Reader() : mode{ SECTIONS } {

	sectionsTemp = new TemporarySections();

	commandsTmp = new TemporaryCommands();

	currentChar = ' ';

	sectionList = new List<Section>();
}


void Reader::ReadSelectors() {

	if (currentChar == SELECTORS_SEPARATOR || currentChar == CSS_SECTION_OPEN_CHAR) {
		if (sectionsTemp->selector->IsEmpty()) {
			sectionsTemp->selector = new MyString("*", 1);
		}

		sectionsTemp->section->AddSelector(*sectionsTemp->selector);

		sectionsTemp->selector->Reset();

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
	/*if (currentChar == ATTRIBUTE_SEPARATOR || currentChar == CSS_SECTION_CLOSE_CHAR) {

		sectionsTemp->attributeName->TrimEdgeWhiteSpaces();
		sectionsTemp->attributeValue->TrimEdgeWhiteSpaces();
		CssAttributeNode attributeNode = { *sectionsTemp->attributeName, *sectionsTemp->attributeValue };

		sectionsTemp->section->AddAttribute(attributeNode);

		sectionsTemp->attributeName = new MyString();
		sectionsTemp->attributeValue = new MyString();
		sectionsTemp->attributeReadingStage = NAME;

		if (currentChar == CSS_SECTION_CLOSE_CHAR) {

			sectionsTemp->sectionReadingStage = SELECTORS;

			rootSectionListNode->AddSection(*(sectionsTemp->section));

			sectionsTemp->section = new CssSection();

		}
	}
	else if (currentChar == ATTRIBUTE_NAME_VALUE_SEPARATOR) {
		sectionsTemp->attributeReadingStage = VALUE;
	}
	else {

		if (sectionsTemp->attributeReadingStage == NAME) {
			*(sectionsTemp->attributeName) += currentChar;
		}
		else {
			*(sectionsTemp->attributeValue) += currentChar;
		}

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

	/*if (currentChar == NEW_LINE_CHARACTER) {
		if (commandsTemp->command->IsEqual(COMMAND_COUNT))
		{
			int size = rootSectionListNode->GetListSize();

			cout << COMMAND_COUNT << " == " << size << endl;
			CleanCommands();
		}
	}
	else {
		*(commandsTemp->command) += currentChar;
	}*/
}


void Reader::ReadAll() {

	while (true) {

		currentChar = getchar();

		if (mode == SECTIONS) {
			ReadSections();
		}
		else {
			ReadCommands();
		}
	};
}


//void Reader::CleanCommands() {
//	delete commandsTemp->command;
//	commandsTemp->command = new MyString();
//}