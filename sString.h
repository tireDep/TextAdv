#pragma once

enum eStringType	// ������ ���
{
	TEXT,	// 0
	BRANCH,	// 1
	QUIT	// 2
};

class sString	// �ؽ�Ʈ�� ����ϱ� ���� �ڷ���
{
// public:	// �ӽ� ���! -> �۾����̱� ������ ��ü ��� => ����ü�� ���� ��Ȳ��
private: // ������ ����x
	eStringType _type;	// int�� ���� �Ӽ� => type�� ��������, eStringType�� ����ϱ� ������!
	char _text[256];	// ���ڿ� ����
	int _selectY;	// y ���� �� �бⰪ
	int _selectN;	// n ���� �� �бⰪ
	sString *_prev;	// ��������
	sString *_next;	// ��������

// �̸� ĸ��ȭ
public:	// �����͸� �ٲٱ� ���ؼ� �Լ� ����
	void Init(const char* text, eStringType type);	// ��������� ���� ���� -> �߻��� (���� ����, ����, ���� Ÿ��)
	void Init(const char* text, eStringType type, int selectY, int selectN);	// InitString �����ε�(�б⹮)
	void Print();	// ���� ���

	// getter �Լ� <-> setter �Լ�
	eStringType GetType()	// ������ ���⸸ ������
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
		return _next;	// ��������
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