#pragma once
#include <iostream>

#include "List.h"
#include "Section.h"
#include "custom_utlis.h"
#include "list_utlis.h"

#include "MyString.h"
#include "List.h"

const int BULK_SECTIONS_SIZE = 8;

const char CSS_SECTION_OPEN_CHAR = '{';
const char CSS_SECTION_CLOSE_CHAR = '}';

const char SELECTORS_SEPARATOR = ',';
const char ATTRIBUTE_NAME_VALUE_SEPARATOR = ':';
const char ATTRIBUTE_SEPARATOR = ';';

const char COMMAND_ARG_SEPARATOR = ',';


const MyString SECTIONS_READER_ACTIVATOR("****", 4);
const MyString COMMANDS_READER_ACTIVATOR("????", 4);

const MyString COMMAND_COUNT("?", 1);

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
    }*sectionsTemp;

    struct TemporaryCommands {
        MyString* parts = new MyString[COMMAND_PARTS_COUNT]();

        int currentPartIndex = 0;
    }*commandsTemp;

    ReaderMode mode;

    char currentChar;

    List<Section>* sectionsList;


    void Command_CountSections() const;


    void Command_CountSelectors();

    void Command_CountAttributes();

    void Command_PrintSelector();

    void Command_PrintAttributeValue();


    void Command_CountSelectorOccurences();

    void Command_CountAttributeOccurences();

    void Command_PrintAttributeValueBySelector();


    void Command_RemoveSection();

    void Command_RemoveAttribute();

public:
    Reader();

    ~Reader();

    void ReadSections();

    void ReadSelectors();
    void ReadAttributes();

    void ExecuteCommand();
    void ReadCommands();

    void ReadAll();


    void CleanCommands();
};
