// print관련 함수들 모음
#pragma once
#ifdef PRINT_LIB_H
#define PRINT_LIB_H
#endif // PRINT_LIB_H

// #include"sString.h"	=> 에러 발생할 확률이 높음
// 전방 선언
class sString;

typedef struct sParagraph	// sString 모음 자료형 => 문단
{
	sString* start;	// 시작문장
	sString* current;	// 현재 출력해야 할 문장
}sParagraph;

typedef struct sParagraphList	// sParagraph 모음 자료형 => 전체 문단
{
	int count;
	sParagraph *list;	// 여기서 부터 사용할거임 표시, 개수는 아직 모름!
}sParagraphList;

void AddStringToParagraph(sParagraph* paragraph, sString* string);	// 문단에 문장 삽입
void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph); // 전체 문단에 문장 삽입 -> overloading
int PrintParagraph(sParagraph* paragraph);	// 문단 출력, 문장 타입에 따라서 문장 출력 후 행동이 결정됨