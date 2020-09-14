//
// Created by guangtao on 2020/9/13.
//

#include "cJSON_PACKAGES.h"

/*
 * {
 *      command: ;
 *      content:{
 *
 *      }
 * }
 */

/*
 * 张圃瑒  16:50:58
/*register

	char host[50]

	char domain[50]

	char password[50]

	char nickname[50]

	char description[200]

	char recovery_question[50]

	char recovery_answer[50]*/

/*login

char username[50]

char password[50]*/

/*send_mail

	char sander[50]

	char recipient[50]

	char title[100]

	char body[1000]

	*/

/*fetch_mail

char username[50]

char type


*/

cJSON * PRE_STRUCTURE(char *command) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(CLIENT, "command", cJSON_CreateString(command));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_DELETE(char *usr) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_DELETE);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(usr));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_DRAFT_BOX(char *draft) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_DRAFT);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "draft", cJSON_CreateString(draft));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_LOGIN(char *usr, char *pass) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_LOGIN);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(usr));
    cJSON_AddItemToObject(CONTENT, "password", cJSON_CreateString(pass));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_RECEIVE_MAIL(char *recipient) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_RECV_M);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "recipient", cJSON_CreateString(recipient));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_FRIEND(char *usr, char *friend) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_FRIEND);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(usr));
    cJSON_AddItemToObject(CONTENT, "friend", cJSON_CreateString(friend));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_RECOVERY(char *n_pass, char *rec_q, char *rec_a) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_RECOVER);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "new_password", cJSON_CreateString(n_pass));
    cJSON_AddItemToObject(CONTENT, "recovery_question", cJSON_CreateString(rec_q));
    cJSON_AddItemToObject(CONTENT, "recovery_answer", cJSON_CreateString(rec_a));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_SEND_MAIL(char *sender, char *recipient, char *title, char *body) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_SEND_M);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "sender", cJSON_CreateString(sender));
    cJSON_AddItemToObject(CONTENT, "recipient", cJSON_CreateString(recipient));
    cJSON_AddItemToObject(CONTENT, "title", cJSON_CreateString(title));
    cJSON_AddItemToObject(CONTENT, "body", cJSON_CreateString(body));
    return CLIENT;
}

cJSON * cJSON_PACKAGE_MAKE_REGISTER(char *usr, char *pass, char *nick, char *description,
                                        char *rec_q, char *rec_a) {
    cJSON * CLIENT = cJSON_CreateObject();
    cJSON * CONTENT = cJSON_CreateObject();
    CLIENT = PRE_STRUCTURE(COMMAND_REGISTER);
    cJSON_AddItemToObject(CLIENT, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(usr));
    cJSON_AddItemToObject(CONTENT, "password", cJSON_CreateString(pass));
    cJSON_AddItemToObject(CONTENT, "nickname", cJSON_CreateString(nick));
    cJSON_AddItemToObject(CONTENT, "description", cJSON_CreateString(description));
    cJSON_AddItemToObject(CONTENT, "recovery_question", cJSON_CreateString(rec_q));
    cJSON_AddItemToObject(CONTENT, "recovery_answer", cJSON_CreateString(rec_a));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}

bool email_addr_format(char * email_account) {
    int ret;
    //匹配邮箱的正则表达式
    char *pattern = "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*";

    regex_t preg;
    size_t nmatch = 1;
    regmatch_t pmatch[1];

    ret = regcomp(&preg, pattern, REG_EXTENDED);  //编译正则表达式
    ret = regexec(&preg, email_account, nmatch, pmatch, REG_NOTEOL);  //匹配字符串

    if(ret != REG_NOERROR){
        printf("The email_account is illegal\n");
        return 0;
    }

    /*匹配成功，打印匹配到的内容*/
    for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) putchar(email_account[i]);
    printf("\r\n");
    regfree(&preg);  //清空编译好的正则表达式
    return 1;
}


