#include "Basic.h"
#include "sString.h"
#include "PrintLib.h"

void AddStringToParagraph(sParagraph* paragraph, sString* string) // ���� �Լ�(���ܿ� ���� ����)	=> ��ũ��Ʈ�� ���� �� ���ܿ� ������ �� �� �ִ��� ����ϴ� �Լ�
{
	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ�
	if (NULL==paragraph->current)	// ��� ���� �� �ƹ��͵� ������ ù ����
	{
		// ù ����(paragraph -> current : ù ����)
		paragraph->current = string;	// ���� ���� ����
		// string->_prev = NULL;	// ���� ���� ����
		// string->_next = NULL;	// ���� ���� ����
		string->InitNode(NULL, NULL);
		paragraph->start = string;	// ù ���� ����
	}
	else
	{
		// ù ���� �ƴ�
		// current ���� "ù ����"�̶�� ���� ����
		// string���� "�� ��° ����"�̶�� ���� ����
		// paragraph->current->_next = string;	// ���� ������ �������� ������
		paragraph->current->SetNext(string);	// ���� ������ �������� ������
		// string->_prev = paragraph->current;	// ���� ���� ����
		// string->_next = NULL;	// ���� ���� ����
		string->InitNode(paragraph->current, NULL);
		paragraph->current = string;	// ������ ���� ���� ����
	}
}

void AddParagraphToList(sParagraphList* paragraphList,  sParagraph* paragraph)	// �����ε�
{
	paragraphList->list[paragraphList->count] = *paragraph;	// ��ü ���ܿ� ���� ����
	paragraphList->count++;
}

int PrintParagraph(sParagraph* paragraph)
{
	/*
	for (int i = 0; i < paragraph->count; i++)	// ���� ���
	{
		Sleep(500);
		switch (paragraph->stringList[i].type)	// enum ���!
		{
		case TEXT:	// case 0: �Ϲ� ���
			PrintText(paragraph->stringList[i].text);	// ���� ���
			break;
		case BRANCH:	// case 1: �б�
			PrintText(paragraph->stringList[i].text);
			/* �䱸����
			- ������ �����ϱ� �������� �ӹ��� �־�� ��
			- ������ Y/N�� �����ϸ� ����
			- ������ ���ÿ� ���� ���� ������ ������ �ε����� ����
			while (true)
			{
				char ch = toupper(_getch());
				if ('Y' == ch)
					return paragraph->stringList[i].selectY;
				else if ('N' == ch)
					return paragraph->stringList[i].selectN;
				else if (27 == ch || ch == 'Q')	// 27 == ESC
				{
					// puts("\n���� ����!");
					return -1;
				}
			}
			break;
		case QUIT:	// case 2 : ����
			PrintText(paragraph->stringList[i].text);
			return -100;
		default:
			puts("����!");
			break;
		}
	}*/
	paragraph->current = paragraph->start; // ���� ����� ������ ���� �������� ���� => ù ������� ���
	while (NULL != paragraph->current)	// ������ ������ �𸣴� ���¿��� �ݺ��� ������
	{
		Sleep(500);
		// stringList[i]. ==> current ->	// ���� : i��° �ִ°� ��� ==> ���� : ���� ���� ���
		switch (paragraph->current->GetType())
		{
		case TEXT:	// case 0: �Ϲ� ���
			paragraph->current->Print();	// ���� ���
			break;
		case BRANCH:	// case 1: �б�
			paragraph->current->Print();
			/* �䱸����
			- ������ �����ϱ� �������� �ӹ��� �־�� ��
			- ������ Y/N�� �����ϸ� ����
			- ������ ���ÿ� ���� ���� ������ ������ �ε����� ����*/
			while (true)
			{
				char ch = toupper(_getch());
				if ('Y' == ch)
					return paragraph->current->GetSelectY();
				else if ('N' == ch)
					return paragraph->current->GetSelectN();
				else if (27 == ch || ch == 'Q')	// 27 == ESC
					return -1;
			}
			break;
		case QUIT:	// case 2 : ����
			paragraph->current->Print();
			return -100;
		default:
			puts("����!");
			break;
		}
		// paragraph->current = paragraph->current->_next;
		paragraph->current = paragraph->current->GetNext();
	}
	return 0;	// �ָ��� ��Ȳ�� ���
}