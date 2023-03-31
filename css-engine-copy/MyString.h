#pragma once
#include <iostream>
#include "custom_utlis.h"

using namespace std;

const char SPACE_CHARACTER = ' ';
const char NEW_LINE_CHARACTER = '\n';
const int STRING_BUFFER_SIZE = 5;

using namespace std;

class MyString
{
private:
	char* characters;

	int lengthWithBuffer;
	int length;

	friend ostream& operator<<(ostream& ostr, const MyString& str);
	friend ostream& operator<<(ostream& ostr, MyString& str);

	int GetLengthWithBuffer(int lengthToUpdate);

public:
	MyString();

	MyString(const char* CharactersArg, int length);

	MyString(MyString& other);

	~MyString();


	MyString& operator=(MyString& other);

	void operator+=(char character);

	char& operator[](int index);

	bool IsEmpty();

	bool IsEqual(MyString& other);

	bool IsEqual(const MyString& other);

	void Reset();

	void TrimEdgeWhiteSpaces();

	int GetLength();
};

