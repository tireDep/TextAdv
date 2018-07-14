#include "Basic.h"
#include "sString.h"
#include "CSVLib.h"

#include "sStringText.h"
#include "sStringBranch.h"
#include "sStringQuit.h"

int CalcParagraphCount(FILE *fp)
{
	char buffer[1024];	// 임시 저장 버퍼
	char* record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성
	int count = 0;
	int prevNo = -1;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성
		if (record == NULL)
			break;

		char* token = strtok(record, ",");	// 문단 번호
		int pNo = atoi(token);
		if (pNo != prevNo)	//	문단이 바뀜
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
	// 스크립트 사용 
	// 1) 파일을 염 - 파일에 있는 내용을 읽을 준비를 함
	FILE* fp = fopen(fileName, "r"); // 구조체 / 모드 : r - read, w - write
	if (fp == NULL)
	{
		puts("Error : File isn't exist");
		return;
	}

	// 2) 파싱 - 파일에 있는 내용을 읽음(데이터 구성까지 포함)
	char buffer[1024];	// 임시 저장 버퍼
	char* record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성
	int count = CalcParagraphCount(fp);
	paragraphList->Create(count);

	// 3) 토큰을 가지고 게임 데이터를 구성함
	int prevNo = -1;
	int cnt = 0;
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성

		if (record == NULL)
			break;

		if (cnt == 0)	// 첫줄 출력 생략
		{
			cnt++;
			continue;
		}

		char* token = strtok(record, ",");	// 문단 번호
		int pNo = atoi(token);

		token = strtok(NULL, ",");// 타입
		eStringType type = (eStringType)atoi(token);

		token = strtok(NULL, ",");// 내용
		char* text = token;

		token = strtok(NULL, ",");// 선택지Y
		int selectY = atoi(token);

		token = strtok(NULL, ",");// 선택지N
		int selectN = atoi(token);

		if (pNo != prevNo)	//	문단이 바뀜
			prevNo = pNo;

		sString* newString = NULL;
		switch (type)
		{
		case eStringType::TEXT:
			newString = new sStringText();
			break;
		case eStringType::BRANCH:
			newString = new sStringBranch();
			break;
		case eStringType::QUIT:
			newString = new sStringQuit();
			break;
		default:
			puts("typeError!!");
			break;
		}
		newString->Init(text, type, selectY, selectN);
		paragraphList->AddStringToList(pNo, newString);
	}
	// 4) 사용 완료 후 파일을 닫음 - 파일을 다시 읽을 수 없는 상태로 만듦
	fclose(fp);
}