#pragma once
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "GeneralFunctions.h"
#include "Def.h"
#define USERNAME_LENGTH 6
#define PASSWORD_LENGTH 7 //including '\0'
#define MAX_STR_LEN 255

typedef struct {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} Login;

void     initLoginNoUser(Login* login);
void     writeLoginToTextFile(FILE* fp, const Login* login);
int      readLoginFromTextFile(FILE* fp, Login* login);
int      writeLoginToBinFileCompressed(FILE* fp, const Login* pLogin);
int      readLoginFromBinFileCompressed(FILE* fp, Login* pLogin);
void     getPlayerUserName(char* userName);
void     getPlayerPassword(char* userName);
int      compareUserName(const void* v1, const void* v2);
int      isValidPassword(const char* password);
int      isValidUserName(const char* UserName);
int      isSameUserName(const Login* User1, const Login* User2);
int      isUserName(const Login* User1, const char* userName);//return 0 if true, -1 if false

