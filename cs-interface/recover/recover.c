//
// Created by guangtao on 2020/9/14.
//

#include <cJSON.h>
#include <sys/socket.h>
#include <string.h>
#include <stdio.h>
#include <z3.h>
//  const char *account_name const char *answer, const char *passwd
// password is new
// answer is the origin answer
//


cJSON *PRE_STRUCTURE(char *command) {
    cJSON *CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(CLIENT, "command", cJSON_CreateString(command));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}

char ERROR[] = {"Get recover name failed!\n"};

bool GET_RECOVER_QUESTION(char *account_name, char *security_question, char *ans) {
    cJSON *package = PRE_STRUCTURE("get_recover_question");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "account_name", cJSON_CreateString(account_name));

    char GRN_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
    if (recret == 0) {
        memset(ans, '\0', sizeof(ans));
        strcat(ans, ERROR);
        return false;
    }
    if (strcmp(GRN_BUFFER, "SUCCEEDED_GET_QU") == 0) {
        /*
         * IF CONNECTED AND FOUND THE USER
         * RETURN THE USER'S SEQ-QUESTION AND ITS ANSWER
         * IF NOT
         * RETURN ERROR
         */
        memset(security_question, '\0', sizeof(security_question));
        strcat(security_question, GRN_BUFFER);
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
        memset(ans, '\0', sizeof(ans));
        strcat(ans, GRN_BUFFER);
        return true;
    } else {
        memset(ans, '\0', sizeof(ans));
        strcat(ans, ERROR);
        return false;
    }
}

bool PAGE_SWITCHER(cJSON *package) {
    char password[20] = {'\0'};
    char correction[20] = {'\0'};
    /*
     * pass and correction
     */
    //
    //
    //
    //
    if (strcmp(correction, password) == 0) {
        char RECOVER_SIGNAL_BUFFER[100] = {'\0'};
        cJSON_AddItemToObject(package, "password", cJSON_CreateString(password));
        send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
        recret = recv(sockfd, RECOVER_SIGNAL_BUFFER, sizeof(RECOVER_SIGNAL_BUFFER), 0);
        if (recret == 0) {
            return false;
        }
        if (strcmp(RECOVER_SIGNAL_BUFFER, "SUCCEEDED_RECOVER") != 0) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

void RECOVER_BUTTON_CLICKED(char *account_name) {
    char security_question[100] = {'\0'};
    char answer_to_the_question[100] = {'\0'};
    if (GET_RECOVER_QUESTION(account_name, security_question, answer_to_the_question)
        && strcmp(answer_to_the_question, ERROR) != 0) {
        /*
         * switch to the next page
         */
        cJSON *package = PRE_STRUCTURE("recover");
        cJSON *CONTENT = cJSON_CreateObject();
        cJSON_AddItemToObject(package, "content", CONTENT);
        cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(account_name));
        // cJSON_AddItemToObject(CONTENT, "recover_question", cJSON_CreateString(security_question));
        cJSON_AddItemToObject(CONTENT, "recover_answer", cJSON_CreateString(answer_to_the_question));
        if (PAGE_SWITCHER(package)) {
            /*
             * // popup_page
             * // popup_page
             */
        }
    } else {
        printf("ANS_AND_QUESTION_ERROR!\n");
    }
}