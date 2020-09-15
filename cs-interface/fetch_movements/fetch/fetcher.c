//
// Created by guangtao on 2020/9/14.
//
#include <stdio.h>
#include <cJSON.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_FOR_TEMPORARY_FIRST_HANDSHAKE cJSON*
#define TYPE_FOR_TEMPORARY_SECOND_HANDSHAKE char*

struct Email_tab {
    char title[100];
    char body[1000];
};

int CHAR_TO_INT(char *num_target) {
    int ans = 0;
    for (int i = 0; i < strlen(num_target); i++) {
        ans *= 10;
        ans += num_target[i];
    }
    return ans;
}

char *INT_TO_CHAR(int num_target) {
    char num[5] = {'\0'};
    return num;
}


// FROM SERVER BACK A JSON TO CLIENT
struct Email_tab *Fetch_email_PACKAGE_TO_TITLE_LIST(cJSON *package_title_order, cJSON *package_title_body) {
    /*
     * FROM THE SERVER, IT WILL SEND ME A PACKAGE WITH SUCH DATA_STRUCTURE:
     *      ROOT : {
     *          number: "int";
     *          TITLES: {
     *              "1" : "title1";
     *              "2" : "title2";
     *              "3" : ...
     *          }
     *      }
     *      ROOT : {
     *          number: "int";
     *          TITLES: {
     *              "title1-str" : "body-str";
     *              "title2-str" : "body-str";
     *              "title3-str" : ...
     *          }
     *      }
     */
    // THE NUMBER OF THE TITLES
    cJSON *NUM_GETTER = cJSON_GetObjectItem(package_title_order, "number");
    // THE TITLE LIST (TITLE->BODY)
    cJSON *KEY_TITLES = cJSON_GetObjectItem(package_title_order, "content");
    // THE NUMBER LIST (NUMBER->BODY)
    cJSON *KEY_NUMBERS = cJSON_GetObjectItem(package_title_body, "content");

    cJSON *body_getter = cJSON_CreateObject();
    cJSON *title_getter = cJSON_CreateObject();

    // THE "TITLES" IN HERE SHALL BE A { }
    char NUM_TARGET[5] = {'\0'};
    strcat(NUM_TARGET, cJSON_Print(NUM_GETTER));
    int RECVNUMBER = CHAR_TO_INT(NUM_TARGET);
    // struct
    struct Email_tab EMAIL_FOR_FETCHING[RECVNUMBER + 2];

    for (int i = 1; i <= RECVNUMBER; i++) {
        // GET TITLE
        title_getter = cJSON_GetObjectItem(KEY_NUMBERS, INT_TO_CHAR(i));
        // save_position starts from 0 not 1
        strcat(EMAIL_FOR_FETCHING[i - 1].title, cJSON_Print(title_getter));
        // USE TITLE TO GET BODY
        body_getter = cJSON_GetObjectItem(KEY_TITLES, EMAIL_FOR_FETCHING[i - 1].title);
        strcat(EMAIL_FOR_FETCHING[i - 1].body, cJSON_Print(body_getter));
    }
    return EMAIL_FOR_FETCHING;
}
