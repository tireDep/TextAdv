#include"Basic.h"
#include"sString.h"

void sString::Init(const char* text, eStringType type)	// ���� x �Լ�, const : ���(�б�����)
{
	_type = type;
	strcpy(_text, text);	// ���� �Լ� : strcpy ��� �ڸ� ����
}

void sString::Init(const char* text, eStringType type, int selectY, int selectN)	// �����ε�(�б⹮ �̿�)
{
	Init(text, type);
	_selectY = selectY;
	_selectN = selectN;
}

void sString::Print()	// �־��� å�� �ִ� �л��� �̸� ���
{
	printf(_text);
	puts("");
}
