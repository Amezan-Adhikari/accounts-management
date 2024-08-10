#include <stdio.h>

struct User{
    int id;
    char name[100];
    char password[100];
    int amount;
};

//parse or stringify data
void parseUserData(struct User *user, char *string);
void stringifyUserData(struct User user,char * stringify);


//file functions
void writeFile(char * _INPUT_STRING_,char *_FILE_NAME_);
void copyfile(char * OLD_FILE_NAME_, char * NEW_FILE_NAME_);
void getLine(char * _FILE_NAME_,int LINE , char * _BUFFER_);
void setLine(char * _FILE_NAME_,int LINE , char * _BUFFER_);

//password functions
void hashPassword(char * password);