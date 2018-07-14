#include"Basic.h"
#include"sString.h"

sString::sString()	// ������
{
	_prev = NULL;	// ��������
	_next = NULL;	// ��������
}

sString::sString(const char* text, eStringType type, int selectY, int selectN)	// ������2 : init ���ұ��� ��
{
	_prev = NULL;	// ��������
	_next = NULL;	// ��������
	Init(text, type, selectY, selectN);
}

sString::~sString() // �Ҹ���(������)
{

}

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
