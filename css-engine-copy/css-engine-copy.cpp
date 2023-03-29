#pragma once
#include <iostream>;

#include "List.h";
#include "MyString.h";
#include "Reader.h"

//using namespace std;


int main()
{
	/*MyString str1("abcd", 4);
	MyString str2("efg", 3);
	MyString str3("hijkl", 5);
	List<MyString>* testList = new List<MyString>();

	testList->AddNode(str1);
	testList->AddNode(str2);
	testList->AddNode(str3);

	testList->Remove_Last();

	delete testList;*/

	Reader* reader = new Reader();


	reader->ReadAll();


	//delete reader;
}