// print���� �Լ��� ����
#pragma once
#ifdef PRINT_LIB_H
#define PRINT_LIB_H
#endif // PRINT_LIB_H

// #include"sString.h"	=> ���� �߻��� Ȯ���� ����
// ���� ����
class sString;

typedef struct sParagraph	// sString ���� �ڷ��� => ����
{
	sString* start;	// ���۹���
	sString* current;	// ���� ����ؾ� �� ����
}sParagraph;

typedef struct sParagraphList	// sParagraph ���� �ڷ��� => ��ü ����
{
	int count;
	sParagraph *list;	// ���⼭ ���� ����Ұ��� ǥ��, ������ ���� ��!
}sParagraphList;

void AddStringToParagraph(sParagraph* paragraph, sString* string);	// ���ܿ� ���� ����
void AddParagraphToList(sParagraphList* paragraphList, sParagraph* paragraph); // ��ü ���ܿ� ���� ���� -> overloading
int PrintParagraph(sParagraph* paragraph);	// ���� ���, ���� Ÿ�Կ� ���� ���� ��� �� �ൿ�� ������