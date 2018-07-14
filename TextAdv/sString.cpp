#include"Basic.h"
#include"sString.h"

void sString::Init(const char* text, eStringType type)	// 생산 x 함수, const : 상수(읽기전용)
{
	_type = type;
	strcpy(_text, text);	// 도움 함수 : strcpy 대신 자리 배정
}

void sString::Init(const char* text, eStringType type, int selectY, int selectN)	// 오버로딩(분기문 이용)
{
	Init(text, type);
	_selectY = selectY;
	_selectN = selectN;
}

void sString::Print()	// 주어진 책상에 있는 학생의 이름 출력
{
	printf(_text);
	puts("");
}
