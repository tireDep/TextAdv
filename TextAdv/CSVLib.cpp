#include "Basic.h"
#include "sString.h"
#include "PrintLib.h"
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

// ������ ����� �ʿ䰡 ����!
/*void CreateParagraphStringList(sParagraph* paragraph, FILE* fp)
{
	char buffer[1024];	// �ӽ� ���� ����
	char* record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����
	int count = 0;
	int prevNo = 0;	// -1�̸� �������� ����, 0�̸� ���� �Ŀ� ������
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����
		if (record == NULL)
		{
			paragraph[prevNo].stringList = (sString*)malloc(count * sizeof(sString));
			break;
		}
		char* token = strtok(record, ",");	// ���� ��ȣ
		int pNo = atoi(token);
		if (pNo != prevNo)	//	������ �ٲ�
		{
			paragraph[prevNo].stringList = (sString*)malloc(count * sizeof(sString));
			prevNo = pNo;
			count = 0;
		}
		count++;	// ���尳��
	}
	fseek(fp, 0, SEEK_SET);
}
*/

void ParsingCSV(const char* fileName, sParagraphList* paragraphList)
{
	// ��ũ��Ʈ ��� 
	// 1) ������ �� - ���Ͽ� �ִ� ������ ���� �غ� ��
	FILE* fp = fopen(fileName,"r"); // ����ü / ��� : r - read, w - write
	if (fp == NULL)
	{
		puts("Error : File isn't exist");
		return;
	}

	// 2) �Ľ� - ���Ͽ� �ִ� ������ ����(������ �������� ����)
	char buffer[1024];	// �ӽ� ���� ����
	char* record = fgets(buffer, sizeof(buffer), fp);	// �� �� ����
	// printf("%s\n", record);	// ù �� ���� -> �ǹ� x�̹Ƿ� skip

	paragraphList->count = CalcParagraphCount(fp);	// ������ ���ڸ��� ���� ���� ���
	paragraphList->list = (sParagraph*)malloc(paragraphList->count * sizeof(sParagraph));// �ű⼭ ���� �����ϴµ�, ������ �ض�(ũ�� ���)
	// (����ü ũ���� ������ �� => ũ�⸦ � ������ ����� ������ �˷��ִ� ��) malloc (����ü ũ��)

	// CreateParagraphStringList(paragraphList->list, fp);	// ����! ������ ���� ���Ŀ� ����ؾ� ��! => ������ ����� �ʿ䰡 ���� ������ ����

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
			// paragraphList->list[pNo].count = 0;
			paragraphList->list[pNo].current = NULL;
			prevNo = pNo;
		}

		// sString newString;
		//InitString(&newString, text, type, selectY, selectN);	// ���ܿ� ��������
		//AddStringToParagraph(&paragraphList->list[pNo], &newString); // ��ü���ܿ� ���� ����

		sString* newString = (sString*)malloc(sizeof(sString));
		newString->Init(text, type, selectY, selectN);	// ���ܿ� ��������
		AddStringToParagraph(&paragraphList->list[pNo], newString); // ��ü���ܿ� ���� ����
	}

	// 4) ��� �Ϸ� �� ������ ���� - ������ �ٽ� ���� �� ���� ���·� ����
	fclose(fp);
}