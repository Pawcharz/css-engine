#pragma once
#include <iostream>

#include "List.h"
#include "Section.h"

using namespace std;

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
		MyString* command = new MyString();
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

	void ReadCommands();

	void ReadAll();


	void CleanCommands();
};

