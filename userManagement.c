#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "DBLinkedList.h"
#include "userManagement.h"

#define MAX_SHOW_USER 20

//���1 ȸ�� ����
void showMemFunctions(List * list)
{
	showBar("ȸ�� ����");
	showUserList(list);
	system("pause");
}

void showUserList(List * list)
{
	int counter = 0;
	LData data;

	if (list->numOfData == 0)
		puts("�����Ͱ� �����ϴ�.");
	else if (list->numOfData > 0)
	{
		LFirst(list);
		
		fprintf(stdout, "%8s\t%-10s\t%-30s\t%-15s\n", "ȸ�����̵�", "ȸ���̸�", "ȸ���ּ�", "����ó");
		while (LNext(list, &data))
		{
			showUser(data);
		
			if (++counter % MAX_SHOW_USER == 0)
			{
				makeStop();
				system("cls");
				fprintf(stdout, "%8s\t%-10s\t%-30s\t%-15s\n", "ȸ�����̵�", "ȸ���̸�", "ȸ���ּ�", "����ó");
			}
		}
	}
}

void makeStop()
{
	int stopper = 0;

	while (1) // ���� �Է����� ������ �ݺ����� ��� ����
	{
		clearReadLine();

		fputs("\n- ���� ���ȭ���� ���÷��� ���͸� ��������.",stdout);
		stopper = fgetc(stdin);
		if (stopper == 10)
			break;
	}
}

void showUser(LData data)
{
	fprintf(stdout, "%8d\t%-10s\t%-30s\t%-15s\n", data.userId,
		data.userName, data.userAddress, data.handphone);
}



//���2 ȸ�� ����ϱ�
void insertMemFunctions(List * list)
{
	int current_maxId = 0;
	clearReadLine();

	current_maxId = findMaxId(list);
	showBar("ȸ�� ���");
	insertUser(list, current_maxId);

	puts("ȸ�� ����� �Ϸ�Ǿ����ϴ�.");

	system("pause");
}

void insertUser(List * list, int current_maxId)
{
	LData newData;
	char tempStr[256]; 
	int validName;
	int validPhone;

	newData.userId = ++current_maxId;

	puts("�߰��Ͻ� �����͸� �Է��ϼ���.");
	printf("ID		: %d \n", newData.userId);

	do
	{
		fputs("�̸�		: ", stdout);
		gets(tempStr);
		validName = checkNameInput(tempStr);
	} while (validName == FALSE);
	strcpy(newData.userName, tempStr);


	fputs("�ּ�		: ", stdout);
	gets(tempStr);
	strcpy(newData.userAddress, tempStr);

	do
	{
		fputs("��ȭ��ȣ	: ", stdout);
		gets(tempStr);
		validPhone = checkPhoneInput(tempStr);
	} while (validPhone == FALSE);
	strcpy(newData.handphone, tempStr);

	LInsert(list, &newData);
}

int findMaxId(List * list)
{
	int i;
	int maxId = 0;

	list->cur = list->head;
	maxId = list->cur->data.userId;

	for (i = 0; i < list->numOfData; i++)
	{
		if (maxId < list->cur->data.userId)
			maxId = list->cur->data.userId;
		list->cur = list->cur->next;
	}
	
	return maxId;
}


//���3 ȸ�� �����ϱ�
void deleteMemFunctions(List * list)
{
	int choose;
	int findNodeNum = 0;
	Node ** findNodeArr = (Node**)NULL;

	do{
		showBar("ȸ�� ����");
		showSearchMenu();
		scanf("%d", &choose);
		getchar();

		switch (choose)
		{
		case 1:
			findNodeArr = searchWithId(list, TRUE, &findNodeNum);
			deleteMember(list, findNodeArr, findNodeNum);
			break;
		case 2:
			findNodeArr = searchWithName(list, TRUE, &findNodeNum);
			deleteMember(list, findNodeArr, findNodeNum);
			break;
		case 3:
			findNodeArr = searchWithPhone(list, TRUE, &findNodeNum);
			deleteMember(list, findNodeArr, findNodeNum);
			break;
		case 4:
			break;
		default:
			puts("�߸� �����Ͽ����ϴ�.");
			break;
		}
	} while (choose != 4);

	system("pause");
}

void deleteMember(List * list, Node ** nodeArr, int nodeNum)
{
	int choose = 0;
	int selectId = 0;
	
	if (nodeNum < 1) // ã�� ��� ������ 0���� ���
		return;
	else if (nodeNum > 1) // ã�� ��� ������ 2�� �̻��� ��� 
		selectId = getTargetPos("����");
	// ã�� ��� ������ 1���� ��� ���ǹ� ó���� ���� �ʴ´�

	Node * targetNode = nodeArr[selectId];
	list->cur = targetNode;

	LRemove(list);
	puts("����� �����Ͽ����ϴ�.");

	free(nodeArr);
	system("pause");
}


//���4 ȸ������ �����ϱ�
void updateMemFunctions(List * list)
{
	int choose;
	int findNodeNum = 0;
	Node ** findNodeArr = (Node**)NULL;

	do{
		showBar("ȸ������ ����");
		showSearchMenu();
		scanf("%d", &choose);
		getchar();

		switch (choose)
		{
		case 1:
			findNodeArr = searchWithId(list, TRUE, &findNodeNum);
			updateMember(findNodeArr, findNodeNum);
			break; 
		case 2:
			findNodeArr = searchWithName(list, TRUE, &findNodeNum);
			updateMember(findNodeArr, findNodeNum);	
			break;
		case 3:
			findNodeArr = searchWithPhone(list, TRUE, &findNodeNum);
			updateMember(findNodeArr, findNodeNum);	
			break;
		case 4:
			break;
		default:
			puts("�߸� �����Ͽ����ϴ�.");
			break;
		}
	} while (choose != 4);

	system("pause");
}

void updateMember(Node ** nodeArr, int nodeNum)
{
	int choose = 0;
	int selectId = 0; 
	
	if (nodeNum < 1) // ã�� ��� ������ 0���� ���
		return;
	else if (nodeNum > 1) // ã�� ��� ������ 2�� �̻��� ��� 
		selectId = getTargetPos("����");
	// ã�� ��� ������ 1���� ��� ���ǹ� ó���� ���� �ʴ´�

	Node * targetNode = nodeArr[selectId];

	do{
		showUpdateMenu();
		scanf("%d", &choose);
		getchar();

		switch (choose)
		{
		case 1:
			updateMemberName(targetNode);
			break;
		case 2:
			updateMemberAddress(targetNode);
			break;
		case 3:
			updateMemberPhone(targetNode);
			break;
		case 4:
			break;
		default:
			puts("�߸� �����Ͽ����ϴ�.");
			break;
		}
	} while (choose != 4);
	
	free(nodeArr);
	system("pause");
}

void showUpdateMenu()
{
	puts("\t\t\t� �����͸� �����Ͻðڽ��ϱ�?");
	puts("");
	puts("\t\t1. �̸�");
	puts("\t\t2. �ּ�");
	puts("\t\t3. ��ȭ��ȣ");
	puts("\t\t4. ���");
	fputs("\t\t  : ", stdout);
}

void updateMemberName(Node * updateNode)
{
	char tempStr[256];
	int validName;

	do
	{
		fputs("�̸� �����͸� �����Ͻʽÿ�. : ", stdout);
		gets(tempStr);
		validName = checkNameInput(tempStr);
	} while (validName == FALSE);
	strcpy(updateNode->data.userName, tempStr);
}

void updateMemberAddress(Node * updateNode)
{
	char tempStr[256];

	fputs("�ּ� �����͸� �����Ͻʽÿ�. : ", stdout);
	gets(tempStr);
	
	strcpy(updateNode->data.userAddress, tempStr);
}

void updateMemberPhone(Node * updateNode)
{
	char tempStr[256];
	int validPhone;

	do
	{
		fputs("��ȭ��ȣ	: ", stdout);
		gets(tempStr);
		validPhone = checkPhoneInput(tempStr);
	} while (validPhone == FALSE);
	strcpy(updateNode->data.handphone, tempStr);
}




//���5 ȸ�� �˻��ϱ�
void searchMemFunctions(List * list)
{
	int choose;

	do{
		showBar("ȸ�� �˻�");
		showSearchMenu();
		scanf("%d", &choose);
		getchar();

		switch (choose)
		{
		case 1:
			searchWithId(list, FALSE, NULL);
			break;
		case 2:
			searchWithName(list, FALSE, NULL);
			break;
		case 3:
			searchWithPhone(list, FALSE, NULL);
			break;
		case 4:
			break;
		default:
			puts("�߸� �����Ͽ����ϴ�.");
			break;
		}
	} while (choose != 4);

	system("pause");
}

void showSearchMenu()
{
	puts("\t\t\t� ������ ã���ðڽ��ϱ�?");
	puts("");
	puts("\t\t1. ID");
	puts("\t\t2. �̸�");
	puts("\t\t3. ��ȭ��ȣ");
	puts("\t\t4. ���");
	fputs("\t\t  : ", stdout);
}

Node** searchWithId(List * list, int needNodeArr, int * nodeArrNum)
{
	LData data;
	Node ** nodeArr = (Node**)malloc(sizeof(Node*));
	int findDataNum = 0;
	int multiple_factor = 0;
	char findId[50];

	fputs("\nã���� ID : ", stdout); gets(findId);
	puts("");

	LFirst(list);
	while (LNext(list, &data))
	{
		if (data.userId == atoi(findId))
		{
			printf("#%d", findDataNum++ + 1); showUser(data);

			if (needNodeArr == TRUE)
			{
				nodeArr[findDataNum-1] = list->cur->prev;

				if (findDataNum % two_n(multiple_factor++) == 0) // ã�� ������ ���� 1,2,4,8 ó�� 2�� ������ ���޽� �迭 Ȯ��
					nodeArr = (Node **)realloc(nodeArr, 2 * findDataNum * sizeof(Node*));
			}
		}
	}
	
	if (findDataNum == 0)
		puts("ã���ô� �����Ͱ� �������� �ʽ��ϴ�.");

	puts("\n\t\t\t�˻��� �Ϸ��Ͽ����ϴ�.\n");
	system("pause");

	if (needNodeArr == TRUE)
	{
		*nodeArrNum = findDataNum;
		return nodeArr;
	}
	else
	{
		free(nodeArr);
		return (Node**)NULL;
	}
}

Node** searchWithName(List * list, int needNodeArr, int * nodeArrNum)
{
	LData data;
	Node ** nodeArr = (Node**)malloc(sizeof(Node*));
	int findDataNum = 0;
	int multiple_factor = 0;
	char findName[100];

	fputs("\nã���� �̸� : ", stdout); gets(findName);
	puts("");

	LFirst(list);
	while (LNext(list, &data))
	{
		if (strcmp(data.userName, findName) == 0)
		{
			printf("#%d", findDataNum++ + 1); showUser(data);
			
			if (needNodeArr == TRUE)
			{
				nodeArr[findDataNum - 1] = list->cur->prev;
			
				if (findDataNum % two_n(multiple_factor++) == 0)
					nodeArr = (Node **)realloc(nodeArr, 2 * findDataNum * sizeof(Node*));
			}
		}
	}

	if (findDataNum == 0)
		puts("ã���ô� �����Ͱ� �������� �ʽ��ϴ�.");

	puts("\n\t\t\t�˻��� �Ϸ��Ͽ����ϴ�.\n");
	system("pause");
	if (needNodeArr == TRUE)
	{
		*nodeArrNum = findDataNum;
		return nodeArr;
	}
	else
	{
		free(nodeArr);
		return (Node**)NULL;
	}
}

Node** searchWithPhone(List * list, int needNodeArr, int * nodeArrNum)
{
	LData data;
	Node ** nodeArr = (Node**)malloc(sizeof(Node*));
	int findDataNum = 0;
	int multiple_factor = 0;
	char findPhone[100];

	fputs("\nã���� ��ȭ��ȣ : ", stdout); gets(findPhone);
	puts("");

	LFirst(list);
	while (LNext(list, &data))
	{
		if (strcmp(data.handphone, findPhone) == 0)
		{
			printf("#%d", findDataNum++ + 1); showUser(data);

			if (needNodeArr == TRUE)
			{
				nodeArr[findDataNum - 1] = list->cur->prev;
				
				if (findDataNum % two_n(multiple_factor++) == 0)
					nodeArr = (Node **)realloc(nodeArr, 2 * findDataNum * sizeof(Node*));
			}
		}
	}

	if (findDataNum == 0)
		puts("ã���ô� �����Ͱ� �������� �ʽ��ϴ�.");

	puts("\n\t\t\t�˻��� �Ϸ��Ͽ����ϴ�.\n");
	system("pause");
	if (needNodeArr == TRUE)
	{
		*nodeArrNum = findDataNum;
		return nodeArr;
	}
	else
	{
		free(nodeArr);
		return (Node**)NULL;
	}
}




//���6 �����ϱ�
void saveMemFunctions(List * list)
{
	FILE * writeFile = fopen("data.txt", "wt");

	if (writeFile == NULL)
	{
		puts("data.txt file open error\n");
		return;
	}

	showBar("ȸ�� ����");
	saveData(list, writeFile);
	puts("������ ������ �Ϸ��Ͽ����ϴ�.");

	fclose(writeFile);
	system("pause");
}

void saveData(List * list, FILE * fp)
{
	int i = 0;

	list->cur = list->head;

	fprintf(fp, "%s", "ȸ�����̵�\tȸ���̸�\tȸ���ּ�\t�ڵ��� ��ȣ\n");
	for (i = 0; i < list->numOfData; i++)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\n", list->cur->data.userId, 
			list->cur->data.userName, list->cur->data.userAddress, list->cur->data.handphone);
		list->cur = list->cur->next;
	}
}




//���7 �����ϱ�
void finishProgram(List * list)
{
	char choose;

	while (1)
	{
		clearReadLine();
		showBar("�����ϱ�");

		puts("\t\t\t�����Ͻðڽ��ϱ�?(Yes : y, No : n)");
		fputs("\t\t: ", stdout); scanf("%c", &choose); getchar();

		if (choose == 'y' || choose == 'Y')
		{
			finishProgramWithSave(list);
			break;
		}
		else if (choose == 'n' || choose == 'N')
		{
			finishProgramWithoutSave(list);
			break;
		}
		else
		{
			puts("�߸� �Է��ϼ̽��ϴ�.");
			system("pause");
		}
	}
	system("cls");
	showBar("�����ϱ�");
	puts("���α׷��� �����մϴ�.");
}

void finishProgramWithSave(List * list)
{
	saveMemFunctions(list);
	freeListData(list);
}

void finishProgramWithoutSave(List * list)
{
	freeListData(list);
}

void freeListData(List * list)
{
	while (LFirst(list))
		LRemove(list);
}




// ��Ÿ
void showBar(const char * str)
{
	system("cls");
	puts("===============================================================================");
	printf("\t\t\t\t%s\n", str);
	puts("===============================================================================");
}

int getTargetPos(const char * str)
{
	int selectId;
	printf("%s�ϰ��� �ϴ� ������ ��ȣ�� �������ּ���. : ", str);
	scanf("%d", &selectId); // k��° ������ ����
	selectId--; // k-1�� �ε���ȭ

	return selectId;
}

void clearReadLine()
{
	while (getchar() != '\n');
}

int checkNameInput(char * str)
{
	int isValid = TRUE;
	int length = strlen(str);

	if (length < 1)
	{
		puts("��� �� ���� �̻� �Է��ؾ� �մϴ�.");
		isValid = FALSE;
	}
	else if (length > 10)
	{
		puts("�̸��� �ʹ� ��ϴ�. �ٽ� �Է����ּ���.");
		isValid = FALSE;
	}
		
	return isValid;
}

int checkPhoneInput(char * str)
{
	int isValid = TRUE;
	int length = strlen(str);
	int pos = 0;

	//000-0000-0000 type�� ��� ���̴� 13
	if (length != 13)
	{
		isValid = FALSE;
	}
	else // �� �ε��� üũ
	{
		for (pos = 0; pos < 3; pos++) //0~2 check
			if (str[pos] > 57 || str[pos] < 48)
				isValid = FALSE;
		
		if (str[pos++] != '-') //3 check
			isValid = FALSE;
		
		for (; pos < 8; pos++) //4 check
			if (str[pos] > 57 || str[pos] < 48)
				isValid = FALSE;
		
		if (str[pos++] != '-') //8 check
			isValid = FALSE;

		for (; pos < 13; pos++) //9~12 check
			if (str[pos] > 57 || str[pos] < 48)
				isValid = FALSE;
	}
	
	if (isValid == FALSE)
		puts("�Է� ������ ����� ���ڷ� 000-0000-0000 ��縸 �����մϴ�. �ٽ� �Է����ּ���.");

	return isValid;
}

int two_n(int n)
{
	int i;
	const int power_factor = 2;
	int result = 1;
	
	if (n == 0)
		return result;
	else if (n > 0)
	{
		for (i = 0; i < n; i++)
			result *= power_factor;
	}

	return result;
}
