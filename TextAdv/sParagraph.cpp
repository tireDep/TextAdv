#include "Basic.h"
#include "sString.h"
#include "sParagraph.h"

sParagraph::sParagraph()
{
	_current = NULL;
}

sParagraph::~sParagraph()
{
	_current = _start;
	
	while (NULL != _current->GetNext())
	{
		sString* nextString = _current->GetNext();
		delete _current;
		_current = nextString;
	}
	
}

void sParagraph::AddString(sString* string) // 도움 함수(문단에 문장 삽입)	=> 스크립트를 읽은 후 문단에 문장이 몇 개 있는지 계산하는 함수
{
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다름
	if (NULL == _current)	// 들어 왔을 때 아무것도 없으면 첫 문장
	{
		_current = string;	// 현재 문장 세팅
		string->InitNode(NULL, NULL);
		_start = string;	// 첫 문장 저장
	}
	else
	{
		_current->SetNext(string);	// 현재 문장의 다음번에 저장함
		string->InitNode(_current, NULL);
		_current = string;	// 마지막 최종 문장 저장
	}
}

int sParagraph::Process()
{
	int nextSelect = 0;
	_current = _start; // 현재 출력할 문장을 시작 문장으로 세팅 => 첫 문장부터 출력
	while (NULL != _current)	// 문장의 갯수는 모르는 상태에서 반복을 진행함
	{
		Sleep(500);
		
		nextSelect = _current->Process();
		_current = _current->GetNext();

		/* 키를 누르면 한 문장씩 출력 시켜주도록 개선
		char ch = _getch();
		if(32==ch)
			_current = _current->GetNext();
		*/
	}
	return nextSelect;
}