// 0714
#include "Basic.h"
#include "sString.h"
#include "CSVLIB.h"
#include "SaveLoad.h"
#include"sparagraphList.h"

int main(void)
{
	sParagraphList paragraphList;
	ParsingCSV("story.csv", &paragraphList);

	int select = 0;
	printf("데이터를 로드할까요? [Y : 로드 / N : 처음부터]\n\n");
	char isload = _getch();	// load 유무 물어봄
	if (isload == 'y' || isload == 'Y')
		select = Load();
	else if (isload == 'n' || isload == 'N')
		select = 0;

	while (true)	// 게임의 프레임! -> 반복 시켜주는게 mainupdate
	{
		int nextSelect = paragraphList.Process(select);

		if (nextSelect < 0)	// 음수면 종료
			break;
		else
			select = nextSelect;
	}

	Save(select);
	paragraphList.Destory();

	puts("프로그램을 종료합니다.");
	return 0;
}