#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

void handleExistingUser();
void handleNewUser();

int main() {
    printf("\n\n\t\t\033[0;33m========== welcome to our banking System ========\033[0m \n");
    printf("\t\t                1) Create New User          \n");
    printf("\t\t                2) Get existing User          \n\n");

    char choice;
    scanf(" %c",&choice);
    switch (choice)
    {
    case '1':
        handleNewUser();
        break;
    case '2':
        handleExistingUser();
        break;

        default:
        printf("\033[0;31mInvalid Option\033[0m\n");
        break;
    }
    return 0;
}


void handleNewUser(){
    struct  User user;

    char name[100];
    char password[100];
    char confirmPassword[100];
    printf("enter your Name : ");
    scanf("%s",name);
    printf("set 4 digit Pin : ");
    scanf("%s",password);
    printf("confirm Pin: ");
    scanf("%s",confirmPassword);

    if(strcmp(confirmPassword,password)!=0){
        printf("\n\033[0;31mPins don't match\033[0m\n");
        return;
    }

    FILE *file = fopen("data.txt","r");
    char output[33];
    int currentUsers;
    if(fscanf(file,"%d",&currentUsers)==EOF){
        currentUsers = 0;
    }

    fclose(file);
    

    strcpy(user.name,name);
    hashPassword(password);
    strcpy(user.password,password);
    user.id = 100000+currentUsers;
    user.amount = 0;

    sprintf(output,"%d",++currentUsers);
    setLine("data.txt",1,output);
    
    char *stringifyUser = (char *)malloc(200*sizeof(char));
    stringifyUserData(user,stringifyUser);
    writeFile(stringifyUser,"data.txt");
    free(stringifyUser);
    printf("\033[0;32mThank you your account has been created with id : %d \033[0m\n", user.id);
}



void handleExistingUser(){
    
    printf("enter your name : ");
    char name[100];
    scanf("%s",name);
    printf("enter your pin  : ");
    char password[100];
    scanf("%s",password);


    FILE *file = fopen("data.txt","r");
    int currentUsers;
    if(fscanf(file,"%d",&currentUsers)==EOF){
        currentUsers = 0;
    }
    fclose(file);

    
    char* buffer = (char *)malloc(sizeof(char)*200);
    struct User user;
    int userLine = 0;
    char foundUser = 0;
    hashPassword(password);
    for(int i = 2; i <= currentUsers+1;i++){
        getLine("data.txt",i,buffer);
        parseUserData(&user,buffer);
        if(strcmp(user.password,password)==0 && strcmp(user.name,name) == 0){
            userLine = i;
            foundUser = 1;
            break; 
        }else{
            buffer[0]='\0';
        }
    }
    if(!foundUser){
        printf("\033[0;31mNo such user found\033[0m\n");
        return;
    }
    
    printf("\n<======User Details=====> \n");
    printf(" id      : %d\n",user.id);
    printf(" name    : %s\n",user.name);
    printf(" amount  : %d\n\n\n",user.amount);

    printf("\n1) Transfer Money");
    printf("\n2) Deposit ");
    printf("\n3) Withdraw ");
    char choice;
    scanf(" %c",&choice);
    int merchantUserLine=0;
    switch (choice)
    {
    case '2':
        printf("enter amount to deposit : ");
        int depositAmount;
        scanf("%d",&depositAmount);
        user.amount += depositAmount;
        char stringUser[100];
        stringifyUserData(user,stringUser); 
        setLine("data.txt",userLine,stringUser);
        printf("\033[0;32m thank you for your transaction \033[0m\n");
        break;

    case '3':
        printf("enter amount to withdraw : ");
        int withdrawAmount;
        scanf("%d",&withdrawAmount);
        if(user.amount < withdrawAmount){
            printf("\033[0;31mInsufficient Balance\033[0m\n");
            return;
        }

        user.amount -= withdrawAmount;
        stringifyUserData(user,stringUser); 
        setLine("data.txt",userLine,stringUser);
        printf("\033[0;32m thank you for your transaction \033[0m\n");
        break;

    case '1':
        printf("enter transfer account Name : ");
        char accountName[100];
        scanf("%s",accountName);
        printf("enter transfer account ID   : ");
        int accountID;
        scanf("%d",&accountID);
        printf("enter transfer ammount      : ");
        int transferAmmount;
        scanf("%d",&transferAmmount);

        if(user.amount < transferAmmount){
            printf("\033[0;31mInsufficient Balance\033[0m\n");
            return;
        }
        

        struct User merchant;
        
        char merchantBuffer[200];
        for(int i = 2; i <= currentUsers+1;i++){
        getLine("data.txt",i,merchantBuffer);
        parseUserData(&merchant,merchantBuffer);
           
        if(merchant.id == accountID && strcmp(merchant.name,accountName) == 0){
            merchantUserLine = i;
            foundUser = 1;
            break; 
        }else{
            merchantBuffer[0]='\0';
        }
        }
        if(!foundUser){
            printf("\033[0;31mNo such user found\033[0m");
            return;
        }
        merchant.amount += transferAmmount;
        user.amount -= transferAmmount;
        stringifyUserData(user,stringUser); 
        setLine("data.txt",userLine,stringUser);

        char stringMerchant[200];
        stringifyUserData(merchant,stringMerchant);
        setLine("data.txt",merchantUserLine,stringMerchant);
        

        printf("successfully transfered Rs %d to %s \n\n",transferAmmount,accountName);
        printf("\033[0;32m thank you for your transaction \033[0m\n");

        break;
    
    default:
        printf("\033[0;31mInvalid Option\033[0m");
        break;
    }
}