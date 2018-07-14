#include "Basic.h"
#include "sString.h"
#include "CSVLib.h"


int CalcParagraphCount(FILE *fp)
{
	char buffer[1024];	// �ӽ� ���� ����
	char* record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����
	int count = 0;
	int prevNo = -1;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����
		if (record == NULL)
			break;

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);
		if (pNo != prevNo)	//	������ �ٲ�
		{
			prevNo = pNo;
			count++;
		}
	}
	fseek(fp, 0, SEEK_SET);
	return count;
}

void ParsingCSV(const char* fileName, sParagraphList* paragraphList)
{
	// ��ũ��Ʈ ��� 
	// 1) ������ �� - ���Ͽ� �ִ� ������ ���� �غ� ��
	FILE* fp = fopen(fileName, "r"); // ����ü / ��� : r - read, w - write
	if (fp == NULL)
	{
		puts("Error : File isn't exist");
		return;
	}

	// 2) �Ľ� - ���Ͽ� �ִ� ������ ����(������ �������� ����)
	char buffer[1024];	// �ӽ� ���� ����
	char* record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����

														// paragraphList->count = CalcParagraphCount(fp);	// ������ ���ڸ��� ���� ���� ���
														// paragraphList->_list = new sParagraph[paragraphList->count];
														// ��� ����� �߰��� �� �ΰ�?
	int count = CalcParagraphCount(fp);
	paragraphList->Create(count);

	// 3) ��ū�� ������ ���� �����͸� ������
	int prevNo = -1;
	int cnt = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����

		if (record == NULL)
			break;

		if (cnt == 0)	// ù�� ��� ����
		{
			cnt++;
			continue;
		}

		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);

		token = strtok(NULL, ",");// Ÿ��
		eStringType type = (eStringType)atoi(token);

		token = strtok(NULL, ",");// ����
		char* text = token;

		token = strtok(NULL, ",");// ������Y
		int selectY = atoi(token);

		token = strtok(NULL, ",");// ������N
		int selectN = atoi(token);

		if (pNo != prevNo)	//	������ �ٲ�
		{
			// paragraphList->list[pNo]._current = NULL; // �����ڿ��� �ذ��
			prevNo = pNo;
		}

		// sString newString;
		//InitString(&newString, text, type, selectY, selectN);	// ���ܿ� ��������
		//AddStringToParagraph(&paragraphList->list[pNo], &newString); // ��ü���ܿ� ���� ����

		// sString* newString = (sString*)malloc(sizeof(sString));
		// sString* newString = new sString();	// Ŭ������ new�� �����ؾ��� �����ڰ� ȣ��ǹǷ� malloc ����ϸ� �ȵ�!!
		// newString->Init(text, type, selectY, selectN);	// ���ܿ� ��������
		sString* newString = new sString(text, type, selectY, selectN);	// ���� �� ���� �� �ٷ� �����(������ ���)
																		// AddString(&paragraphList->list[pNo], newString);	// ��ü���ܿ� ���� ����
																		// paragraphList->_list[pNo].AddString(newString); // ������
		paragraphList->AddStringToList(pNo, newString);
	}

	// 4) ��� �Ϸ� �� ������ ���� - ������ �ٽ� ���� �� ���� ���·� ����
	fclose(fp);
}