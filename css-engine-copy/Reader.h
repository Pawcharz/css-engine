#pragma once
#include <iostream>

#include "List.h"
#include "Section.h"
#include "custom_utlis.h"

using namespace std;

const int COMMAND_PARTS_COUNT = 3;


enum ReaderMode {
	SECTIONS,
	COMMANDS
};

enum SectionReadingStage {
	SELECTORS,
	ATTRIBUTES
};

class Reader
{
private:
	struct TemporarySections {
		Section* section = new Section();
		SectionReadingStage sectionReadingStage = SELECTORS;
		MyString* selector = new MyString();

		AttributePart attributeReadingStage = NAME;

		Attribute* attribute = new Attribute();
	}* sectionsTemp;

	struct TemporaryCommands {
		MyString* parts = new MyString[COMMAND_PARTS_COUNT]();

		int currentPartIndex = 0;
	}* commandsTemp;

	ReaderMode mode;

	char currentChar;

	List<Section>* sectionsList;


	//int CountSections();


public:
	Reader();

	void ReadSections();

	void ReadSelectors();
	void ReadAttributes();

	void ExecuteCommand();
	void ReadCommands();

	void ReadAll();


	void CleanCommands();
};

