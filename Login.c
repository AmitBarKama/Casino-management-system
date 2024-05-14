#define _CRT_SECURE_NO_WARNINGS
#include "Login.h"
#include <ctype.h>


void initLoginNoUser(Login* login) {
    char temp[MAX_STR_LEN];
    getPlayerPassword(temp);
    strcpy(login->password, temp);
}

void writeLoginToTextFile(FILE* fp, const Login* login)
{
    fprintf(fp, "%s\n%s\n", login->username, login->password);
}

int readLoginFromTextFile(FILE* fp, Login* login)
{
    if (!fp)
    {
        printf("File can not open.\n");
        return 0;
    }
    if (fgets(login->username, USERNAME_LENGTH, fp) == NULL) {
        printf("Failed to read username.\n");
        return 0;
    }
    login->username[strcspn(login->username, "\n")] = 0; //Replace newline with null terminator
    int ch;
    while ((ch = fgetc(fp)) != '\n');
    if (fgets(login->password, PASSWORD_LENGTH, fp) == NULL) {
        printf("Failed to read password.\n");
        return 0;
    }
    login->password[strcspn(login->password, "\n")] = 0; //Replace newline with null terminator
    return 1;
}

int writeLoginToBinFileCompressed(FILE* fp, const Login* pLogin)
{
    if (!fp)
        return 0;
    BYTE data[10] = { 0 };
    data[0] = (((((pLogin->username[0]) & 0x7F) << 1) & 0xFE) | ((((pLogin->username[1]) & 0x7F) >> 6) & 0x1));
    data[1] = (((((pLogin->username[1]) & 0x7F) << 2) & 0xFC) | (((pLogin->username[2]) & 0x7F) >> 5) & 0x3);
    data[2] = (((((pLogin->username[2]) & 0x7F) << 3) & 0xFA) | ((((pLogin->username[3]) & 0x7F) >> 4) & 0x7));
    data[3] = (((((pLogin->username[3]) & 0x7F) << 4) & 0xF8) | ((((pLogin->username[4]) & 0x7F) >> 3) & 0xF));
    data[4] = (((((pLogin->username[4]) & 0x7F) << 5) & 0xF0) | ((((pLogin->password[0]) & 0x7F) >> 2) & 0x1F));
    data[5] = (((((pLogin->password[0]) & 0x7F) << 6) & 0x40) | ((((pLogin->password[1]) & 0x7F) >> 1) & 0x3F));
    data[6] = (((((pLogin->password[1]) & 0x7F) << 7) & 0x80) | (((pLogin->password[2]) & 0x7F) & 0x7F));
    data[7] = (((((pLogin->password[3]) & 0x7F) << 1) & 0xFE) | (((pLogin->password[4]) & 0x7F) >> 6) & 0x1);
    data[8] = (((((pLogin->password[4]) & 0x7F) << 2) & 0xFC) | (((pLogin->password[5]) & 0x7F) >> 5) & 0x3);
    data[9] = ((((pLogin->password[5]) & 0x7F) << 3) & 0xFA);
    if (fwrite(&data, sizeof(BYTE), 10, fp) != 10)
        return 0;
    return 1;
}

int readLoginFromBinFileCompressed(FILE* fp, Login* pLogin)
{
    if (!fp)
        return 0;
    BYTE data[10];
    if (fread(data, sizeof(BYTE), 10, fp) != 10)
        return 0;
    pLogin->username[0] = ((data[0] >> 1) & 0x7f);
    pLogin->username[1] = (((data[0] << 6) & 0x40) | ((data[1] >> 2) & 0x3f));
    pLogin->username[2] = (((data[1] << 5) & 0x60) | ((data[2] >> 3) & 0x1f));
    pLogin->username[3] = (((data[2] << 4) & 0x70) | ((data[3] >> 4) & 0xf));
    pLogin->username[4] = (((data[3] << 3) & 0x78) | ((data[4] >> 5) & 0x7));
    pLogin->username[5] = '\0';
    pLogin->password[0] = (((data[4] << 2) & 0x7c) | ((data[5] >> 6) & 0x3));
    pLogin->password[1] = (((data[5] << 1) & 0x7e) | ((data[6] >> 7) & 0x1));
    pLogin->password[2] = ((data[6] & 0x7f));
    pLogin->password[3] = ((data[7] >> 1) & 0x7f);
    pLogin->password[4] = (((data[7] << 6) & 0x40) | ((data[8] >> 2) & 0x3f));
    pLogin->password[5] = (((data[8] << 5) & 0x60) | ((data[9] >> 3) & 0x1f));
    pLogin->password[6] = '\0';
    return 1;
}

int isValidPassword(const char* password) {
    int length = (int)strlen(password);
    if (length != (PASSWORD_LENGTH - 1))
        return 0;
    int hasUpperCase = 0;
    int hasLowerCase = 0;
    int hasDigit = 0;

    for (int i = 0; i < length; ++i)
    {
        if (isupper(password[i]))
            hasUpperCase = 1;
        else if (islower(password[i]))
            hasLowerCase = 1;
        else if (isdigit(password[i]))
            hasDigit = 1;
    }
    return hasUpperCase && hasLowerCase && hasDigit;
}

int isValidUserName(const char* UserName) {
    int length = (int)strlen(UserName);
    if (length != (USERNAME_LENGTH - 1))
        return 0;
    int amountUpperCase = 0;

    for (int i = 0; i < length; ++i)
    {
        if (isupper(UserName[i]))
            amountUpperCase++;
    }
    return amountUpperCase == 5;
}

int isSameUserName(const Login* User1, const Login* User2)
{
    if (!User1 || !User2)
        return 0;
    if (strcmp(User1->username, User2->username) == 0)
        return 1;
    return 0;
}

int compareUserName(const void* v1, const void* v2)
{
    Login* User1 = (Login*)v1;
    Login* User2 = (Login*)v2;
    return strcmp(User1->username, User2->username);
}

int isUserName(const Login* User1, const char* userName) //return zero if true, -1 if false
{
    if (!User1)
        return -1;
    if (strcmp(User1->username, userName) == 0)
        return 0;
    return -1;
}

void getPlayerUserName(char* userName)
{
    char temp[MAX_STR_LEN];
    int ok = 1;
    do {
        ok = 1;
        printf("Enter player username - %d UPPER CASE letters\t", USERNAME_LENGTH - 1);
        myGets(temp, MAX_STR_LEN);
        if (strlen(temp) != USERNAME_LENGTH - 1)
        {
            printf("Username should be %d letters\n", USERNAME_LENGTH - 1);
            ok = 0;
        }
        if (!isValidUserName(temp))
            ok = 0;
    } while (!ok);
    strcpy(userName, temp);
}

void getPlayerPassword(char* password)
{
    char temp[MAX_STR_LEN];
    int ok = 1;
    do {
        ok = 1;
        printf("Enter player password - Must be %d characters long and include one uppercase letter, one lowercase letter, and one number \t", PASSWORD_LENGTH - 1);
        myGets(temp, MAX_STR_LEN);
        if (strlen(temp) != PASSWORD_LENGTH - 1)
        {
            printf("password should be %d letters\n", PASSWORD_LENGTH - 1);
            ok = 0;
        }
        if (!isValidPassword(temp))
            ok = 0;
    } while (!ok);
    strcpy(password, temp);
}
