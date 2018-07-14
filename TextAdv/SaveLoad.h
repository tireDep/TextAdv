#ifdef SAVELOAD_H
#define SAVELOAD_H
#endif // SAVELOAD_H
#include "Basic.h"

void Save(int select)
{
	FILE *fp = fopen("save.dat", "w+b");	// + : 없으면 생성, b : 바이너리 파일 -> 읽기 불가능, 속도가 빠르고 용량이 작음 => 굳이 뭐가 저장되어있는지 확인할 필요가 없음
	// 저장위치는 랜덤인듯

	if (fp == NULL)
	{
		printf("File dosen't exist!\n");
		return;
	}

	// select값을 파일에 기록하는 부분
	if (1 == fwrite(&select, sizeof(int), 1, fp))
		printf("Save Successed\n");
	else
		printf("Save Failed\n");
	// 저장 성공 시 1 반환
	// 주소는 포인터!
	// 주소(void const* : 뭘 저장할지 모르기 때문), 크기, 개수, 파일 => 변수의 시작과 끝(크기, 개수 =>  |크기*개수|)를 파일에 저장
	// 개수는 기획자와 상담인가

	fclose(fp);
}

int Load()
{
	FILE *fp = fopen("save.dat", "rb");	// rb : 바이너리파일을 염
	if (fp == NULL)
	{
		printf("File dosen't exist!\n");
		return 0;
	}

	// 저장된 select 값을 읽어옴
	int loadSelect = 0;
	if (fread(&loadSelect, sizeof(int), 1, fp) == 1)
		printf("Load Success!\n");
	else
		printf("Load Failed\n");

	fclose(fp);	
	return loadSelect;
}