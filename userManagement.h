#ifndef __USER_MANAGEMENT_H__
#define __USER_MANAGEMENT_H__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//���1 ȸ�� ����
void showMemFunctions(List *);
void makeStop();
void showUserList(List *);
void showUser(LData);

//���2 ȸ�� ����ϱ�
void insertMemFunctions();
void insertUser(List *, int);
int findMaxId(List *);


//���3 ȸ�� �����ϱ�
void deleteMemFunctions(List *);
void deleteMember(List *, Node **, int);

//���4 ȸ������ �����ϱ�
void updateMemFunctions(List *);
void showUpdateMenu();
void updateMember(Node **, int);
void updateMemberName(Node *);
void updateMemberAddress(Node *);
void updateMemberPhone(Node *);

//���5 ȸ�� �˻��ϱ�
void searchMemFunctions(List *);
void showSearchMenu();
Node** searchWithId(List *, int, int *);
Node** searchWithName(List *, int, int *);
Node** searchWithPhone(List *, int, int *);

//���6 �����ϱ�
void saveMemFunctions(List *);
void saveData(List *, FILE *);

//���7 �����ϱ�
void finishProgram(List *);
void finishProgramWithSave(List *);
void finishProgramWithoutSave();
void freeListData(List *);

//��Ÿ
void showBar(const char *);
int getTargetPos(const char *);
void clearReadLine();
int checkNameInput(char *);
int checkPhoneInput(char *);
int two_n(int);

#endif
