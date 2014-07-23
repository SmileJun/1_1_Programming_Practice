#ifndef __USER_MANAGEMENT_H__
#define __USER_MANAGEMENT_H__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//기능1 회원 보기
void showMemFunctions(List *);
void makeStop();
void showUserList(List *);
void showUser(LData);

//기능2 회원 등록하기
void insertMemFunctions();
void insertUser(List *, int);
int findMaxId(List *);


//기능3 회원 삭제하기
void deleteMemFunctions(List *);
void deleteMember(List *, Node **, int);

//기능4 회원정보 수정하기
void updateMemFunctions(List *);
void showUpdateMenu();
void updateMember(Node **, int);
void updateMemberName(Node *);
void updateMemberAddress(Node *);
void updateMemberPhone(Node *);

//기능5 회원 검색하기
void searchMemFunctions(List *);
void showSearchMenu();
Node** searchWithId(List *, int, int *);
Node** searchWithName(List *, int, int *);
Node** searchWithPhone(List *, int, int *);

//기능6 저장하기
void saveMemFunctions(List *);
void saveData(List *, FILE *);

//기능7 종료하기
void finishProgram(List *);
void finishProgramWithSave(List *);
void finishProgramWithoutSave();
void freeListData(List *);

//기타
void showBar(const char *);
int getTargetPos(const char *);
void clearReadLine();
int checkNameInput(char *);
int checkPhoneInput(char *);
int two_n(int);

#endif
