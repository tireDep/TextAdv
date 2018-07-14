#pragma once

enum eStringType	// 열거형 상수
{
	TEXT,	// 0
	BRANCH,	// 1
	QUIT	// 2
};

class sString	// 텍스트를 출력하기 위한 자료형
{
public:
	sString();	// 생성자
	sString(const char* text, eStringType type, int selectY, int selectN);	// init역할 까지 하는 생성자
	~sString(); // 소멸자

private: // 데이터 접근x
	eStringType _type;	// int형 문장 속성 => type은 정수지만, eStringType을 사용하기 때문에!
	char _text[256];	// 문자열 저장
	int _selectY;	// y 선택 시 분기값
	int _selectN;	// n 선택 시 분기값
	sString *_prev;	// 이전문장
	sString *_next;	// 다음문장

private:	// 생성자에서 사용하기 때문에 외부에서 사용x
	void Init(const char* text, eStringType type);	// 저장공간에 문장 삽입 -> 추상적 (저장 공간, 문장, 문장 타입)
	void Init(const char* text, eStringType type, int selectY, int selectN);	// InitString 오버로딩(분기문)

public:	// 데이터를 바꾸기 위해서 함수 실행
	void Print();	// 문장 출력

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