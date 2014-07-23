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
			puts("�߸� �����Ͽ����ϴ�.");
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
	puts("\t\t\t    ȸ�� ���� ���α׷�");
	puts("===============================================================================");
}

void showMainMenu()
{
	puts("1. ȸ�� ����");
	puts("2. ȸ�� ����ϱ�");
	puts("3. ȸ�� �����ϱ�");
	puts("4. ȸ������ �����ϱ�");
	puts("5. ȸ�� �˻��ϱ�");
	puts("6. �����ϱ�");
	puts("7. �����ϱ�");
	puts("===============================================================================");

	fputs("� ����� �����ðڽ��ϱ�?<���ڷ� �Է�> ", stdout);
}

void initListWithFile(List * list, FILE * fp)
{
	char str[256];
	int count = 0;
	LData data;

	fgets(str, sizeof(str), fp); // ù° �� ����

	while (fgets(str, sizeof(str), fp) != NULL)
	{
		data.userId = atoi(strtok(str, "\t"));
		strcpy(data.userName, strtok(NULL, "\t"));
		strcpy(data.userAddress, strtok(NULL, "\t"));
		strcpy(data.handphone, strtok(NULL, "\n"));
		LInsert(list, &data);
	}
}
