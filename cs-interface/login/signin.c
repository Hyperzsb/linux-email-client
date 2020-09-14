//
// Created by guangtao on 2020/9/14.
//
#include <stdio.h>
#include <cJSON.h>
#include <sys/socket.h>
#include <string.h>

cJSON * PRE_STRUCTURE(char *command) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(CLIENT, "command", cJSON_CreateString(command));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}

cJSON * SIGNIN_FROM_CLIENT_TO_SERVER(char * account_name, char * password) {
    cJSON * package = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    package = PRE_STRUCTURE("login");
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(account_name));
    cJSON_AddItemToObject(CONTENT, "password", cJSON_CreateString(password));
    return package;
}

bool SIGNIN_FROM_SERVER_TO_CLIENT(char * SIGNAL) {
    if (strcmp(SIGNAL, "SUCCEEDED_SIGNIN")) {
        return true;
    }
    return false;
}

int sockfd = -1;
int sendret = 0;
int recret = 0;
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
