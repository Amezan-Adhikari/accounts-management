#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BUFFER 1024

struct User{
    int id;
    char name[100];
    char password[100];
    int amount;  
};


void writeFile(char * _INPUT_STRING_,char *_FILE_NAME_){
    FILE * file = fopen(_FILE_NAME_,"a");
    fprintf(file,"%s\n",_INPUT_STRING_);
    fclose(file);
};

void copyfile(char * OLD_FILE_NAME_, char * NEW_FILE_NAME_){
    FILE* file = fopen(OLD_FILE_NAME_,"r");
    FILE * temp = fopen(NEW_FILE_NAME_,"w");
    if(file==NULL || temp == NULL){
        perror("couldn't open file");
        return;
    }
    char buffer[MAX_BUFFER];
    while(!feof(file)){
        fgets(buffer,MAX_BUFFER,file);
        fputs(buffer,temp);

        buffer[0] = '\0';
    }

    fclose(file);
    fclose(temp);
}

void getLine(char * _FILE_NAME_,int LINE , char * _BUFFER_){
    FILE *_FILE_ = fopen(_FILE_NAME_,"r");
    int CURRENT_LINE = 1;
    while(!feof(_FILE_)){   
        fgets(_BUFFER_,MAX_BUFFER,_FILE_);
        if(CURRENT_LINE == LINE){
           break; 
        }
        else{
            _BUFFER_[0]='\0';
        }
        CURRENT_LINE++;
    }
    fclose(_FILE_);
}
void setLine(char * _FILE_NAME_,int LINE , char * _BUFFER_){
    FILE * _FILE_ = fopen(_FILE_NAME_,"r");
    FILE * _TEMP_ = fopen("temp____.txt","w");
    if(_FILE_==NULL || _TEMP_ == NULL){
        perror("couldn't open file");
        return;
    }
    char buffer[MAX_BUFFER];
    int CURRENT_LINE = 1;
    while(!feof(_FILE_)){
        fgets(buffer,MAX_BUFFER,_FILE_);
        if(CURRENT_LINE == LINE){
            fprintf(_TEMP_,"%s\n",_BUFFER_);
        }
        else{
            fputs(buffer,_TEMP_);
        }
        buffer[0]='\0';
        CURRENT_LINE++;
    }

    fclose(_FILE_);
    fclose(_TEMP_);
    remove(_FILE_NAME_);
    rename("temp____.txt",_FILE_NAME_);
}


void parseUserData(struct User *user, char *string) {
    // Remove surrounding parentheses and trailing underscore
    char *cleanString = strdup(string);
    cleanString[strlen(cleanString) - 1] = '\0'; // Remove last character (closing parenthesis)
    memmove(cleanString, cleanString + 1, strlen(cleanString)); // Remove first character (opening parenthesis)
    
    // Define delimiters
    char DELIMITER[] = ":~";
    char *TOKEN = strtok(cleanString, DELIMITER);
    int count = 1;

    while (TOKEN != NULL) {
        if (count % 2 == 0) {
            // Even counts are values
            switch (count) {
                case 2:
                    user->id = atoi(TOKEN);
                    break;
                case 4:
                    strcpy(user->name, TOKEN);
                    break;
                case 6:
                    strcpy(user->password,TOKEN);
                    break;
                case 8:
                    user->amount = atoi(TOKEN);
                    break;
                default:
                    break;
            }
        }
        TOKEN = strtok(NULL, DELIMITER);
        count++;
    }

    // Clean up
    free(cleanString);
}

void hashPassword(char * password){
    int i = 0;
    while(password[i]){
        password[i]+= 20;
        i++;
    }
}

void stringifyUserData(struct User user,char * stringify){
    strcpy(stringify,"");
    strcat(stringify,"(id:");
    char buffer[33];
    sprintf(buffer, "%d", user.id);
    strcat(stringify,buffer);
    strcat(stringify,"~name:");
    strcat(stringify,user.name);
    strcat(stringify,"~password:");
    strcat(stringify,user.password);
    strcat(stringify,"~ammount:");
    sprintf(buffer, "%d", user.amount);
    strcat(stringify,buffer);
    strcat(stringify,"~)");
}