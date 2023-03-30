#pragma once
#include <iostream>

using namespace std;

const char SPACE_CHARACTER = ' ';
const char NEW_LINE_CHARACTER = '\n';
const int STRING_BUFFER_SIZE = 5;

class MyString
{
private:
	char* characters;

	int lengthWithBuffer;
	int length;

	//friend ostream& operator<<(ostream& ostr, MyString& str);

	int GetLengthWithBuffer(int lengthToUpdate);

public:
	MyString();

	MyString(const char* CharactersArg, int length);

	MyString(MyString& other);

	~MyString();


	MyString& operator=(MyString& other);

	//MyString& operator=(char character);

	void operator+=(char character);

	char& operator[](int index);

	bool IsEmpty();

	bool IsEqual(MyString& other);
	bool IsEqual(const MyString& other);

	//int& GetLength();


	void Reset();

	void TrimEdgeWhiteSpaces();


};

