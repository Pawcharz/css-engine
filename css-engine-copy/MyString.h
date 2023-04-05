#pragma once
#include <iostream>
#include "custom_utlis.h"

using namespace std;


const int STRING_BUFFER_SIZE = 5;

class MyString
{
private:
	char* characters;

	int lengthWithBuffer;
	int length;

	friend ostream& operator<<(ostream& ostr, const MyString& str);
	friend ostream& operator<<(ostream& ostr, MyString& str);

	static int GetLengthWithBuffer(int lengthToUpdate);

public:
	MyString();

	MyString(const char* charactersArg, int length);

	MyString(MyString& other);

	~MyString();


	MyString& operator=(MyString& other);

	MyString& operator+=(char character);

	char& operator[](int index);

	bool IsEmpty() const;

	bool IsEqual(MyString& other) const;
	bool IsEqual(const MyString& other) const;
	bool IsEqual(const char* otherCharacters, int otherLength) const;

	void Reset();

	void TrimEdgeWhiteSpaces();

	int GetLength() const;


	bool isNumerical() const;

	int ToInteger() const;
};

