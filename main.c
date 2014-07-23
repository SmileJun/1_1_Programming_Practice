#define CRT_SECURE_NO_WARNINGS
#include "DBLinkedList.h"
#include "main.h"
#include "userManagement.h"

int main(void)
{
	int choose;

	List * userList = (List*)malloc(sizeof(List));
	initList(userList);

	FILE * readFile = fopen("data.txt", "rt");
	if (readFile == NULL)
	{
		puts("data.txt file open error\n");
		return -1;
	}

	initListWithFile(userList, readFile);

	do{
		showMainBar();
		showMainMenu();
		scanf("%d", &choose);

		switch (choose)
		{
		case 1:
			showMemFunctions(userList);
			break;
		case 2:
			insertMemFunctions(userList);
			break;
		case 3:
			deleteMemFunctions(userList);
			break;
		case 4:
			updateMemFunctions(userList);
			break;
		case 5:
			searchMemFunctions(userList);
			break;
		case 6:
			saveMemFunctions(userList);
			break;
		case 7:
			finishProgram(userList);
			break;
		default:
			puts("잘못 선택하였습니다.");
			break;
		}
	} while (choose != 7);

	free(userList);
	fclose(readFile);
	return 0;
}

void showMainBar()
{
	system("cls");
	puts("===============================================================================");
	puts("\t\t\t    회원 관리 프로그램");
	puts("===============================================================================");
}

void showMainMenu()
{
	puts("1. 회원 보기");
	puts("2. 회원 등록하기");
	puts("3. 회원 삭제하기");
	puts("4. 회원정보 수정하기");
	puts("5. 회원 검색하기");
	puts("6. 저장하기");
	puts("7. 종료하기");
	puts("===============================================================================");

	fputs("어떤 명령을 내리시겠습니까?<숫자로 입력> ", stdout);
}

void initListWithFile(List * list, FILE * fp)
{
	char str[256];
	int count = 0;
	LData data;

	fgets(str, sizeof(str), fp); // 첫째 줄 제거

	while (fgets(str, sizeof(str), fp) != NULL)
	{
		data.userId = atoi(strtok(str, "\t"));
		strcpy(data.userName, strtok(NULL, "\t"));
		strcpy(data.userAddress, strtok(NULL, "\t"));
		strcpy(data.handphone, strtok(NULL, "\n"));
		LInsert(list, &data);
	}
}
