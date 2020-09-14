//
// Created by guangtao on 2020/9/14.
//

#include <cJSON.h>
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

/*
 * datastructure :
 * {    command : "get_recover_question"
 *      {   account_name : "str"; }
 * }
 *  */

/*
 * ONCE THE BUTTON IS CLICKED, JUST SEND THE CHAR LINE TO HERE
 * AND USE THE FUNCTION TO GET ERROR OR THE QUESTION
 * AND SHOW IT TO THE UI-LAYER
 */

char ERROR[] = {"Get recover name failed!\n"};
char * GET_RECOVER_NAME(char * account_name) {
    cJSON * package = PRE_STRUCTURE("get_recover_question");
    cJSON * CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "account_name", cJSON_CreateString(account_name));

    char GRN_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
    if (recret == 0) {
        return ERROR;
    }
    if (strcmp(GRN_BUFFER, "SUCCEEDED_GET_QU") == 0) {
        return GRN_BUFFER;
    }
    else {
        return ERROR;
    }
}

