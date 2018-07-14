// 0616 ����
#include "Basic.h"
#include "sString.h"
#include "PrintLib.h"
#include "CSVLIB.h"
#include "SaveLoad.h"

int main(void)
{
	sParagraphList paragraphList;
	ParsingCSV("story.csv", &paragraphList);

	int select = 0; // ó�� ����� ���� ǥ�� -> ����! // ��쿡 ���� nextselect�� ������ �� ����

	// ���� �޴� �߰� -> ���� ���� ȭ��/���ӽ���/�̾��ϱ�/���� �䷱��
	// puts("���Ӱ���\n���� ����\n�̾��ϱ�\n����\n");

	// �䱸����(��ȹ) : �ε带 �Ͻðڽ��ϱ�? Y or N (Y : �ε� / N : ó������)
	printf("�����͸� �ε��ұ��? [Y : �ε� / N : ó������]\n\n");
	char isload = _getch();	// load ���� ���
	if (isload == 'y' || isload == 'Y')
		select = Load();
	else if (isload == 'n' || isload == 'N')
		select = 0;

	while (true)	// ������ ������! -> �ݺ� �����ִ°� mainupdate
	{
		int nextSelect = 0;	// ������ ����� ���� ǥ��
		
		if(select<paragraphList.count)
		{
			printf("\n");
			nextSelect = PrintParagraph(&paragraphList.list[select]);
		}
		else
			break; // �߸� �Է½� ����

		if (nextSelect < 0)	// ������ ����
			break;
		else
		{
			select = nextSelect;
		}
	}

	Save(select);	// ����

	// malloc ����� ���� free �޸� �����ʿ���!
	for (int i = 0; i < paragraphList.count; i++)
	{
		// free(paragraphList.list[i].stringList);
		paragraphList.list[i].current = paragraphList.list[i].start;
		while (NULL != paragraphList.list[i].current->GetNext())
		{
			sString* nextString = paragraphList.list[i].current->GetNext();	// �������� ���
			free(paragraphList.list[i].current);	// ���� ���� ����
			paragraphList.list[i].current = nextString;	// ���� ������ ����� ���� ���� �������� ����
			// ���� ������ ������ ���� �ʰ� ���� ������ �����ϸ� ���� ������ �� ���� ����!(Linked List)
		}
	}
	free(paragraphList.list);

	puts("���α׷��� �����մϴ�.");
	return 0;
}