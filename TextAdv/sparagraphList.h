#pragma once
#include "Basic.h"
#include "sString.h"
#include "sParagraph.h"

class sString;
class sParagraphList	// sParagraph ���� �ڷ��� => ��ü ����
{
private:
	int _count;
	sParagraph *_list;	// ���⼭ ���� ����Ұ��� ǥ��, ������ ���� ��!

public:
	void Create(int count);
	void AddStringToList(int pNo, sString* newString);
	int Process(int select);
	void Destory();

};