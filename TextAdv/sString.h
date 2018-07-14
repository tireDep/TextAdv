#pragma once

enum eStringType	// 열거형 상수
{
	TEXT,	// 0
	BRANCH,	// 1
	QUIT	// 2
};

class sString	// 텍스트를 출력하기 위한 자료형
{
// public:	// 임시 허용! -> 작업중이기 때문에 전체 허용 => 구조체랑 같은 상황임
private: // 데이터 접근x
	eStringType _type;	// int형 문장 속성 => type은 정수지만, eStringType을 사용하기 때문에!
	char _text[256];	// 문자열 저장
	int _selectY;	// y 선택 시 분기값
	int _selectN;	// n 선택 시 분기값
	sString *_prev;	// 이전문장
	sString *_next;	// 다음문장

// 이름 캡슐화
public:	// 데이터를 바꾸기 위해서 함수 실행
	void Init(const char* text, eStringType type);	// 저장공간에 문장 삽입 -> 추상적 (저장 공간, 문장, 문장 타입)
	void Init(const char* text, eStringType type, int selectY, int selectN);	// InitString 오버로딩(분기문)
	void Print();	// 문장 출력

	// getter 함수 <-> setter 함수
	eStringType GetType()	// 가져다 쓰기만 가능함
	{
		return _type;
	}
	int GetSelectY()
	{
		return _selectY;
	}
	int GetSelectN()
	{
		return _selectN;
	}
	sString *GetNext() 
	{
		return _next;	// 다음문장
	}
	void InitNode(sString *prev, sString *next)
	{
		_prev = prev;
		_next = next;
	}
	void SetNext(sString *next)
	{
		_next = next;
	}
};