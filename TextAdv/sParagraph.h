#pragma once
class sString;

// sParagraph ĸ��ȭ
class sParagraph	// sString ���� �ڷ��� => ����
{
public:
	sParagraph();
	~sParagraph();

private:
	sString * _start;	// ���۹���
	sString* _current;	// ���� ����ؾ� �� ����

public:
	void AddString(sString* string);	// ���ܿ� ���� ����
	int Process();	// ���� ���, ���� Ÿ�Կ� ���� ���� ��� �� �ൿ�� ������
};