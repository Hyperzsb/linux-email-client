//
// Created by guangtao on 2020/9/14.
//

#include <regex.h>
#include <z3.h>
#include <string.h>
#include <cJSON.h>
#include <sys/socket.h>
#include "register.h"

cJSON *PRE_STRUCTURE(char *command) {
    cJSON *CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(CLIENT, "command", cJSON_CreateString(command));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}

bool email_addr_format(char *email_account) {
    int ret;
    //匹配邮箱的正则表达式
    char *pattern = "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*";

    regex_t preg;
    size_t nmatch = 1;
    regmatch_t pmatch[1];

    ret = regcomp(&preg, pattern, REG_EXTENDED);  //编译正则表达式
    ret = regexec(&preg, email_account, nmatch, pmatch, REG_NOTEOL);  //匹配字符串

    if (ret != REG_NOERROR) {
        printf("The email_account is illegal\n");
        return 0;
    }

    /*匹配成功，打印匹配到的内容*/
    for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) putchar(email_account[i]);
    printf("\r\n");
    regfree(&preg);  //清空编译好的正则表达式
    return 1;
}

/*
 * UI-LAYER handle the "already used name issue" with this function
 * so in general it 's also a function which will lead to the success or failure
 * of the SIGNING_UP PROCESS
 */
bool flag_transmit(char *username, char *nickname, char *password, char *seq_question, char *ans) {
    /*
     * IT THE EMAIL_ADDR IS ILLEGAL
     */
    if (email_addr_format(username)) {
        return false;
    }
    /*
     * PARSE host and domain
     */
    int email_addr_length = strlen(username);
    char host[15] = {'\0'}, domain[15] = {'\0'};
    int i = 0;
    // GET host
    for (; username[i] != '@'; i++) {
        host[i] = username[i];
    }
    i++;
    // GET domain
    for (; i < email_addr_length; i++) {
        domain[i] = username[i];
    }

    cJSON *CONTENT = cJSON_CreateObject();
    cJSON *package = PRE_STRUCTURE("register");
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "host", cJSON_CreateString(host));
    cJSON_AddItemToObject(CONTENT, "domain", cJSON_CreateString(domain));
    cJSON_AddItemToObject(CONTENT, "nickname", cJSON_CreateString(nickname));
    cJSON_AddItemToObject(CONTENT, "password", cJSON_CreateString(password));
    cJSON_AddItemToObject(CONTENT, "description", cJSON_CreateString(""));
    cJSON_AddItemToObject(CONTENT, "recovery_question", cJSON_CreateString(seq_question));
    cJSON_AddItemToObject(CONTENT, "recovery_answer", cJSON_CreateString(ans));

    //// HERE WE NEED ONE MORE FUNCTION
    /*
     *  change the personal description function
     */
    char REGISTER_SIGNAL_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, REGISTER_SIGNAL_BUFFER, sizeof(REGISTER_SIGNAL_BUFFER), 0);
    if (recret == 0) {
        return false;
    }
    if (strcmp(REGISTER_SIGNAL_BUFFER, "SUCCEEDED_REGISTED") == 0) {
        memset(REGISTER_SIGNAL_BUFFER, '\0', sizeof(REGISTER_SIGNAL_BUFFER));
        return true;
    } else {
        memset(REGISTER_SIGNAL_BUFFER, '\0', sizeof(REGISTER_SIGNAL_BUFFER));
        return false;
    }
}