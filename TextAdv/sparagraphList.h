#pragma once
#include "Basic.h"
#include "sString.h"
#include "sParagraph.h"

class sString;
class sParagraphList	// sParagraph 모음 자료형 => 전체 문단
{
private:
	int _count;
	sParagraph *_list;	// 여기서 부터 사용할거임 표시, 개수는 아직 모름!

public:
	void Create(int count);
	void AddStringToList(int pNo, sString* newString);
	int Process(int select);
	void Destory();

};