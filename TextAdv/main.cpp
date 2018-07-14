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
	printf("�����͸� �ε��ұ��? [Y : �ε� / N : ó������]\n\n");
	char isload = _getch();	// load ���� ���
	if (isload == 'y' || isload == 'Y')
		select = Load();
	else if (isload == 'n' || isload == 'N')
		select = 0;

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