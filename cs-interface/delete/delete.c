//
// Created by guangtao on 2020/9/14.
//
#include "cJSON.h"
#include <string.h>
#include <sys/socket.h>

int sockfd = -1;
int sendret = 0;
int recret = 0;

cJSON * PRE_STRUCTURE(char *command) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(CLIENT, "command", cJSON_CreateString(command));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}

bool SIGN_WHOLE_PROCESS(char * account_name, char * password) {
    char SIGNAL_BUFFER[20] = {'\0'};
    cJSON * DIRECT_PACKAGE = SIGNIN_FROM_CLIENT_TO_SERVER(account_name, password);
    send(sockfd, cJSON_PrintUnformatted(DIRECT_PACKAGE), strlen(cJSON_PrintUnformatted(DIRECT_PACKAGE)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        return false;
    }
    if (SIGNIN_FROM_SERVER_TO_CLIENT(SIGNAL_BUFFER)) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return true;
    } else {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return false;
    }
}
// PRE_CONDITION: CODE CORRECT
// if (SIGN_WHOLE_PROCESS(email_addr, password) == true) {
//        cJSON * package = PRE_STRUCTURE("delete");
//        cJSON * CONTENT = cJSON_CreateObject();
//        cJSON_AddItemToObject(package, "content", CONTENT);
//        cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(email_addr));
//        return package;
//    }

bool LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(char * email_addr) {
    cJSON * package = PRE_STRUCTURE("delete");
    cJSON * CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(email_addr));
    // return package;
    char DELETE_BUFFER[30] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, DELETE_BUFFER, sizeof(DELETE_BUFFER), 0);
    if (recret == 0) {
        return false;
    }
    if (strcmp(DELETE_BUFFER, "SUCCEEDED_DELETED") == 0) {
        return true;
    }
    else {
        return false;
    }
}

// if false-logoff_deactivate_account_button_clicked then popup and recursive
