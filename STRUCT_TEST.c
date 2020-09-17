//
// Created by guangtao on 2020/9/15.
//

#include "define.h"
/*
int main() {
    cJSON * PACKAGE = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE, "content", CONTENT);
    cJSON_AddItemToObject(PACKAGE, "number", cJSON_CreateString("3"));
    char title1[] = {"The title of the first email"};
    char title2[] = {"The title of the second email"};
    char title3[] = {"The title of the third email"};
    char body1[] = {"The first body"};
    char body2[] = {"The second body"};
    char body3[] = {"The third body"};
    char cont1[] = {"The first cont"};
    char cont2[] = {"The second cont"};
    char cont3[] = {"The third cont"};
    char time1[] = {"The first time"};
    char time2[] = {"The second time"};
    char time3[] = {"The third time"};
    cJSON_AddItemToObject(CONTENT, "1", cJSON_CreateString(title1));
    cJSON_AddItemToObject(CONTENT, "2", cJSON_CreateString(title2));
    cJSON_AddItemToObject(CONTENT, "3", cJSON_CreateString(title3));
    cJSON_AddItemToObject(CONTENT, title1, cJSON_CreateString(body1));
    cJSON_AddItemToObject(CONTENT, title2, cJSON_CreateString(body2));
    cJSON_AddItemToObject(CONTENT, title3, cJSON_CreateString(body3));
    cJSON_AddItemToObject(CONTENT, "cont1", cJSON_CreateString(cont1));
    cJSON_AddItemToObject(CONTENT, "cont2", cJSON_CreateString(cont2));
    cJSON_AddItemToObject(CONTENT, "cont3", cJSON_CreateString(cont3));
    cJSON_AddItemToObject(CONTENT, "time1", cJSON_CreateString(time1));
    cJSON_AddItemToObject(CONTENT, "time2", cJSON_CreateString(time2));
    cJSON_AddItemToObject(CONTENT, "time3", cJSON_CreateString(time3));
    printf("%s\n", cJSON_Print(PACKAGE));

    // struct EMAIL_CONTENT *A = NULL;
    FETCH_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(PACKAGE);
    printf("%s\n", cJSON_Print(PACKAGE));
    printf("EMAIL_NUM : %d\n", EMAIL_NUM);
    for (int i = 0; i < EMAIL_NUM; i++) {
        printf("The No. %d email's title is : %s\n", i + 1, EMAIL_FROM_PACKAGE[i].title);
        printf("The No. %d email's body is : %s\n", i + 1, EMAIL_FROM_PACKAGE[i].body);
        printf("The No. %d email's contact is : %s\n", i + 1, EMAIL_FROM_PACKAGE[i].contactor);
        printf("The No. %d email's time is : %s\n", i + 1, EMAIL_FROM_PACKAGE[i].time);
    }

    cJSON * NEW_CONTENT = cJSON_GetObjectItem(PACKAGE, "content");
    cJSON_AddItemToObject(NEW_CONTENT, "XXX", cJSON_CreateString("LALAAL"));
    printf("%s\n", cJSON_Print(PACKAGE));

    return 0;
}
*/