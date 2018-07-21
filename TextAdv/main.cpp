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

	puts("- MyGame -\n\n�̾��ϱ�(Y)\nó������(N)\n��������(ESC)\n");
	int select = 0;
	char isload = _getch();
	if (isload == 'y' || isload == 'Y')
		select = Load();
	else if (isload == 'n' || isload == 'N')
		select = 0;
	else if (isload == 27)	// esc �ڵ�
	{
		puts("������ �����մϴ�.\n");
		exit(1);
	}

	while (true)	// ������ ������! -> �ݺ� �����ִ°� mainupdate
	{
		int nextSelect = paragraphList.Process(select);

		if (nextSelect < 0)	// ������ ����
			break;
		else
			select = nextSelect;
	}

	Save(select);
	paragraphList.Destory();

	puts("���α׷��� �����մϴ�.");
	return 0;
}