//
// Created by guangtao on 2020/9/13.
//

#ifndef CLIENT_NEW_CJSON_PACKAGES_H
#define CLIENT_NEW_CJSON_PACKAGES_H
#include "PRE_CONDITIONS.h"
#include "info-acc.h"
#include "regex.h"

extern cJSON * PRE_STRUCTURE(char *command);
extern cJSON * cJSON_PACKAGE_MAKE_DELETE(char *usr);
extern cJSON * cJSON_PACKAGE_MAKE_DRAFT_BOX(char *draft);
extern cJSON * cJSON_PACKAGE_MAKE_LOGIN(char *usr, char *pass);
extern cJSON * cJSON_PACKAGE_MAKE_RECEIVE_MAIL(char *recipient);
extern cJSON * cJSON_PACKAGE_MAKE_FRIEND(char *usr, char *friend);
extern cJSON * cJSON_PACKAGE_MAKE_RECOVERY(char *n_pass, char *rec_q, char *rec_a);
extern cJSON * cJSON_PACKAGE_MAKE_SEND_MAIL(char *sender, char *recipient, char *title, char *body);
extern cJSON * cJSON_PACKAGE_MAKE_REGISTER(char *usr, char *pass, char *nick, char *description,
                                        char *rec_q, char *rec_a);

#endif //CLIENT_NEW_CJSON_PACKAGES_H
