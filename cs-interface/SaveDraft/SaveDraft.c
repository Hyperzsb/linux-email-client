//
// Created by guangtao on 2020/9/14.
//

#include "SaveDraft.h"
#include <cJSON.h>
#include <z3.h>
#include <string.h>
#include <sys/socket.h>


cJSON *SAVE_DRAFT_CLIENT_TO_SERVER(char *account_name, cJSON *PACKAGE_FROM_UI) {
    /*
     * PACKAGE_FROM_UI: {   recipient: "str"
     *                      title: "str"
     *                      body: "str" }
     */
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "account_name", cJSON_CreateString(account_name));
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "sender", cJSON_CreateString(account_name));
    /*
     * Formatted the package and send it to SERVER
     * the key is the defined data structure
     */
    cJSON *PACKAGE_FROM_CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FROM_CLIENT, "command", cJSON_CreateString("SendMail"));
    cJSON_AddItemToObject(PACKAGE_FROM_CLIENT, "content", PACKAGE_FROM_UI);
    return PACKAGE_FROM_CLIENT;
}

/*
 * Since the MAINPAGE can't receive who is now logging in
 * So save the account (sender) as a global para
 * deliver this into the function
 */
bool AVE_DRAFT_BUTTON_CLICKED(char *username, char *title, char *body) {  // API for the UI

    /*
     * Here is the space for the cJSON packing process
     * (UI) will pack it
     */
    //// global parameter -- account name
    char account_name[] = {""};
    cJSON *result = cJSON_CreateObject();
    cJSON *package = cJSON_CreateObject();
    package = SAVE_DRAFT_CLIENT_TO_SERVER(account_name, result);

    char SAVE_DRAFT_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, SAVE_DRAFT_BUFFER, sizeof(SAVE_DRAFT_BUFFER), 0);
    if (recret == 0) {
        return false;
    }

    if (strcmp(SAVE_DRAFT_BUFFER, "SUCCEEDED_SAVED") == 0) {
        memset(SAVE_DRAFT_BUFFER, '\0', sizeof(SAVE_DRAFT_BUFFER));
        /*
         *
         */
        return true;
    } else {
        memset(SAVE_DRAFT_BUFFER, '\0', sizeof(SAVE_DRAFT_BUFFER));
        /*
         *
         */
        return false;
    }
}

