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

enum AttributeReadingStage {
	NAME,
	VALUE
};

class Reader
{
private:
	struct TemporarySections {
		Section* section = new Section();
		SectionReadingStage sectionReadingStage = SELECTORS;
		MyString* selector = new MyString();

		AttributeReadingStage attributeReadingStage = NAME;
		MyString* attributeName = new MyString();
		MyString* attributeValue = new MyString();
	}* sectionsTemp;

	struct TemporaryCommands {
		MyString* command = new MyString();
	}* commandsTmp;

	ReaderMode mode;

	char currentChar;

	List<Section>* sectionList;


	//int CountSections();


public:
	Reader();

	void ReadSections();

	void ReadSelectors();
	void ReadAttributes();

	void ReadCommands();


	void ReadAll();


	//void CleanCommands();
};

