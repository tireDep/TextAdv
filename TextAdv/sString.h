#pragma once

enum eStringType	// ������ ���
{
	TEXT,	// 0
	BRANCH,	// 1
	QUIT	// 2
};

class sString	// �ؽ�Ʈ�� ����ϱ� ���� �ڷ���
{
public:
	sString();	// ������
	sString(const char* text, eStringType type, int selectY, int selectN);	// init���� ���� �ϴ� ������
	~sString(); // �Ҹ���

private: // ������ ����x
	eStringType _type;	// int�� ���� �Ӽ� => type�� ��������, eStringType�� ����ϱ� ������!
	char _text[256];	// ���ڿ� ����
	int _selectY;	// y ���� �� �бⰪ
	int _selectN;	// n ���� �� �бⰪ
	sString *_prev;	// ��������
	sString *_next;	// ��������

private:	// �����ڿ��� ����ϱ� ������ �ܺο��� ���x
	void Init(const char* text, eStringType type);	// ��������� ���� ���� -> �߻��� (���� ����, ����, ���� Ÿ��)
	void Init(const char* text, eStringType type, int selectY, int selectN);	// InitString �����ε�(�б⹮)

public:	// �����͸� �ٲٱ� ���ؼ� �Լ� ����
	void Print();	// ���� ���

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