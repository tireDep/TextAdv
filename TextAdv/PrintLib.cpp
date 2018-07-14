#include "Basic.h"
#include "sString.h"
#include "PrintLib.h"

void AddStringToParagraph(sParagraph* paragraph, sString* string) // 도움 함수(문단에 문장 삽입)	=> 스크립트를 읽은 후 문단에 문장이 몇 개 있는지 계산하는 함수
{
	// 첫 문장일 때, 첫 문장이 아닐 때 세팅이 다름
	if (NULL==paragraph->current)	// 들어 왔을 때 아무것도 없으면 첫 문장
	{
		// 첫 문장(paragraph -> current : 첫 문장)
		paragraph->current = string;	// 현재 문장 세팅
		// string->_prev = NULL;	// 이전 문장 없음
		// string->_next = NULL;	// 다음 문장 없음
		string->InitNode(NULL, NULL);
		paragraph->start = string;	// 첫 문장 저장
	}
	else
	{
		// 첫 문장 아님
		// current 에는 "첫 문장"이라는 내용 세팅
		// string에는 "두 번째 문장"이라는 내용 세팅
		// paragraph->current->_next = string;	// 현재 문장의 다음번에 저장함
		paragraph->current->SetNext(string);	// 현재 문장의 다음번에 저장함
		// string->_prev = paragraph->current;	// 이전 문장 있음
		// string->_next = NULL;	// 다음 문장 없음
		string->InitNode(paragraph->current, NULL);
		paragraph->current = string;	// 마지막 최종 문장 저장
	}
}

void AddParagraphToList(sParagraphList* paragraphList,  sParagraph* paragraph)	// 오버로딩
{
	paragraphList->list[paragraphList->count] = *paragraph;	// 전체 문단에 문단 저장
	paragraphList->count++;
}

int PrintParagraph(sParagraph* paragraph)
{
	/*
	for (int i = 0; i < paragraph->count; i++)	// 문단 출력
	{
		Sleep(500);
		switch (paragraph->stringList[i].type)	// enum 사용!
		{
		case TEXT:	// case 0: 일반 출력
			PrintText(paragraph->stringList[i].text);	// 문장 출력
			break;
		case BRANCH:	// case 1: 분기
			PrintText(paragraph->stringList[i].text);
			/* 요구사항
			- 유저가 선택하기 전까지는 머물러 있어야 함
			- 유저가 Y/N을 선택하면 진행
			- 유저의 선택에 따라 다음 진행할 내용의 인덱스가 결정
			while (true)
			{
				char ch = toupper(_getch());
				if ('Y' == ch)
					return paragraph->stringList[i].selectY;
				else if ('N' == ch)
					return paragraph->stringList[i].selectN;
				else if (27 == ch || ch == 'Q')	// 27 == ESC
				{
					// puts("\n종료 선택!");
					return -1;
				}
			}
			break;
		case QUIT:	// case 2 : 종료
			PrintText(paragraph->stringList[i].text);
			return -100;
		default:
			puts("에러!");
			break;
		}
	}*/
	paragraph->current = paragraph->start; // 현재 출력할 문장을 시작 문장으로 세팅 => 첫 문장부터 출력
	while (NULL != paragraph->current)	// 문장의 갯수는 모르는 상태에서 반복을 진행함
	{
		Sleep(500);
		// stringList[i]. ==> current ->	// 기존 : i번째 있는거 출력 ==> 현재 : 현재 문장 출력
		switch (paragraph->current->GetType())
		{
		case TEXT:	// case 0: 일반 출력
			paragraph->current->Print();	// 문장 출력
			break;
		case BRANCH:	// case 1: 분기
			paragraph->current->Print();
			/* 요구사항
			- 유저가 선택하기 전까지는 머물러 있어야 함
			- 유저가 Y/N을 선택하면 진행
			- 유저의 선택에 따라 다음 진행할 내용의 인덱스가 결정*/
			while (true)
			{
				char ch = toupper(_getch());
				if ('Y' == ch)
					return paragraph->current->GetSelectY();
				else if ('N' == ch)
					return paragraph->current->GetSelectN();
				else if (27 == ch || ch == 'Q')	// 27 == ESC
					return -1;
			}
			break;
		case QUIT:	// case 2 : 종료
			paragraph->current->Print();
			return -100;
		default:
			puts("에러!");
			break;
		}
		// paragraph->current = paragraph->current->_next;
		paragraph->current = paragraph->current->GetNext();
	}
	return 0;	// 애매한 상황인 경우
}