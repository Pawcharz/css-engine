#pragma once
#include <iostream>

using namespace std;

const char SPACE_CHARACTER = ' ';
const char NEW_LINE_CHARACTER = '\n';

class MyString
{
private:
	char* characters;
	int length;

	friend ostream& operator<<(ostream& ostr, MyString& str);

public:
	MyString();

	MyString(const char* characters, int length);

	MyString(MyString& other);

	~MyString();


	//MyString& operator=(MyString& newValue);

	//MyString& operator=(char character);

	void operator+=(char character);

	char& operator[](int index);

	bool IsEmpty();

	bool IsEqual(MyString& right);
	bool IsEqual(const MyString& right);

	//int& GetLength();


	void Reset();

	void TrimEdgeWhiteSpaces();


};

