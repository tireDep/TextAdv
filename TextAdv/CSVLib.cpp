#include "Basic.h"
#include "sString.h"
#include "PrintLib.h"
#include "CSVLib.h"


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

// 개수를 계산할 필요가 없음!
/*void CreateParagraphStringList(sParagraph* paragraph, FILE* fp)
{
	char buffer[1024];	// 임시 저장 버퍼
	char* record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성
	int count = 0;
	int prevNo = 0;	// -1이면 시작하자 마자, 0이면 한턴 후에 시작함
	while (1)
	{
		record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성
		if (record == NULL)
		{
			paragraph[prevNo].stringList = (sString*)malloc(count * sizeof(sString));
			break;
		}
		char* token = strtok(record, ",");	// 문단 번호
		int pNo = atoi(token);
		if (pNo != prevNo)	//	문단이 바뀜
		{
			paragraph[prevNo].stringList = (sString*)malloc(count * sizeof(sString));
			prevNo = pNo;
			count = 0;
		}
		count++;	// 문장개수
	}
	fseek(fp, 0, SEEK_SET);
}
*/

void ParsingCSV(const char* fileName, sParagraphList* paragraphList)
{
	// 스크립트 사용 
	// 1) 파일을 염 - 파일에 있는 내용을 읽을 준비를 함
	FILE* fp = fopen(fileName,"r"); // 구조체 / 모드 : r - read, w - write
	if (fp == NULL)
	{
		puts("Error : File isn't exist");
		return;
	}

	// 2) 파싱 - 파일에 있는 내용을 읽음(데이터 구성까지 포함)
	char buffer[1024];	// 임시 저장 버퍼
	char* record = fgets(buffer, sizeof(buffer), fp);	// 한 줄 생성
	// printf("%s\n", record);	// 첫 줄 읽음 -> 의미 x이므로 skip

	paragraphList->count = CalcParagraphCount(fp);	// 파일을 열자마자 문단 개수 계산
	paragraphList->list = (sParagraph*)malloc(paragraphList->count * sizeof(sParagraph));// 거기서 부터 시작하는데, 어디까지 해라(크기 계산)
	// (구조체 크기의 기준을 모름 => 크기를 어떤 정보로 사용할 것인지 알려주는 것) malloc (구조체 크기)

	// CreateParagraphStringList(paragraphList->list, fp);	// 주의! 개수를 잡은 이후에 사용해야 함! => 개수를 계산할 필요가 없기 때문에 삭제

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
		{
			// paragraphList->list[pNo].count = 0;
			paragraphList->list[pNo].current = NULL;
			prevNo = pNo;
		}

		// sString newString;
		//InitString(&newString, text, type, selectY, selectN);	// 문단에 문장저장
		//AddStringToParagraph(&paragraphList->list[pNo], &newString); // 전체문단에 문단 저장

		sString* newString = (sString*)malloc(sizeof(sString));
		newString->Init(text, type, selectY, selectN);	// 문단에 문장저장
		AddStringToParagraph(&paragraphList->list[pNo], newString); // 전체문단에 문단 저장
	}

	// 4) 사용 완료 후 파일을 닫음 - 파일을 다시 읽을 수 없는 상태로 만듦
	fclose(fp);
}