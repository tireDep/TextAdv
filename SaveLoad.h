#ifdef SAVELOAD_H
#define SAVELOAD_H
#endif // SAVELOAD_H
#include "Basic.h"

void Save(int select)
{
	FILE *fp = fopen("save.dat", "w+b");	// + : ������ ����, b : ���̳ʸ� ���� -> �б� �Ұ���, �ӵ��� ������ �뷮�� ���� => ���� ���� ����Ǿ��ִ��� Ȯ���� �ʿ䰡 ����
	// ������ġ�� �����ε�

	if (fp == NULL)
	{
		printf("File dosen't exist!\n");
		return;
	}

	// select���� ���Ͽ� ����ϴ� �κ�
	if (1 == fwrite(&select, sizeof(int), 1, fp))
		printf("Save Successed\n");
	else
		printf("Save Failed\n");
	// ���� ���� �� 1 ��ȯ
	// �ּҴ� ������!
	// �ּ�(void const* : �� �������� �𸣱� ����), ũ��, ����, ���� => ������ ���۰� ��(ũ��, ���� =>  |ũ��*����|)�� ���Ͽ� ����
	// ������ ��ȹ�ڿ� ����ΰ�

	fclose(fp);
}

int Load()
{
	FILE *fp = fopen("save.dat", "rb");	// rb : ���̳ʸ������� ��
	if (fp == NULL)
	{
		printf("File dosen't exist!\n");
		return 0;
	}

	// ����� select ���� �о��
	int loadSelect = 0;
	if (fread(&loadSelect, sizeof(int), 1, fp) == 1)
		printf("Load Success!\n");
	else
		printf("Load Failed\n");

	fclose(fp);	
	return loadSelect;
}