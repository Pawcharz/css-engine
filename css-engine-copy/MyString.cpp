#include "MyString.h"

using namespace std;


MyString::MyString() : characters(nullptr), lengthWithBuffer(0), length(0) {

}

MyString::MyString(const char* charactersArg, int length): length(length) {
    if (length == 0) {
        lengthWithBuffer = 0;
        characters = nullptr;
        return;
    }

    lengthWithBuffer = GetLengthWithBuffer(length);
    characters = new char[lengthWithBuffer];

    for (int i = 0; i < length; i++)
    {
        characters[i] = charactersArg[i];
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

    customSwap(&characters, &tmp.characters);
    length = tmp.length;
    lengthWithBuffer = tmp.lengthWithBuffer;
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

MyString& MyString::operator+=(char character) {
    int newLength = length + 1;

    if (newLength < lengthWithBuffer) {
        characters[length] = character;
        length = newLength;
        return *this;
    }


    lengthWithBuffer = GetLengthWithBuffer(newLength);
    char* charactersTmp = new char[lengthWithBuffer];

    for (int i = 0; i < length; i++)
    {
        charactersTmp[i] = characters[i];
    }

    charactersTmp[length] = character;

    customSwap(&characters, &charactersTmp);
    length = newLength;

    delete[] charactersTmp;

    return *this;
}

int MyString::GetLengthWithBuffer(int lengthToUpdate) {
   
    int more = STRING_BUFFER_SIZE - (lengthToUpdate % STRING_BUFFER_SIZE);
    if (more == STRING_BUFFER_SIZE) {
        more = 0;
    }

    return lengthToUpdate + more;
}


bool MyString::IsEmpty() const {
    if (length > 0) {
        return false;
    }

    return true;
}

bool MyString::IsEqual(MyString& other) const {
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

bool MyString::IsEqual(const MyString& other) const {
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

bool MyString::IsEqual(const char* otherCharacters, int otherLength) const {
    if (otherLength != length) {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        if (otherCharacters[i] != characters[i]) {
            return false;
        }
    }

    return true;
}

void MyString::Reset() {
    if (characters != nullptr) {
        delete[] characters;
    }
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

    customSwap(&characters, &charactersTemp);
    length = newLength;
    lengthWithBuffer = GetLengthWithBuffer(length);

    delete[] charactersTemp;
}

int MyString::GetLength() const {
    return length;
}

ostream& operator<<(ostream& ostr, MyString& str) {
    for (int i = 0; i < str.length; i++)
    {
        ostr << str.characters[i];
    }
    return ostr;
}
ostream& operator<<(ostream& ostr, const MyString& str) {
    for (int i = 0; i < str.length; i++)
    {
        ostr << str.characters[i];
    }
    return ostr;
}


bool MyString::isNumerical() const {
    for (int i = 0; i < length; i++)
    {
        if (characters[i] - '0' < 0 || characters[i] - '0' > 9) {
            return false;
        }
    }
    return true;
}

int MyString::ToInteger() const {
    int number = 0;

    int powerOf10 = 1;

    for (int i = length-1; i >= 0; i--)
    {
        int digit = (int)(characters[i] - '0');

        if (digit < 0 || digit > 9) {
            return -1;
        }

        number += powerOf10 * digit;

        powerOf10 *= 10;
    }

    return number;
}