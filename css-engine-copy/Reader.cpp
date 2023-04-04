#include "Reader.h"

using namespace std;

Reader::Reader() : mode{ SECTIONS } {

	sectionsTemp = new TemporarySections();

	commandsTemp = new TemporaryCommands();

	currentChar = ' ';

	sectionsList = new List<Section>(BULK_SECTIONS_SIZE);
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

		if (sectionsTemp->selector->IsEqual(COMMANDS_READER_ACTIVATOR)) {
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
		sectionsTemp->attribute->Trim();

		if (sectionsTemp->attribute->IsEmpty() == false) {

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


void Reader::ExecuteCommand() {
	if (commandsTemp->parts[0].IsEqual(COMMAND_COUNT) && commandsTemp->parts[1].IsEmpty()) {
		Command_CountSections();
	}
	else if(commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("S", 1) && commandsTemp->parts[2].IsEqual("?", 1)) {
		Command_CountSelectors();
	}
	else if (commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("A", 1) && commandsTemp->parts[2].IsEqual("?", 1)) {
		Command_CountAttributes();
	}
	else if (commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("S", 1) && commandsTemp->parts[2].isNumerical()) {
		Command_PrintSelector();
	}
	else if (commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("A", 1) && !commandsTemp->parts[2].isNumerical()) {
		Command_PrintAttributeValue();
	}
	else if (!commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("S", 1) && commandsTemp->parts[2].IsEqual("?", 1)) {
		Command_CountSelectorOccurences();
		// PrintCountOfSelectorOccurences(name)
		//cout << "PrintCountOfSelectorOccurences(name)" << endl;
	}
	else if (!commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("A", 1) && commandsTemp->parts[2].IsEqual("?", 1)) {
		Command_CountAttributeOccurences();
		// PrintCountOfAttribute(name)
		//cout << "PrintCountOfAttribute(name)" << endl;
	}
	else if (!commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("E", 1) && !commandsTemp->parts[2].isNumerical()) {
		Command_PrintAttributeValueBySelector();
		// PrintValueOfAttributeForSelector(attributeName, selectorName)
		//cout << "PrintValueOfAttributeForSelector(attributeName, selectorName)" << endl;
	}
	else if (commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("D", 1) && commandsTemp->parts[2].IsEqual("*", 1)) {
		Command_RemoveSection();
		// RemoveSectionWithNumber(number)
		//cout << "RemoveSectionWithNumber(number)" << endl;
	}
	else if (commandsTemp->parts[0].isNumerical() && commandsTemp->parts[1].IsEqual("D", 1) && !commandsTemp->parts[2].isNumerical()) {
		// RemoveAttributeFromSection(sectionIndex, attributeName)
		cout << "RemoveAttributeFromSection(sectionIndex, attributeName)" << endl;
	}
}

void Reader::ReadCommands() {
	if (commandsTemp->parts[0].IsEqual(SECTIONS_READER_ACTIVATOR) ) {
		mode = SECTIONS;

		CleanCommands();
		return;
	}

	else if (currentChar == NEW_LINE_CHARACTER) {
		//cout << "--->" << commandsTemp->parts[0] << "," << commandsTemp->parts[1] << "," << commandsTemp->parts[2] << endl;
		ExecuteCommand();

		CleanCommands();

	}
	else if (currentChar == COMMAND_ARG_SEPARATOR && commandsTemp->currentPartIndex < 2) {
		commandsTemp->currentPartIndex += 1;
	}
	else {
		commandsTemp->parts[commandsTemp->currentPartIndex] += currentChar;
	}
}

void Reader::ReadAll() {
	//mode = COMMANDS; //Remove after testing

	//currentChar = getchar();

	while (currentChar != EOF) {

		currentChar = getchar();

		if (currentChar != TABULATOR) {
			if (mode == SECTIONS) {
				ReadSections();
			}
			else {
				ReadCommands();
			}
		}
	};
}

void Reader::CleanCommands() {
	for (int i = 0; i < 3; i++)
	{
		commandsTemp->parts[i].Reset();
	}
	commandsTemp->currentPartIndex = 0;
}