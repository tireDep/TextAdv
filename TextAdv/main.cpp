// 0616 수업
#include "Basic.h"
#include "sString.h"
#include "PrintLib.h"
#include "CSVLIB.h"
#include "SaveLoad.h"

int main(void)
{
	sParagraphList paragraphList;
	ParsingCSV("story.csv", &paragraphList);

	int select = 0; // 처음 출력할 문단 표시 -> 저장! // 경우에 따라서 nextselect도 저장할 수 있음

	// 메인 메뉴 추가 -> 게임 시작 화면/게임시작/이어하기/종료 요런식
	// puts("게임게임\n게임 시작\n이어하기\n종료\n");

	// 요구사항(기획) : 로드를 하시겠습니까? Y or N (Y : 로드 / N : 처음부터)
	printf("데이터를 로드할까요? [Y : 로드 / N : 처음부터]\n\n");
	char isload = _getch();	// load 유무 물어봄
	if (isload == 'y' || isload == 'Y')
		select = Load();
	else if (isload == 'n' || isload == 'N')
		select = 0;

	while (true)	// 게임의 프레임! -> 반복 시켜주는게 mainupdate
	{
		int nextSelect = 0;	// 다음에 출력할 문단 표시
		
		if(select<paragraphList.count)
		{
			printf("\n");
			nextSelect = PrintParagraph(&paragraphList.list[select]);
		}
		else
			break; // 잘못 입력시 종료

		if (nextSelect < 0)	// 음수면 종료
			break;
		else
		{
			select = nextSelect;
		}
	}

	Save(select);	// 저장

	// malloc 사용한 것은 free 메모리 해제필요함!
	for (int i = 0; i < paragraphList.count; i++)
	{
		// free(paragraphList.list[i].stringList);
		paragraphList.list[i].current = paragraphList.list[i].start;
		while (NULL != paragraphList.list[i].current->GetNext())
		{
			sString* nextString = paragraphList.list[i].current->GetNext();	// 다음문장 기억
			free(paragraphList.list[i].current);	// 현재 문장 삭제
			paragraphList.list[i].current = nextString;	// 현재 문장을 기억해 놓은 다음 문장으로 세팅
			// 다음 문장을 저장해 놓지 않고 현재 문장을 삭제하면 다음 문장을 알 수가 없음!(Linked List)
		}
	}
	free(paragraphList.list);

	puts("프로그램을 종료합니다.");
	return 0;
}