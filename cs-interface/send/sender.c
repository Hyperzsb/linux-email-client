//
// Created by guangtao on 2020/9/14.
//
#include <cJSON.h>
#include <string.h>
#include <stdio.h>

#define bool int
#define true 1
#define false 0

cJSON *SENDER_CLIENT_TO_SERVER(char *account_name, cJSON *PACKAGE_FROM_UI) {
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
 * There is ONE process between S-C,
 * when the S try to send a signal to C
 * if succeeded, goto the SENDER_CLIENT_TO_UI function
 */

bool SENDER_CLIENT_TO_UI(char *SIGNAL_FROM_SERVER) {
    if (strcmp(SIGNAL_FROM_SERVER, "SendMail_Succeed")) {
        // if (POPUP_FOR_GROUP_SENDING) {
        //
        //  }
        return true;
    }
    return false;
}

void SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(cJSON *PACKAGE_FROM_UI_t) {

    char account_name[] = {"test_account"};
    cJSON * PACKAGE_FROM_CLIENT = cJSON_CreateObject();
    PACKAGE_FROM_CLIENT = SENDER_CLIENT_TO_SERVER(account_name, PACKAGE_FROM_UI_t);
    /*
     * sending
     */
    char SIGNAL[] = {"SendMail_Succeed"};
    if (SENDER_CLIENT_TO_UI(SIGNAL)) {
        printf("send succeeded\n");
    } else {
        printf("failed\n");
    }
}
