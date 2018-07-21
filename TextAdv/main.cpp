// 0721
#include "Basic.h"
#include "sString.h"
#include "CSVLIB.h"
#include "SaveLoad.h"
#include"sparagraphList.h"

int main(void)
{
	sParagraphList paragraphList;
	ParsingCSV("story.csv", &paragraphList);

	puts("- MyGame -\n\n이어하기(Y)\n처음부터(N)\n게임종료(ESC)\n");
	int select = 0;
	char isload = _getch();
	if (isload == 'y' || isload == 'Y')
		select = Load();
	else if (isload == 'n' || isload == 'N')
		select = 0;
	else if (isload == 27)	// esc 코드
	{
		puts("게임을 종료합니다.\n");
		exit(1);
	}

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