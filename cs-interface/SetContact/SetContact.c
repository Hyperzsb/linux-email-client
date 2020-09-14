//
// Created by guangtao on 2020/9/14.
//

#include "SetContact.h"
#include <z3.h>
#include <string.h>
#include <sys/socket.h>

int sockfd = -1;
int sendret = 0;
int recret = 0;

bool SET_CONTACT_WHOLE_PROCESS(cJSON * package) {
    char SIGNAL_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        return false;
    }
    if (strcmp(SIGNAL_BUFFER, "SUCCEEDED SET CONTACT") == 0) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return true;
    }
    else {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return false;
    }
}

/*
 * API for press the button to set a new contact
 * (it might need a refresh)
 */
void BUTTON_CLICKED_TO_SET_CONTACT(struct cJSON * package) {
    if (SET_CONTACT_WHOLE_PROCESS(package)) {

    }
    else {

    }
}