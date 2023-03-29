#include "MyString.h"

const int INVALID_INDEX = -1;

using namespace std;

MyString::MyString() : length(0), characters(nullptr) {

}

MyString::MyString(const char* existingCharacters, int length) :length(length) {

    characters = new char[length];

    for (int i = 0; i < length; i++)
    {
        characters[i] = existingCharacters[i];
    }
}

MyString::MyString(MyString& other) : length(other.length) {
    characters = new char[length];

    for (int i = 0; i < length; i++) {
        characters[i] = other.characters[i];
    }
}

//MyString& MyString::operator=(MyString& other) {
//    MyString tmp = other;
//
//    swap(characters, tmp.characters);
//
//    swap(length, tmp.length);
//    return *this;
//}

MyString::~MyString() {
    if (characters != nullptr) {
        delete[] characters;
    }
    
    characters = nullptr;
    length = 0;
}

char& MyString::operator[](int index) {

    if (index >= length || index < 0) {
        throw "Error - index out of bounds of array";
    }

    return characters[index];
}

void MyString::operator+=(char character) {
    int newLength = length + 1;

    char* charactersTmp = new char[newLength];

    for (int i = 0; i < length; i++)
    {
        charactersTmp[i] = characters[i];
    }

    charactersTmp[newLength - 1] = character;

    swap(characters, charactersTmp);
    length = newLength;

    delete[] charactersTmp;
}


bool MyString::IsEmpty() {
    if (length > 0) {
        return false;
    }

    return true;
}

bool MyString::IsEqual(MyString& other) {
    if (other.length != length) {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        if (other[i] != characters[i]) {
            return false;
        }
    }

    return true;
}

bool MyString::IsEqual(const MyString& other) {
    if (other.length != length) {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        if (other.characters[i] != characters[i]) {
            return false;
        }
    }

    return true;
}

void MyString::Reset() {
    delete[] characters;
    characters = nullptr;
    length = 0;

    return;
}

void MyString::TrimEdgeWhiteSpaces() {
    if (length == 0) {
        return;
    }
    int firstIndex = INVALID_INDEX;

    int lastIndex = INVALID_INDEX;


    for (int i = 0; i < length; i++)
    {
        if (characters[i] != SPACE_CHARACTER && characters[i] != NEW_LINE_CHARACTER) {
            firstIndex = i;
            break;
        }
    }
    for (int i = length - 1; i >= 0; i--)
    {
        if (characters[i] != SPACE_CHARACTER && characters[i] != NEW_LINE_CHARACTER) {
            lastIndex = i;
            break;
        }
    }

    if (firstIndex == INVALID_INDEX || lastIndex == INVALID_INDEX) {
        Reset();
        return;
    }

    int newLength = lastIndex - firstIndex + 1;

    if (newLength <= 0) {
        Reset();
        return;
    }

    char* charactersTemp = new char[newLength];

    for (int i = 0; i < newLength; i++)
    {
        charactersTemp[i] = characters[firstIndex + i];
    }

    swap(characters, charactersTemp);
    length = newLength;

    delete[] charactersTemp;
}