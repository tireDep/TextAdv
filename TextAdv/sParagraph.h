#pragma once
class sString;

// sParagraph 캡슐화
class sParagraph	// sString 모음 자료형 => 문단
{
public:
	sParagraph();
	~sParagraph();

private:
	sString * _start;	// 시작문장
	sString* _current;	// 현재 출력해야 할 문장

public:
	void AddString(sString* string);	// 문단에 문장 삽입
	int Process();	// 문단 출력, 문장 타입에 따라서 문장 출력 후 행동이 결정됨
};