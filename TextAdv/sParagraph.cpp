#include "Basic.h"
#include "sString.h"
#include "sParagraph.h"

sParagraph::sParagraph()
{
	_current = NULL;
}

sParagraph::~sParagraph()
{
	_current = _start;
	
	while (NULL != _current->GetNext())
	{
		sString* nextString = _current->GetNext();
		delete _current;
		_current = nextString;
	}
	
}

void sParagraph::AddString(sString* string) // ���� �Լ�(���ܿ� ���� ����)	=> ��ũ��Ʈ�� ���� �� ���ܿ� ������ �� �� �ִ��� ����ϴ� �Լ�
{
	// ù ������ ��, ù ������ �ƴ� �� ������ �ٸ�
	if (NULL == _current)	// ��� ���� �� �ƹ��͵� ������ ù ����
	{
		_current = string;	// ���� ���� ����
		string->InitNode(NULL, NULL);
		_start = string;	// ù ���� ����
	}
	else
	{
		_current->SetNext(string);	// ���� ������ �������� ������
		string->InitNode(_current, NULL);
		_current = string;	// ������ ���� ���� ����
	}
}

int sParagraph::Process()
{
	int nextSelect = 0;
	_current = _start; // ���� ����� ������ ���� �������� ���� => ù ������� ���
	while (NULL != _current)	// ������ ������ �𸣴� ���¿��� �ݺ��� ������
	{
		Sleep(500);
		
		nextSelect = _current->Process();
		_current = _current->GetNext();

		/* Ű�� ������ �� ���徿 ��� �����ֵ��� ����
		char ch = _getch();
		if(32==ch)
			_current = _current->GetNext();
		*/
	}
	return nextSelect;
}