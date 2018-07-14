#include"Basic.h"
#include"sparagraphList.h"

void sParagraphList::Create(int count)
{
	_count = count;
	_list = new sParagraph[_count];
}

void sParagraphList::AddStringToList(int pNo, sString* newString)
{
	_list[pNo].AddString(newString);
}

int sParagraphList::Process(int select)
{
	if (select<_count)
	{
		printf("\n");
		return _list[select].Process();
	}
	return -1;
}

void sParagraphList::Destory()
{
	delete[] _list;	// 배열 삭제
}