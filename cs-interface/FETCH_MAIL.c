//
// Created by guangtao on 2020/9/13.
//
#include "FETCH_MAIL.h"

#define TYPE_FOR_TEMPORARY_FIRST_HANDSHAKE cJSON*
#define TYPE_FOR_TEMPORARY_SECOND_HANDSHAKE char*


void MAIN_PAGE_SWITCHER() {

}

/*
 *
 */

int CHAR_TO_INT(char * num_target) {
    int ans = 0;
    for (int i = 0; i < strlen(num_target); i++) {
        ans *= 10;
        ans += num_target[i];
    }
    return ans;
}

char * INT_TO_CHAR(int num_target) {
    int len = 5;
    char ans[len];
    memset(ans, '\0', sizeof(ans));

    return ans;
}

char * Fetch_email_PACKAGE_TO_TITLE_LIST(cJSON * package) {
    cJSON * NUM_GETTER = cJSON_GetObjectItem(package, "number");
    cJSON * TITLES = cJSON_GetObjectItem(package, "content");
    char * NUM_TARGET = cJSON_Print(NUM_GETTER);
    int RECVNUMBER = CHAR_TO_INT(NUM_TARGET);
    char title_list[RECVNUMBER + 1];// = {'\0'};
    memset(title_list, '\0', sizeof(title_list));
    cJSON * tmp;
    for (int i = 0; i < RECVNUMBER; i++) {
        tmp = cJSON_GetObjectItem(TITLES, INT_TO_CHAR(i));

    }

}

TYPE_FOR_TEMPORARY_FIRST_HANDSHAKE Fetch_email_first_handshake(cJSON * package) {
    /*
     * THE JSON DOC HERE SHALL BE A PIECE WITH BOTH "USERNAME" AND "TYPE_OF_MAILBOXES"
     */
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    /*
     * SEND 20 LATEST EMAILS FROM THE MAILBOX
     */
    int RECVRET;
    char RECV_BUFFER_cJSON_PACKAGE[20 * MAIL_TITLE_LENGTH_MAXIME] = {'\0'};
    RECVRET = recv(sockfd, RECV_BUFFER_cJSON_PACKAGE, strlen(RECV_BUFFER_cJSON_PACKAGE), 0);
    if (RECVRET == 0) {
        printf("CAN'T RECEIVE EMAIL'S BODY\n");
        close(sockfd);
        exit(-1);
    }
    if (RECVRET > 0) {
        printf("RECEIVE EMAIL'S BODY SUCCESSFULLY\n");
    }
    /*
     * PACK THIS CHAR LINE INTO A cJSON_PACKAGE
     * /////// HERE FOR THE CONVERGING CODE
     */


    /// A LIST OF TITLES

    cJSON * return_package = cJSON_CreateObject();

    return return_package;
}

TYPE_FOR_TEMPORARY_SECOND_HANDSHAKE Fetch_email_second_handshake(char * target_title) {
    /*
     * SEND THE TARGET_TITLE TO THE SERVER AND TRY TO GET THE CORRECT BODY
     */
    send(sockfd, target_title, strlen(target_title), 0);
    /*
     * NOW RECEIVE THE BODY
     */
    int RECVRET;
    char RECV_BUFFER_EMAIL_BODY[1000] = {'\0'};
    RECVRET = recv(sockfd, RECV_BUFFER_EMAIL_BODY, strlen(RECV_BUFFER_EMAIL_BODY), 0);
    if (RECVRET == 0) {
        printf("CAN'T RECEIVE EMAIL'S BODY\n");
        close(sockfd);
        exit(-1);
    }
    if (RECVRET > 0) {
        printf("RECEIVE EMAIL'S BODY SUCCESSFULLY\n");
    }
    return RECV_BUFFER_EMAIL_BODY;
}

bool SignIN(cJSON * package) {
    /*
     * send the package to the server
     */
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);

    int RECVRET;
    char SIGNAL_CHECKING_SIGNING[20] = {'\0'};
    RECVRET = recv(sockfd, SIGNAL_CHECKING_SIGNING, strlen(SIGNAL_CHECKING_SIGNING), 0);
    if (RECVRET == 0) {
        printf("CAN RECEIVE NOTHING (SIGN_IN)\n");
        close(sockfd);
        exit(-1);
    }

    /*
     * IF IT IS TRUE THEN IT WILL SWITCH TO THE MAINPAGE
     */
    if (strcmp(SIGNAL_CHECKING_SIGNING, "SIGN_IN_SUCCEEDED.\n")) {
        MAIN_PAGE_SWITCHER();
        return true;
    }
    return false;
}

// package has been formatted
bool SignUp(cJSON * package) {
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    int RECVRET;
    char SIGNAL_CHECKING_SIGNING[20] = {'\0'};
    RECVRET = recv(sockfd, SIGNAL_CHECKING_SIGNING, strlen(SIGNAL_CHECKING_SIGNING), 0);
    if (RECVRET == 0) {
        printf("CAN RECEIVE NOTHING (SIGN_UP)\n");
        close(sockfd);
        exit(-1);
    }

    /*
     * IF IT IS TRUE THEN IT WILL SWITCH TO THE MAINPAGE
     */
    if (strcmp(SIGNAL_CHECKING_SIGNING, "SIGN_UP_SUCCEEDED.\n")) {
        MAIN_PAGE_SWITCHER(); //
        return true;
    }
    return false;
}

bool flag_transmit(char * username) {

    send(sockfd, username, strlen(username), 0);

    int RECVRET;
    char SIGNAL_CHECKING_SIGNING[20] = {'\0'};
    RECVRET = recv(sockfd, SIGNAL_CHECKING_SIGNING, strlen(SIGNAL_CHECKING_SIGNING), 0);
    if (RECVRET == 0) {
        printf("CAN RECEIVE NOTHING (REGISTER)\n");
        close(sockfd);
        exit(-1);
    }
    if (strcmp(SIGNAL_CHECKING_SIGNING, "REGISTER_SUCCEEDED.\n")) {
        return true;
    }
    return false;
}

void SAVE_REGISTER_INFORMATION(struct cJSON * NEW_CLIENT) {
    send(sockfd, cJSON_PrintUnformatted(NEW_CLIENT), strlen(cJSON_PrintUnformatted(NEW_CLIENT)), 0);

    int RECVRET;
    char SIGNAL_CHECKING_SIGNING[20] = {'\0'};
    RECVRET = recv(sockfd, SIGNAL_CHECKING_SIGNING, strlen(SIGNAL_CHECKING_SIGNING), 0);
    if (RECVRET == 0) {
        printf("CAN RECEIVE NOTHING (REGISTER-SAVE)\n");
        close(sockfd);
        exit(-1);
    }
    if (strcmp(SIGNAL_CHECKING_SIGNING, "REGISTER_SAVE_SUCCEEDED.\n")) {
        // ZHUJIEMIAN
    }
        //
}

cJSON * REGISTER_INFO_PACKAGE(REgister client) {
    cJSON * OBJ = cJSON_CreateObject();
    //OBJ = cJSON_PACKAGE_MAKE_REGISTER(client.username, client.password, client.security_question, client.answer);
            ///
}
