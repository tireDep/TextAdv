#include "Basic.h"
#include "sStringBranch.h"

sStringBranch::sStringBranch()
{
}

sStringBranch::~sStringBranch()
{
}

int sStringBranch::Process()
{	
	Print();
	int select = -1;

	while (true)
	{
		char ch = toupper(_getch());
		if ('Y' == ch)
		{
			select = GetSelectY();
			break;
		}
		else if ('N' == ch)
		{
			select = GetSelectN();
			break;
		}
		else if (27 == ch || ch == 'Q')	// 27 == ESC
		{
			select = -1;
			break;
		}
	}

	return select;
}