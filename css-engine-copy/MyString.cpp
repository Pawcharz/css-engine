#include "MyString.h"

const int INVALID_INDEX = -1;

using namespace std;

MyString::MyString() : length(0), lengthWithBuffer(0), characters(nullptr) {

}

MyString::MyString(const char* CharactersArg, int length): length(length) {
    lengthWithBuffer = GetLengthWithBuffer(length);
    characters = new char[lengthWithBuffer];

    for (int i = 0; i < length; i++)
    {
        characters[i] = CharactersArg[i];
    }
}

MyString::MyString(MyString& other) : length(other.length) {
    lengthWithBuffer = GetLengthWithBuffer(length);
    characters = new char[lengthWithBuffer];

    for (int i = 0; i < length; i++) {
        characters[i] = other.characters[i];
    }
}

MyString& MyString::operator=(MyString& other) {
    MyString tmp = other;

    swap(characters, tmp.characters);

    swap(length, tmp.length);
    swap(lengthWithBuffer, tmp.lengthWithBuffer);
    return *this;
}

MyString::~MyString() {
    if (characters != nullptr) {
        delete[] characters;
    }
    
    characters = nullptr;
    length = 0;
    lengthWithBuffer = 0;
}

char& MyString::operator[](int index) {

    if (index >= length || index < 0) {
        throw "Error - index out of bounds of array";
    }

    return characters[index];
}

void MyString::operator+=(char character) {
    int newLength = length + 1;

    if (newLength < lengthWithBuffer) {
        characters[length] = character;
        length = newLength;
        return;
    }


    lengthWithBuffer = GetLengthWithBuffer(newLength);
    char* charactersTmp = new char[lengthWithBuffer];

    for (int i = 0; i < length; i++)
    {
        charactersTmp[i] = characters[i];
    }

    charactersTmp[length] = character;

    swap(characters, charactersTmp);
    length = newLength;

    delete[] charactersTmp;
}

int MyString::GetLengthWithBuffer(int lengthToUpdate) {
   
    int more = STRING_BUFFER_SIZE - (lengthToUpdate % STRING_BUFFER_SIZE);
    if (more == STRING_BUFFER_SIZE) {
        more = 0;
    }

    return lengthToUpdate + more;
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
    lengthWithBuffer = 0;

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
    lengthWithBuffer = GetLengthWithBuffer(length);

    delete[] charactersTemp;
}