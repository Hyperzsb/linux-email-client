#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>
#include <cJSON.h>
#include <string.h>
#include "define.h"

// int main(int argc, char *argv[]) {
/*
cJSON * test_package = cJSON_CreateObject();
struct account test_client;
test_client = CreateAccount();
/
test_package = cJSON_PACKAGE_MAKE_REGISTER(test_client.usrname,
                                           test_client.passwd,
                                           test_client.nickname,
                                           test_client.description,
                                           test_client.securityQuestion,
                                           test_client.securityQuAnswer);

test_package = cJSON_PACKAGE_MAKE_DELETE(test_client.usrname);
printf("%s\n", cJSON_Print(test_package));
*/
// BUTTON_CLICKED SHALL BE A FUNCTION FOR CONNECTING THE SERVER
// IF IT DOES NOT WORK, THE LOOPS WILL KEEP GOING BACK TO WHERE THE POINT IS;
/*
connection_point:
if (BUTTON_CLICKED() == 1) {
    if (CONNECTION() == false) {
        goto connection_point;
    }
} else {
    goto connection_point;
}
 */////////////////////
// IF CONNECTION IS DONE, SWITCH TO THE INIT PAGE
//////SWITCHER_TO_LOGIN_AND_REGISTER_PAGE();

//UPPER PART IS FOR CONNECTION AND SWITCH TO LOGIN PAGE
//-----------------------------------------------------------------------//
//子线程读
/////pthread_create(&th, NULL, thread_control, NULL);
///// int times = 100;
//主线程写
/////while (true) {////
/*
scanf("%s", sendbuf);
send(sockfd, sendbuf, strlen(sendbuf), 0);
memset(sendbuf, 0, sizeof(sendbuf));
*/
///    if (times--) break;/////
/*
if (CONNECTION() == false) {
    printf("CONNECTION FAILED.\n");
}

cJSON *test = cJSON_CreateObject();
test = PRE_STRUCTURE("fetch_mail");
cJSON *CONTENT = cJSON_CreateObject();
cJSON_AddItemToObject(test, "content", CONTENT);

send(sockfd, cJSON_PrintUnformatted(test), strlen(cJSON_PrintUnformatted(test)), 0);
int REC = 0, REC_ORIGIN = 0;
// char rec_test[5] = {"\0"};
char rec_origin[100] = {'\0'};
REC_ORIGIN = recv(sockfd, rec_origin, sizeof(rec_origin), 0);

if (REC_ORIGIN > 0) {
    printf("%s\n", rec_origin);
} else {
    printf("receive nothing\n");
}
memset(rec_origin, '\0', sizeof(rec_origin));
REC = recv(sockfd, rec_origin, sizeof(rec_origin), 0);
if (REC > 0) {
    printf("%s\n", rec_origin);
} else {
    printf("receive nothing\n");
}
*/

//return 0;
// }



/*
int main(int argc, char* argv[]){

    if (CONNECTION()) {
        printf("SUCCEEDED CONNECTED\n");
    }
    else {
        printf("failed\n");
    }

    char acn[] = {"new_account_the_sender"};
    char emn[] = {"new_account_the_sender@test.com"};
    char pass[] = {"testpasfrresword"};
    char nps[] = {"newpassrgrgword"};
    char recovery_question[] = {"Is this a test question?"};
    char recovery_question_answer[] = {"Yes, it is!"};

    char rcn[] = {"new_account_the_receiver"};
    char recipient[] = {"new_account_the_receiver@qq.com"};
    char pass_r[] = {"xxxxxxxxxx"};

    char description[] = {"sender_description"};
    char des_r[] = {"receiver_description"};

    char title[] = {"THE TEST_EMAIL from test"};
    char body[] = {"THE TEST_BODY:\n\tHELLO: I M THE TESTER"};
    char alias[] = {"nickname_contactor"};
    cJSON *PACKAGE_FOR_SENDING = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FOR_SENDING, "recipient", cJSON_CreateString(recipient));
    cJSON_AddItemToObject(PACKAGE_FOR_SENDING, "title", cJSON_CreateString(title));
    cJSON_AddItemToObject(PACKAGE_FOR_SENDING, "body", cJSON_CreateString(body));

    cJSON *PACKAGE_FOR_SET_CONTENT = cJSON_CreateObject();
    cJSON *PACKAGE_FOR_SET_CONTACT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "content", PACKAGE_FOR_SET_CONTENT);
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "command", cJSON_CreateString("set_contact"));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTENT, "remark", cJSON_CreateString(alias));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTENT, "friend", cJSON_CreateString(recipient));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTENT, "username", cJSON_CreateString(emn));

    switch(flag_transmit(emn, acn, pass, description, recovery_question, recovery_question_answer)) {
        case 0:
            printf("ERROR\n");
            break;
        case 1:
            printf("SIGN_UP_SUCCEEDED\n");
            break;
        case -1:
            printf("UNEXPECTED_ERROR\n");
            break;
        case 2:
            printf("SIGN_UP_ACCOUNT_CONFLICT\n");
            break;
        default: ;
    }

    switch(flag_transmit(recipient, rcn, pass_r, des_r, recovery_question, recovery_question_answer)) {
        case 0:
            printf("ERROR\n");
            break;
        case 1:
            printf("SIGN_UP_SUCCEEDED\n");
            break;
        case -1:
            printf("UNEXPECTED_ERROR\n");
            break;
        case 2:
            printf("SIGN_UP_ACCOUNT_CONFLICT\n");
            break;
        default: ;
    }

// login
    switch(SIGN_WHOLE_PROCESS(emn, pass)) {
        case 0:
            printf("UNEXPECTED_ERROR\n");
            break;
        case 1:
            printf("EXPECTED_SUCCESS\n");
            break;
        case 2:
            printf("ACCOUNT_INVALID\n");
            break;
        case 3:
            printf("PASSWORD_INVALID\n");
            break;
        default:
            printf("ERROR\n");
    }

    strcat(LOGGER, emn);

    gtk_init(&argc, &argv);

//	create main_table
    table_main=init_main_table();

//	create window
    window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
    set_window(window);
    state=0;

    gtk_main();
}
 */