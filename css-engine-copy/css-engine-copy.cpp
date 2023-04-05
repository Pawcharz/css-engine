#pragma once

#include "List.h"
#include "MyString.h"
#include "Reader.h"

int main()
{
	Reader* reader = new Reader();

	reader->ReadAll();

	delete reader;
}