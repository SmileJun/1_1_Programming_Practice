#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "DBLinkedList.h"
#include "userManagement.h"

#define MAX_SHOW_USER 20

//기능1 회원 보기
void showMemFunctions(List * list)
{
	showBar("회원 보기");
	showUserList(list);
	system("pause");
}

void showUserList(List * list)
{
	int counter = 0;
	LData data;

	if (list->numOfData == 0)
		puts("데이터가 없습니다.");
	else if (list->numOfData > 0)
	{
		LFirst(list);
		
		fprintf(stdout, "%8s\t%-10s\t%-30s\t%-15s\n", "회원아이디", "회원이름", "회원주소", "연락처");
		while (LNext(list, &data))
		{
			showUser(data);
		
			if (++counter % MAX_SHOW_USER == 0)
			{
				makeStop();
				system("cls");
				fprintf(stdout, "%8s\t%-10s\t%-30s\t%-15s\n", "회원아이디", "회원이름", "회원주소", "연락처");
			}
		}
	}
}

void makeStop()
{
	int stopper = 0;

	while (1) // 엔터 입력하지 않으면 반복문을 계속 실행
	{
		clearReadLine();

		fputs("\n- 다음 출력화면을 보시려면 엔터를 누르세요.",stdout);
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



//기능2 회원 등록하기
void insertMemFunctions(List * list)
{
	int current_maxId = 0;
	clearReadLine();

	current_maxId = findMaxId(list);
	showBar("회원 등록");
	insertUser(list, current_maxId);

	puts("회원 등록이 완료되었습니다.");

	system("pause");
}

void insertUser(List * list, int current_maxId)
{
	LData newData;
	char tempStr[256]; 
	int validName;
	int validPhone;

	newData.userId = ++current_maxId;

	puts("추가하실 데이터를 입력하세요.");
	printf("ID		: %d \n", newData.userId);

	do
	{
		fputs("이름		: ", stdout);
		gets(tempStr);
		validName = checkNameInput(tempStr);
	} while (validName == FALSE);
	strcpy(newData.userName, tempStr);


	fputs("주소		: ", stdout);
	gets(tempStr);
	strcpy(newData.userAddress, tempStr);

	do
	{
		fputs("전화번호	: ", stdout);
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


//기능3 회원 삭제하기
void deleteMemFunctions(List * list)
{
	int choose;
	int findNodeNum = 0;
	Node ** findNodeArr = (Node**)NULL;

	do{
		showBar("회원 삭제");
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
			puts("잘못 선택하였습니다.");
			break;
		}
	} while (choose != 4);

	system("pause");
}

void deleteMember(List * list, Node ** nodeArr, int nodeNum)
{
	int choose = 0;
	int selectId = 0;
	
	if (nodeNum < 1) // 찾은 노드 개수가 0개인 경우
		return;
	else if (nodeNum > 1) // 찾은 노드 개수가 2개 이상일 경우 
		selectId = getTargetPos("삭제");
	// 찾은 노드 개수가 1개인 경우 조건문 처리를 하지 않는다

	Node * targetNode = nodeArr[selectId];
	list->cur = targetNode;

	LRemove(list);
	puts("대상을 제거하였습니다.");

	free(nodeArr);
	system("pause");
}


//기능4 회원정보 수정하기
void updateMemFunctions(List * list)
{
	int choose;
	int findNodeNum = 0;
	Node ** findNodeArr = (Node**)NULL;

	do{
		showBar("회원정보 수정");
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
			puts("잘못 선택하였습니다.");
			break;
		}
	} while (choose != 4);

	system("pause");
}

void updateMember(Node ** nodeArr, int nodeNum)
{
	int choose = 0;
	int selectId = 0; 
	
	if (nodeNum < 1) // 찾은 노드 개수가 0개인 경우
		return;
	else if (nodeNum > 1) // 찾은 노드 개수가 2개 이상일 경우 
		selectId = getTargetPos("수정");
	// 찾은 노드 개수가 1개인 경우 조건문 처리를 하지 않는다

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
			puts("잘못 선택하였습니다.");
			break;
		}
	} while (choose != 4);
	
	free(nodeArr);
	system("pause");
}

void showUpdateMenu()
{
	puts("\t\t\t어떤 데이터를 수정하시겠습니까?");
	puts("");
	puts("\t\t1. 이름");
	puts("\t\t2. 주소");
	puts("\t\t3. 전화번호");
	puts("\t\t4. 취소");
	fputs("\t\t  : ", stdout);
}

void updateMemberName(Node * updateNode)
{
	char tempStr[256];
	int validName;

	do
	{
		fputs("이름 데이터를 수정하십시오. : ", stdout);
		gets(tempStr);
		validName = checkNameInput(tempStr);
	} while (validName == FALSE);
	strcpy(updateNode->data.userName, tempStr);
}

void updateMemberAddress(Node * updateNode)
{
	char tempStr[256];

	fputs("주소 데이터를 수정하십시오. : ", stdout);
	gets(tempStr);
	
	strcpy(updateNode->data.userAddress, tempStr);
}

void updateMemberPhone(Node * updateNode)
{
	char tempStr[256];
	int validPhone;

	do
	{
		fputs("전화번호	: ", stdout);
		gets(tempStr);
		validPhone = checkPhoneInput(tempStr);
	} while (validPhone == FALSE);
	strcpy(updateNode->data.handphone, tempStr);
}




//기능5 회원 검색하기
void searchMemFunctions(List * list)
{
	int choose;

	do{
		showBar("회원 검색");
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
			puts("잘못 선택하였습니다.");
			break;
		}
	} while (choose != 4);

	system("pause");
}

void showSearchMenu()
{
	puts("\t\t\t어떤 정보로 찾으시겠습니까?");
	puts("");
	puts("\t\t1. ID");
	puts("\t\t2. 이름");
	puts("\t\t3. 전화번호");
	puts("\t\t4. 취소");
	fputs("\t\t  : ", stdout);
}

Node** searchWithId(List * list, int needNodeArr, int * nodeArrNum)
{
	LData data;
	Node ** nodeArr = (Node**)malloc(sizeof(Node*));
	int findDataNum = 0;
	int multiple_factor = 0;
	char findId[50];

	fputs("\n찾으실 ID : ", stdout); gets(findId);
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

				if (findDataNum % two_n(multiple_factor++) == 0) // 찾은 데이터 수가 1,2,4,8 처럼 2의 제곱에 도달시 배열 확장
					nodeArr = (Node **)realloc(nodeArr, 2 * findDataNum * sizeof(Node*));
			}
		}
	}
	
	if (findDataNum == 0)
		puts("찾으시는 데이터가 존재하지 않습니다.");

	puts("\n\t\t\t검색을 완료하였습니다.\n");
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

	fputs("\n찾으실 이름 : ", stdout); gets(findName);
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
		puts("찾으시는 데이터가 존재하지 않습니다.");

	puts("\n\t\t\t검색을 완료하였습니다.\n");
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

	fputs("\n찾으실 전화번호 : ", stdout); gets(findPhone);
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
		puts("찾으시는 데이터가 존재하지 않습니다.");

	puts("\n\t\t\t검색을 완료하였습니다.\n");
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




//기능6 저장하기
void saveMemFunctions(List * list)
{
	FILE * writeFile = fopen("data.txt", "wt");

	if (writeFile == NULL)
	{
		puts("data.txt file open error\n");
		return;
	}

	showBar("회원 저장");
	saveData(list, writeFile);
	puts("데이터 저장을 완료하였습니다.");

	fclose(writeFile);
	system("pause");
}

void saveData(List * list, FILE * fp)
{
	int i = 0;

	list->cur = list->head;

	fprintf(fp, "%s", "회원아이디\t회원이름\t회원주소\t핸드폰 번호\n");
	for (i = 0; i < list->numOfData; i++)
	{
		fprintf(fp, "%d\t%s\t%s\t%s\n", list->cur->data.userId, 
			list->cur->data.userName, list->cur->data.userAddress, list->cur->data.handphone);
		list->cur = list->cur->next;
	}
}




//기능7 종료하기
void finishProgram(List * list)
{
	char choose;

	while (1)
	{
		clearReadLine();
		showBar("종료하기");

		puts("\t\t\t저장하시겠습니까?(Yes : y, No : n)");
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
			puts("잘못 입력하셨습니다.");
			system("pause");
		}
	}
	system("cls");
	showBar("종료하기");
	puts("프로그램을 종료합니다.");
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




// 기타
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
	printf("%s하고자 하는 데이터 번호를 선택해주세요. : ", str);
	scanf("%d", &selectId); // k번째 데이터 선택
	selectId--; // k-1로 인덱스화

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
		puts("적어도 한 글자 이상 입력해야 합니다.");
		isValid = FALSE;
	}
	else if (length > 10)
	{
		puts("이름이 너무 깁니다. 다시 입력해주세요.");
		isValid = FALSE;
	}
		
	return isValid;
}

int checkPhoneInput(char * str)
{
	int isValid = TRUE;
	int length = strlen(str);
	int pos = 0;

	//000-0000-0000 type인 경우 길이는 13
	if (length != 13)
	{
		isValid = FALSE;
	}
	else // 각 인덱스 체크
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
		puts("입력 가능한 양식은 숫자로 000-0000-0000 모양만 가능합니다. 다시 입력해주세요.");

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
