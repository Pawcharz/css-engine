#pragma once
#include <iostream>

#include "List.h"
#include "MyString.h"
#include "Reader.h"

//using namespace std;

int main()
{
	/*MyString str1("abcd", 4);
	MyString str2("efg", 3);
	MyString str3("hijkl", 5);
	List<MyString>* testList = new List<MyString>(1);

	testList->AddElement(str1);
	testList->AddElement(str2);
	testList->AddElement(str3);
	testList->AddElement(str1);
	testList->AddElement(str2);

	testList->RemoveLastNode();
	testList->RemoveLastNode();

	delete testList;*/

	Reader* reader = new Reader();


	reader->ReadAll();


	delete reader;
}