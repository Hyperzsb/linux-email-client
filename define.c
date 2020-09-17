
// Created by guangtao on 2020/9/15.
//
#include "define.h"

void quyinhao(char *str) {
    int n = strlen(str);
    if (str[0] != '\"') {
        printf("yinhao error\n");
    }
    for (int i = 1; i < n; i++) {
        if (str[i] == '\"') {
            printf("yinhao success!\n");
            str[i - 1] = '\0';
            return;
        }
        str[i - 1] = str[i];
    }
}

cJSON *PRE_STRUCTURE(char *command) {
    cJSON *CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(CLIENT, "command", cJSON_CreateString(command));
    printf("%s\n", cJSON_Print(CLIENT));
    return CLIENT;
}
/*
 * DELETE_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

// PRE_CONDITION: CODE CORRECT
// if (SIGN_WHOLE_PROCESS(email_addr, password) == true) {
//        cJSON * package = PRE_STRUCTURE("delete");
//        cJSON * CONTENT = cJSON_CreateObject();
//        cJSON_AddItemToObject(package, "content", CONTENT);
//        cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(email_addr));
//        return package;
//    }

bool LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(char *email_addr) {
    cJSON *package = PRE_STRUCTURE("delete");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(email_addr));
    printf("%s\n", cJSON_Print(package));
    // return package;
    char DELETE_BUFFER[300] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, DELETE_BUFFER, sizeof(DELETE_BUFFER), 0);
    if (recret == 0) {
        memset(DELETE_BUFFER, '\0', sizeof(DELETE_BUFFER));
        return false;
    }
    if (strcmp(DELETE_BUFFER, "EXPECTED_SUCCESS") == 0) {
        memset(DELETE_BUFFER, '\0', sizeof(DELETE_BUFFER));
        return true;
    } else {
        memset(DELETE_BUFFER, '\0', sizeof(DELETE_BUFFER));
        return false;
    }
}

bool LOGOFF_TEST_FUNCTION(char *username) {
    if (LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(username)) {
        return true;
    } else {
        return false;
    }
}

/*
 * GET_RECOVER_QUESTION_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

/*
 * datastructure :
 * {    command : "get_recover_question"
 *      {   account_name : "str"; }
 * }
 *  */

/*
 * ONCE THE BUTTON IS CLICKED, JUST SEND THE CHAR LINE TO HERE
 * AND USE THE FUNCTION TO GET ERROR OR THE QUESTION
 * AND SHOW IT TO THE UI-LAYER
 */

char *GET_RECOVER_QUESTION_ORIGIN(char *account_name, char *security_question) {
    cJSON *package = PRE_STRUCTURE("get_recover_question");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "account_name", cJSON_CreateString(account_name));

    char GRN_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
    if (recret == 0) {
        return ERROR;
    }
    if (strcmp(GRN_BUFFER, "SUCCEEDED_GET_QU") == 0) {
        /*
         * IF CONNECTED AND FOUND THE USER
         * RETURN THE USER'S SEQ-QUESTION AND ITS ANSWER
         * IF NOT
         * RETURN ERROR
         */
        memset(security_question, '\0', sizeof(security_question));
        strcat(security_question, GRN_BUFFER);
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
        return GRN_BUFFER;
    } else {
        return ERROR;
    }
}

/*
 * LOGIN_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

cJSON *SIGNIN_FROM_CLIENT_TO_SERVER(char *account_name, char *password) {
    cJSON *package = cJSON_CreateObject();
    cJSON *CONTENT = cJSON_CreateObject();
    package = PRE_STRUCTURE("login");
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(account_name));
    cJSON_AddItemToObject(CONTENT, "password", cJSON_CreateString(password));
    return package;
}

int SIGNIN_FROM_SERVER_TO_CLIENT(char *SIGNAL) {
    if (strcmp(SIGNAL, "SIGN_IN_SUCCESS") == 0) {
        return 1;
    } else if (strcmp(SIGNAL, "SIGN_IN_INVALID_ACCOUNT") == 0) {
        return 2;
    } else if (strcmp(SIGNAL, "SIGN_IN_INVALID_PASSWD") == 0) {
        return 3;
    }
    return 0;
}


int SIGN_WHOLE_PROCESS(char *account_name, char *password) {
    char SIGNAL_BUFFER[20] = {'\0'};
    cJSON *DIRECT_PACKAGE = SIGNIN_FROM_CLIENT_TO_SERVER(account_name, password);
    send(sockfd, cJSON_PrintUnformatted(DIRECT_PACKAGE), strlen(cJSON_PrintUnformatted(DIRECT_PACKAGE)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        return 0;
    }
    if (SIGNIN_FROM_SERVER_TO_CLIENT(SIGNAL_BUFFER) == 1) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return 1;
    } else if (SIGNIN_FROM_SERVER_TO_CLIENT(SIGNAL_BUFFER) == 2) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return 2;
    } else if (SIGNIN_FROM_SERVER_TO_CLIENT(SIGNAL_BUFFER) == 3) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return 3;
    } else {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return 0;
    }
}

/*
 * RECOVER_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

bool GET_RECOVER_QUESTION(char *account_name, char *question) {
    cJSON *package = PRE_STRUCTURE("get_recovery_question");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(account_name));
    printf("%s\n", cJSON_Print(package));
    char GRN_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
    if (recret == 0) {
        printf("nothing received\n");
        return false;
    }
    if (strcmp(GRN_BUFFER, "ERROR!") == 0) {
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        return false;
    } else {
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        strcat(question, GRN_BUFFER);
        return true;
    }
}

int QUESTION_GET_BUTTON_CLICKED(char *account_name, char *ans, char *new_password) {
    cJSON *package = PRE_STRUCTURE("recovery");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(account_name));
    cJSON_AddItemToObject(CONTENT, "new_password", cJSON_CreateString(new_password));
    cJSON_AddItemToObject(CONTENT, "recovery_answer", cJSON_CreateString(ans));
    char GRN_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
    if (recret == 0) {
        printf("nothing received\n");
        return -1;
    }
    if (strcmp(GRN_BUFFER, "ERROR!") == 0) {
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        return 0;
    } else if (strcmp(GRN_BUFFER, "RECOVER_SUCCESS") == 0) {
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        return 1;
    } else {
        // INVALID_ANSWER
        memset(GRN_BUFFER, '\0', sizeof(GRN_BUFFER));
        return 2;
    }
}

bool PAGE_SWITCHER(cJSON *package) {
    char password[20] = {'\0'};
    char correction[20] = {'\0'};
    /*
     * pass and correction
     */
    //
    //
    //
    //
    if (strcmp(correction, password) == 0) {
        char RECOVER_SIGNAL_BUFFER[100] = {'\0'};
        cJSON_AddItemToObject(package, "password", cJSON_CreateString(password));
        send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
        recret = recv(sockfd, RECOVER_SIGNAL_BUFFER, sizeof(RECOVER_SIGNAL_BUFFER), 0);
        if (recret == 0) {
            return false;
        }
        if (strcmp(RECOVER_SIGNAL_BUFFER, "EXPECTED_SUCCESS") != 0) {
            return false;
        }
        return true;
    } else {
        return false;
    }
}

void PAGE_INPUT_GETTER(char *name, char *ans, char *passwd) {
    switch (QUESTION_GET_BUTTON_CLICKED(name, ans, passwd)) {
        case -1:
            // UNEXPECTED_ERROR;
            // POPUP WINDOW;
            printf("RECOVERY_UNEXPECTED_ERROR\n");
            break;
        case 0:
            // ERROR;
            // POPUP WINDOW;
            printf("RECOVERY_ERROR\n");
            break;
        case 1:
            // EXPECTED_SUCCEED
            // POPUP WINDOW;
            printf("RECOVERY_EXPECTED_SUCCEED\n");
            break;
        case 2:
            // INVALID ANS;
            // POPUP WINDOW;
            printf("RECOVERY_INVALID_ANS\n");
            break;
        default:
            // UNEXPECTED_ERROR;
            printf("__UNEXPECTED_ERROR\n");
            break;
    }
}

bool RECOVERY_BUTTON_CLICKED_(char *ans, char *passwd) {
    switch (QUESTION_GET_BUTTON_CLICKED(LOGGER, ans, passwd)) {
        case -1:
            // UNEXPECTED_ERROR;
            // POPUP WINDOW;
            printf("RECOVERY_UNEXPECTED_ERROR\n");
            return false;
        case 0:
            // ERROR;
            // POPUP WINDOW;
            printf("RECOVERY_ERROR\n");
            return false;
        case 1:
            // EXPECTED_SUCCEED
            // POPUP WINDOW;
            printf("RECOVERY_EXPECTED_SUCCEED\n");
            return true;
        case 2:
            // INVALID ANS;
            // POPUP WINDOW;
            printf("RECOVERY_INVALID_ANS\n");
            return false;
        default:
            // UNEXPECTED_ERROR;
            printf("__UNEXPECTED_ERROR\n");
            return false;
    }
}

void RECOVER_BUTTON_CLICKED(char *account_name) {
    char question[100] = {'\0'};
    if (GET_RECOVER_QUESTION(account_name, question)) {
        /*
         * SWITCH TO A NEW PAGE
         * THE PAGE WHICH HAS 3 LINE FOR INPUT
         */
        char ans[100] = {'\0'};
        char new_passwd[100] = {"\0"};
        PAGE_INPUT_GETTER(account_name, ans, new_passwd);
    }
}

/*
 * REGISTER_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

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
int flag_transmit(char *username, char *nickname, char *password, char *des, char *seq_question, char *ans) {
    /*
     * IT THE EMAIL_ADDR IS ILLEGAL
     */
    if (!email_addr_format(username)) {
        return false;
    }
    /*
     * PARSE host and domain
     */
    int email_addr_length = strlen(username);
    char host[100] = {'\0'}, domain[100] = {'\0'};
    int i = 0, j = 0;
    // GET host
    for (; username[i] != '@'; i++) {
        host[i] = username[i];
    }
    i++;
    // GET domain
    for (j = 0; i < email_addr_length; i++, j++) {
        domain[j] = username[i];
    }

    cJSON *CONTENT = cJSON_CreateObject();
    cJSON *package = PRE_STRUCTURE("register");
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "host", cJSON_CreateString(host));
    cJSON_AddItemToObject(CONTENT, "domain", cJSON_CreateString(domain));
    cJSON_AddItemToObject(CONTENT, "nickname", cJSON_CreateString(nickname));
    cJSON_AddItemToObject(CONTENT, "password", cJSON_CreateString(password));
    cJSON_AddItemToObject(CONTENT, "description", cJSON_CreateString(des));
    cJSON_AddItemToObject(CONTENT, "recovery_question", cJSON_CreateString(seq_question));
    cJSON_AddItemToObject(CONTENT, "recovery_answer", cJSON_CreateString(ans));
    printf("%s\n", cJSON_Print(package));
    //// HERE WE NEED ONE MORE FUNCTION
    /*
     *  change the personal description function
     */
    char REGISTER_SIGNAL_BUFFER[200] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, REGISTER_SIGNAL_BUFFER, sizeof(REGISTER_SIGNAL_BUFFER), 0);
    if (recret == 0) {
        memset(REGISTER_SIGNAL_BUFFER, '\0', sizeof(REGISTER_SIGNAL_BUFFER));
        return -1;
    }
    if (strcmp(REGISTER_SIGNAL_BUFFER, "SIGN_UP_SUCCESS") == 0) {
        memset(REGISTER_SIGNAL_BUFFER, '\0', sizeof(REGISTER_SIGNAL_BUFFER));
        return 1;
    } else if (strcmp(REGISTER_SIGNAL_BUFFER, "SIGN_UP_ACCOUNT_CONFLICT") == 0) {
        memset(REGISTER_SIGNAL_BUFFER, '\0', sizeof(REGISTER_SIGNAL_BUFFER));
        return 2;
    } else {
        memset(REGISTER_SIGNAL_BUFFER, '\0', sizeof(REGISTER_SIGNAL_BUFFER));
        return 0;
    }
}

/*
 * SAVE_DRAFT_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

cJSON *SAVE_DRAFT_CLIENT_TO_SERVER(char *recipient, cJSON *PACKAGE_FROM_UI) {
    /*
     * PACKAGE_FROM_UI: {   recipient: "str"
     *                      title: "str"
     *                      body: "str" }
     */
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "recipient", cJSON_CreateString(recipient));
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "sender", cJSON_CreateString(LOGGER));
    /*
     * Formatted the package and send it to SERVER
     * the key is the defined data structure
     */
    cJSON *PACKAGE_FROM_CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FROM_CLIENT, "command", cJSON_CreateString("save_draft"));
    cJSON_AddItemToObject(PACKAGE_FROM_CLIENT, "content", PACKAGE_FROM_UI);
    printf("%s\n", cJSON_Print(PACKAGE_FROM_CLIENT));
    return PACKAGE_FROM_CLIENT;
}

/*
 * Since the MAINPAGE can't receive who is now logging in
 * So save the account (sender) as a global para
 * deliver this into the function
 */
bool SAVE_DRAFT_BUTTON_CLICKED(char *recipient, char *title, char *body) {  // API for the UI

    /*
     * Here is the space for the cJSON packing process
     * (UI) will pack it
     */
    //// global parameter -- account name
    // char account_name[] = {""};
    cJSON *result = cJSON_CreateObject();
    cJSON_AddItemToObject(result, "title", cJSON_CreateString(title));
    cJSON_AddItemToObject(result, "body", cJSON_CreateString(body));
    cJSON *package = cJSON_CreateObject();
    package = SAVE_DRAFT_CLIENT_TO_SERVER(recipient, result);

    printf("%s\n", cJSON_Print(package));

    char SAVE_DRAFT_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, SAVE_DRAFT_BUFFER, sizeof(SAVE_DRAFT_BUFFER), 0);
    if (recret == 0) {
        return false;
    }

    if (strcmp(SAVE_DRAFT_BUFFER, "EXPECTED_SUCCESS") == 0) {
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


/*
 * SEND_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

cJSON *SENDER_CLIENT_TO_SERVER(char *username, cJSON *PACKAGE_FROM_UI) {
    /*
     * PACKAGE_FROM_UI: {   recipient: "str"
     *                      title: "str"
     *                      body: "str" }
     */
    // cJSON_AddItemToObject(PACKAGE_FROM_UI, "username", cJSON_CreateString(LOGGER));
    // cJSON_AddItemToObject(PACKAGE_FROM_UI, "sender", cJSON_CreateString(LOGGER));
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "username", cJSON_CreateString(username));
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "sender", cJSON_CreateString(username));
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "f_title", cJSON_CreateString("null"));
    cJSON_AddItemToObject(PACKAGE_FROM_UI, "file", cJSON_CreateString("null"));
    /*
     * Formatted the package and send it to SERVER
     * the key is the defined data structure
     */
    cJSON *PACKAGE_FROM_CLIENT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FROM_CLIENT, "command", cJSON_CreateString("send_mail"));
    cJSON_AddItemToObject(PACKAGE_FROM_CLIENT, "content", PACKAGE_FROM_UI);
    printf("%s\n", cJSON_Print(PACKAGE_FROM_CLIENT));
    return PACKAGE_FROM_CLIENT;
}

/*
 * There is ONE process between S-C,
 * when the S try to send a signal to C
 * if succeeded, goto the SENDER_CLIENT_TO_UI function
 */

bool SENDER_CLIENT_TO_UI(char *SIGNAL_FROM_SERVER) {
    if (strcmp(SIGNAL_FROM_SERVER, "EXPECTED_SUCCESS") == 0) {
        // if (POPUP_FOR_GROUP_SENDING) {
        //
        //  }
        return true;
    }
    return false;
}


void SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(char *username, cJSON *PACKAGE_FROM_UI_t) {
    // char account_name[] = {"test_account"};
    cJSON *PACKAGE_FROM_CLIENT = cJSON_CreateObject();
    PACKAGE_FROM_CLIENT = SENDER_CLIENT_TO_SERVER(username, PACKAGE_FROM_UI_t);
    // cJSON * CONTENT = cJSON_GetObjectItem(PACKAGE_FROM_CLIENT, "content");
    printf("%s\n", cJSON_Print(PACKAGE_FROM_CLIENT));
    /*
     * sending
     */
    char SENDER_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(PACKAGE_FROM_CLIENT),
         strlen(cJSON_PrintUnformatted(PACKAGE_FROM_CLIENT)), 0);
    recret = recv(sockfd, SENDER_BUFFER, sizeof(SENDER_BUFFER), 0);
    if (recret == 0) {
        printf("SENDING_ERROR\n");
    }
    // char SIGNAL[] = {"EXPECTED_SUCCESS"};
    if (strcmp(SENDER_BUFFER, "EXPECTED_SUCCESS") == 0) {
        memset(SENDER_BUFFER, '\0', sizeof(SENDER_BUFFER));
        printf("send succeeded\n");
    } else {
        memset(SENDER_BUFFER, '\0', sizeof(SENDER_BUFFER));
        printf("failed\n");
    }
}

/*
 * SET_CONTACT_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

bool ADD_CONTACT(char *remark, char *username) {
    cJSON *PACKAGE_FOR_SET_CONTENT = cJSON_CreateObject();
    cJSON *PACKAGE_FOR_SET_CONTACT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "content", PACKAGE_FOR_SET_CONTENT);
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "command", cJSON_CreateString("set_contact"));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTENT, "remark", cJSON_CreateString(remark));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTENT, "friend", cJSON_CreateString(username));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTENT, "username", cJSON_CreateString(LOGGER));
    printf("----%s\n", cJSON_Print(PACKAGE_FOR_SET_CONTACT));
    return SET_CONTACT_WHOLE_PROCESS(PACKAGE_FOR_SET_CONTACT);
}

bool SET_CONTACT_WHOLE_PROCESS(cJSON *package) {
    char SIGNAL_BUFFER[100] = {'\0'};
    printf("---------%s\n", cJSON_Print(package));
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        return false;
    }
    if (strcmp(SIGNAL_BUFFER, "EXPECTED_SUCCESS") == 0) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return true;
    } else {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return false;
    }
}

/*
 * API for press the button to set a new contact
 * (it might need a refresh)
 */
void BUTTON_CLICKED_TO_SET_CONTACT(cJSON *package) {
    if (SET_CONTACT_WHOLE_PROCESS(package)) {

    } else {

    }
}

/*
 * FETCH_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

/*
 * The data_structure of this package is:
 *      sending : {
 *          command : "fetch_mail";
 *          content : {
 *              username : "str;
 *              type : "inbox" / "outbox";
 *          }
 *      }
 */

/*
 * The data-structure of receiving package is :
 *      receiving : {
 *          num : "int"
 *          content : {
 *              1 : "title1_str";
 *              2 : "title2_str";
 *              ...
 *              num : "titlenum_str";
 *
 *              title1 : "body1_str";
 *              title2 : "body2_str";
 *              ...
 *              titlenum_str : "bodynum_str";
 *
 *              cont1 : "recipient/sender1_name";
 *              cont2 : "recipient/sender2_name";
 *              ...
 *              contnum : "recipient/sender3_name";
 *          }
 *      }
 */


int CHAR_TO_INT(char *num_target) {
    int ans = 0;
    int i = 0;
    for (i = 0; i < strlen(num_target); i++) {
        ans *= 10;
        // printf("--%d\n", ans);
        ans += (num_target[i] - '0');
        // printf("%d-----\n", ans);
    }
    return ans;
}

void int_to_string(int num, char *str) {
    int i = 0, j = 0;
    char temp[20];
    while (num) {
        temp[i++] = num % 10 + '0';  //将数字加字符0就变成相应字符
        num /= 10;               //此时的字符串为逆序
    }
    temp[i] = '\0';
    i = i - 1;
    while (i >= 0) str[j++] = temp[i--];   //将逆序的字符串转为正序
    str[j] = '\0';               //字符串结束标志
}

void MEMORY_SET_EMAIL_FETCH_BUFFER(struct EMAIL_CONTENT *EMAIL) {
    for (int i = 0; i < EMAIL_NUM; i++) {
        memset(EMAIL[i].title, '\0', sizeof(EMAIL[i].title));
        memset(EMAIL[i].body, '\0', sizeof(EMAIL[i].body));
        memset(EMAIL[i].contactor, '\0', sizeof(EMAIL[i].contactor));
        memset(EMAIL[i].time, '\0', sizeof(EMAIL[i].time));
        memset(EMAIL[i].file, '\0', sizeof(EMAIL[i].file));
        memset(EMAIL[i].f_title, '\0', sizeof(EMAIL[i].f_title));
    }
}

int FETCH_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(cJSON *package, char *type) {
    //printf("%s\n", cJSON_Print(package));
    char email_num[20] = {'\0'};
    printf("%s\n", cJSON_Print(cJSON_GetObjectItem(package, "number")));
    strcat(email_num, cJSON_Print(cJSON_GetObjectItem(package, "number")));
    quyinhao(email_num);
    EMAIL_NUM = CHAR_TO_INT(email_num);
    if (strcmp(type, "inbox") == 0) {
        MEMORY_SET_EMAIL_FETCH_BUFFER(EMAIL_FROM_PACKAGE);

        char CONTACT_ORDER[EMAIL_NUM + 20];
        char TIME_ORDER[EMAIL_NUM + 20];
        char FILE_ORDER[EMAIL_NUM + 20];
        cJSON *CONTENT = cJSON_GetObjectItem(package, "content");
        printf("%s\n", cJSON_Print(CONTENT));
        for (int i = 1; i <= EMAIL_NUM; i++) {
            char number_[20] = {'\0'};
            int_to_string(i, number_);
            printf("%s\n", number_);

            printf("%s\n", cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));

            strcat(EMAIL_FROM_PACKAGE[i - 1].title,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));
            quyinhao(EMAIL_FROM_PACKAGE[i - 1].title);
            printf("%s\n", EMAIL_FROM_PACKAGE[i - 1].title);

            strcat(EMAIL_FROM_PACKAGE[i - 1].body,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, EMAIL_FROM_PACKAGE[i - 1].title)));
            quyinhao(EMAIL_FROM_PACKAGE[i - 1].body);
            printf("%s\n", EMAIL_FROM_PACKAGE[i - 1].body);

            memset(CONTACT_ORDER, '\0', sizeof(CONTACT_ORDER));

            strcat(CONTACT_ORDER, "cont");
            strcat(CONTACT_ORDER, number_);

            strcat(EMAIL_FROM_PACKAGE[i - 1].contactor,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, CONTACT_ORDER)));
            quyinhao(EMAIL_FROM_PACKAGE[i - 1].contactor);
            printf("%s\n", EMAIL_FROM_PACKAGE[i - 1].contactor);

            memset(TIME_ORDER, '\0', sizeof(TIME_ORDER));
            strcat(TIME_ORDER, "time");
            strcat(TIME_ORDER, number_);

            strcat(EMAIL_FROM_PACKAGE[i - 1].time,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, TIME_ORDER)));
            quyinhao(EMAIL_FROM_PACKAGE[i - 1].time);
            printf("%s\n", EMAIL_FROM_PACKAGE[i - 1].time);


            memset(FILE_ORDER, '\0', sizeof(FILE_ORDER));
            strcat(FILE_ORDER, "file");
            strcat(FILE_ORDER, number_);

            strcat(EMAIL_FROM_PACKAGE[i - 1].f_title, "null");
            strcat(EMAIL_FROM_PACKAGE[i - 1].file, cJSON_Print(cJSON_GetObjectItem(CONTENT, FILE_ORDER)));
        }
    } else {
        MEMORY_SET_EMAIL_FETCH_BUFFER(SENT_FROM_PACKAGE);
        char CONTACT_ORDER[EMAIL_NUM + 20];
        char TIME_ORDER[EMAIL_NUM + 20];
        char FILE_ORDER[EMAIL_NUM + 20];
        cJSON *CONTENT = cJSON_GetObjectItem(package, "content");
        printf("%s\n", cJSON_Print(CONTENT));
        for (int i = 1; i <= EMAIL_NUM; i++) {
            char number_[20] = {'\0'};
            int_to_string(i, number_);
            printf("%s\n", number_);

            printf("%s\n", cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));

            strcat(SENT_FROM_PACKAGE[i - 1].title,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));
            quyinhao(SENT_FROM_PACKAGE[i - 1].title);
            printf("%s\n", SENT_FROM_PACKAGE[i - 1].title);

            strcat(SENT_FROM_PACKAGE[i - 1].body,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, SENT_FROM_PACKAGE[i - 1].title)));
            quyinhao(SENT_FROM_PACKAGE[i - 1].body);
            printf("%s\n", SENT_FROM_PACKAGE[i - 1].body);

            memset(CONTACT_ORDER, '\0', sizeof(CONTACT_ORDER));

            strcat(CONTACT_ORDER, "cont");
            strcat(CONTACT_ORDER, number_);

            strcat(SENT_FROM_PACKAGE[i - 1].contactor,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, CONTACT_ORDER)));
            quyinhao(SENT_FROM_PACKAGE[i - 1].contactor);
            printf("%s\n", SENT_FROM_PACKAGE[i - 1].contactor);

            memset(TIME_ORDER, '\0', sizeof(TIME_ORDER));
            strcat(TIME_ORDER, "time");
            strcat(TIME_ORDER, number_);

            strcat(SENT_FROM_PACKAGE[i - 1].time,
                   cJSON_Print(cJSON_GetObjectItem(CONTENT, TIME_ORDER)));
            quyinhao(SENT_FROM_PACKAGE[i - 1].time);
            printf("%s\n", SENT_FROM_PACKAGE[i - 1].time);


            memset(FILE_ORDER, '\0', sizeof(FILE_ORDER));
            strcat(FILE_ORDER, "file");
            strcat(FILE_ORDER, number_);

            strcat(SENT_FROM_PACKAGE[i - 1].f_title, "null");
            strcat(SENT_FROM_PACKAGE[i - 1].file, cJSON_Print(cJSON_GetObjectItem(CONTENT, FILE_ORDER)));
        }
    }

    return EMAIL_NUM;
}

int FETCH_FROM_UI_TO_CLIENT_TO_SERVER(cJSON *COMMAND_PACKAGE, char *type) {
    printf("the command package: %s\n", cJSON_Print(COMMAND_PACKAGE));
    char SIGNAL_BUFFER[100] = {'\0'};
    char PACKAGE_BUFFER[10000] = {'\0'};
    char RSP[] = {"REQUEST_FOR_SENDING_PACKAGE"};
    send(sockfd, cJSON_PrintUnformatted(COMMAND_PACKAGE), strlen(cJSON_PrintUnformatted(COMMAND_PACKAGE)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        printf("FAILED_TO_GET_READY\n");
        return -1;
    }
    if (strcmp(SIGNAL_BUFFER, "EXPECTED_SUCCESS") == 0) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        send(sockfd, RSP, strlen(RSP), 0);
        recret = recv(sockfd, PACKAGE_BUFFER, sizeof(PACKAGE_BUFFER), 0);
        if (recret == 0) {
            printf("PACKAGE_NOT_RECEIVED_OR_EMPTY\n");
            return 0;
        }
        cJSON *RECEIVE_PACKAGE = cJSON_Parse(PACKAGE_BUFFER);

        printf("%s\n", cJSON_Print(RECEIVE_PACKAGE));
        memset(PACKAGE_BUFFER, '\0', sizeof(PACKAGE_BUFFER));
        /*
         * FILL IN THE STRUCT
         */
        if (strcmp(type, "inbox") == 0) {
            size_inbox = FETCH_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(RECEIVE_PACKAGE, type);
        } else {
            size_sent = FETCH_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(RECEIVE_PACKAGE, type);
        }
        /*
         * THE STRUCT HAS BEEN FILLED IN
         */
        printf("GET_PACKAGE_SUCCEEDED\n");
        return 1;
    } else {
        printf("ERROR!\n");
        return 2;
    }
}

/* COMMAND_PACKAGE'S FORMAT :
 *      command_package : {
 *          command : "fetch"
 *          content : {
 *              username : "str;
 *              type : "inbox" / "outbox";
 *          }
 *      }
 */
bool FETCH_BUTTON_CLICKED(cJSON *COMMAND_PACKAGE, char *type) {
    /*
     * ADD COMMAND
     */
    cJSON *CONTENT = cJSON_GetObjectItem(COMMAND_PACKAGE, "content");
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(LOGGER));
    printf("%s\n", cJSON_Print(COMMAND_PACKAGE));
    switch (FETCH_FROM_UI_TO_CLIENT_TO_SERVER(COMMAND_PACKAGE, type)) {
        case -1:
            printf("FETCH_FAILED_TO_GET_READY\n");
            return false;
        case 0:
            printf("FETCH_PACKAGE_NOT_RECEIVED_OR_EMPTY\n");
            return false;
        case 1:
            /*
             * struct built completed
             */
            printf("FETCH_GET_PACKAGE_SUCCEEDED\n");
            return true;
        case 2:
            printf("FETCH_ERROR!\n");
            return false;
        default:
            printf("FETCH_UNEXPECTED_ERROR!\n");
            return false;
    }
}

// return all the titles as list, 6/times
//

/*
 * FETCH_DRAFT_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

int FETCH_DRAFT_FROM_UI_TO_CLIENT_TO_SERVER(cJSON *COMMAND_PACKAGE) {
    char SIGNAL_BUFFER[100] = {'\0'};
    char PACKAGE_BUFFER[1000] = {'\0'};
    char RSP[] = {"REQUEST_FOR_SENDING_PACKAGE"};
    send(sockfd, cJSON_PrintUnformatted(COMMAND_PACKAGE), strlen(cJSON_PrintUnformatted(COMMAND_PACKAGE)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        printf("FAILED_TO_GET_READY\n");
        return -1;
    }
    if (strcmp(SIGNAL_BUFFER, "EXPECTED_SUCCESS") == 0) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        send(sockfd, RSP, strlen(RSP), 0);
        recret = recv(sockfd, PACKAGE_BUFFER, sizeof(PACKAGE_BUFFER), 0);
        if (recret == 0) {
            printf("PACKAGE_NOT_RECEIVED_OR_EMPTY\n");
            return 0;
        }
        cJSON *RECEIVE_PACKAGE = cJSON_Parse(PACKAGE_BUFFER);
        memset(PACKAGE_BUFFER, '\0', sizeof(PACKAGE_BUFFER));

        /*
         * FILL IN THE STRUCT
         */

        printf("%s\n", cJSON_Print(RECEIVE_PACKAGE));

        size_draft = FETCH_DRAFT_PACKAGE_FROM_SERVER_TO_CLIENT(RECEIVE_PACKAGE);
        /*
         * THE STRUCT HAS BEEN FILLED IN
         */
        printf("GET_PACKAGE_SUCCEEDED\n");
        return 1;
    } else {
        printf("ERROR!\n");
        return 2;
    }
}

int FETCH_DRAFT_PACKAGE_FROM_SERVER_TO_CLIENT(cJSON *package) {
    char email_num[20] = {'\0'};
    strcat(email_num, cJSON_Print(cJSON_GetObjectItem(package, "number")));
    quyinhao(email_num);
    EMAIL_NUM = CHAR_TO_INT(email_num);
    MEMORY_SET_EMAIL_FETCH_BUFFER(DRAFT_FROM_PACKAGE);
    char CONTACT_ORDER[EMAIL_NUM + 20];
    char TIME_ORDER[EMAIL_NUM + 20];
    cJSON *CONTENT = cJSON_GetObjectItem(package, "content");
    printf("%s\n", cJSON_Print(CONTENT));
    for (int i = 1; i <= EMAIL_NUM; i++) {
        char number_[20] = {'\0'};
        int_to_string(i, number_);
        printf("%s\n", number_);

        printf("%s\n", cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));

        strcat(DRAFT_FROM_PACKAGE[i - 1].title,
               cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));
        quyinhao(DRAFT_FROM_PACKAGE[i - 1].title);
        printf("%s\n", DRAFT_FROM_PACKAGE[i - 1].title);

        strcat(DRAFT_FROM_PACKAGE[i - 1].body,
               cJSON_Print(cJSON_GetObjectItem(CONTENT, DRAFT_FROM_PACKAGE[i - 1].title)));
        quyinhao(DRAFT_FROM_PACKAGE[i - 1].body);
        printf("%s\n", DRAFT_FROM_PACKAGE[i - 1].body);

        memset(CONTACT_ORDER, '\0', sizeof(CONTACT_ORDER));

        strcat(CONTACT_ORDER, "cont");
        strcat(CONTACT_ORDER, number_);

        strcat(DRAFT_FROM_PACKAGE[i - 1].contactor,
               cJSON_Print(cJSON_GetObjectItem(CONTENT, CONTACT_ORDER)));
        quyinhao(DRAFT_FROM_PACKAGE[i - 1].contactor);
        printf("%s\n", DRAFT_FROM_PACKAGE[i - 1].contactor);

        memset(TIME_ORDER, '\0', sizeof(TIME_ORDER));
        strcat(TIME_ORDER, "time");
        strcat(TIME_ORDER, number_);

        strcat(DRAFT_FROM_PACKAGE[i - 1].time,
               cJSON_Print(cJSON_GetObjectItem(CONTENT, TIME_ORDER)));
        quyinhao(DRAFT_FROM_PACKAGE[i - 1].time);
        printf("%s\n", DRAFT_FROM_PACKAGE[i - 1].time);

        strcat(DRAFT_FROM_PACKAGE[i - 1].f_title, "null");
        strcat(DRAFT_FROM_PACKAGE[i - 1].file, "null");
    }
    return EMAIL_NUM;
}

bool FETCH_DRAFT_BUTTON_CLICKED() {
    cJSON *COMMAND_PACKAGE = PRE_STRUCTURE("fetch_draft");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(COMMAND_PACKAGE, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(LOGGER));

    switch (FETCH_DRAFT_FROM_UI_TO_CLIENT_TO_SERVER(COMMAND_PACKAGE)) {
        case -1:
            printf("FETCH_DRAFT_FAILED_TO_GET_READY\n");
            return false;
        case 0:
            printf("FETCH_DRAFT_PACKAGE_NOT_RECEIVED_OR_EMPTY\n");
            return false;
        case 1:
            /*
             * struct built completed
             */
            printf("FETCH_DRAFT_GET_PACKAGE_SUCCEEDED\n");
            return true;
        case 2:
            printf("FETCH_DRAFT_ERROR!\n");
            return false;
        default:
            printf("FETCH_DRAFT_UNEXPECTED_ERROR!\n");
            return false;
    }
}

/*
 * GET_CONTACT_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

/*
 * The data-structure of receiving package is :
 *      receiving : {
 *          num : "int"
 *          content : {
 *              1 : "username1";
 *              2 : "username2";
 *              ...
 *              num : "usernamenum";
 *
 *              username1 : "remark1";
 *              username2 : "remark2";
 *              ...
 *              usernamenum : "remark3";
 *
 *          }
 *      }
 */

void MEMORY_SET_GET_CONTACT_BUFFER() {
    for (int i = 0; i < FRIEND_NUM; i++) {
        memset(FRIEND_LIST[i].username, '\0', sizeof(FRIEND_LIST[i].username));
        memset(FRIEND_LIST[i].remark, '\0', sizeof(FRIEND_LIST[i].remark));
    }
}

int GET_CONTACT_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(cJSON *package) {
    /*
     * GET_NUMBER_PART
     */
    char friend_num[20] = {'\0'};
    strcat(friend_num, cJSON_Print(cJSON_GetObjectItem(package, "number")));
    quyinhao(friend_num);
    FRIEND_NUM = CHAR_TO_INT(friend_num);
    MEMORY_SET_GET_CONTACT_BUFFER();
    /*
     * package get
     */
    cJSON *CONTENT = cJSON_GetObjectItem(package, "content");
    printf("%s\n", cJSON_Print(CONTENT));
    for (int i = 1; i <= FRIEND_NUM; i++) {

        char number_[20] = {'\0'};
        int_to_string(i, number_);
        printf("%s\n", number_);
        // printf("%s\n", cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));

        strcat(FRIEND_LIST[i - 1].username,
               cJSON_Print(cJSON_GetObjectItem(CONTENT, number_)));
        quyinhao(FRIEND_LIST[i - 1].username);
        printf("%s\n", FRIEND_LIST[i - 1].username);

        strcat(FRIEND_LIST[i - 1].remark,
               cJSON_Print(cJSON_GetObjectItem(CONTENT, FRIEND_LIST[i - 1].username)));
        quyinhao(FRIEND_LIST[i - 1].remark);
        printf("%s\n", FRIEND_LIST[i - 1].remark);
    }
    return FRIEND_NUM;
}

int GET_CONTACT_FROM_UI_TO_CLIENT_TO_SERVER(cJSON *COMMAND_PACKAGE) {
    printf("%s\n", cJSON_Print(COMMAND_PACKAGE));
    char SIGNAL_BUFFER[100] = {'\0'};
    char PACKAGE_BUFFER[10000] = {'\0'};
    char RSP[] = {"REQUEST_FOR_SENDING_PACKAGE"};
    send(sockfd, cJSON_PrintUnformatted(COMMAND_PACKAGE), strlen(cJSON_PrintUnformatted(COMMAND_PACKAGE)), 0);
    recret = recv(sockfd, SIGNAL_BUFFER, sizeof(SIGNAL_BUFFER), 0);
    if (recret == 0) {
        printf("FAILED_TO_GET_READY\n");
        return -1;
    }
    if (strcmp(SIGNAL_BUFFER, "EXPECTED_SUCCESS") == 0) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        send(sockfd, RSP, strlen(RSP), 0);
        recret = read(sockfd, PACKAGE_BUFFER,
                      sizeof(PACKAGE_BUFFER));// recv(sockfd, PACKAGE_BUFFER, sizeof(PACKAGE_BUFFER), 0);

        // printf("%s\n", cJSON_Print(PACKAGE_BUFFER));

        if (recret == 0) {
            printf("PACKAGE_NOT_RECEIVED_OR_EMPTY\n");
            return 0;
        }
        cJSON *RECEIVE_PACKAGE = cJSON_Parse(PACKAGE_BUFFER);
        memset(PACKAGE_BUFFER, '\0', sizeof(PACKAGE_BUFFER));
        printf("%s\n", cJSON_Print(RECEIVE_PACKAGE));
        /*
         * FILL IN THE STRUCT
         */
        size_contact = GET_CONTACT_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(RECEIVE_PACKAGE);
        /*
         * THE STRUCT HAS BEEN FILLED IN
         */
        printf("GET_PACKAGE_SUCCEEDED\n");
        return 1;
    } /*else if(strcmp(SIGNAL_BUFFER, "EMPTY_LIST") == 0) {
        memset(SIGNAL_BUFFER, '\0', sizeof(SIGNAL_BUFFER));
        return 1;
    } */
    else {
        printf("ERROR!\n");
        return 2;
    }
}

bool GET_CONTACT_BUTTON_CLICKED() {
    /*
     * ADD COMMAND
     */
    cJSON *COMMAND_PACKAGE = PRE_STRUCTURE("get_contact");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(COMMAND_PACKAGE, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(LOGGER));
    printf("%s\n", cJSON_Print(COMMAND_PACKAGE));
    switch (GET_CONTACT_FROM_UI_TO_CLIENT_TO_SERVER(COMMAND_PACKAGE)) {
        case -1:
            printf("GET_CONTACT_FAILED_TO_GET_READY\n");
            return false;
        case 0:
            printf("GET_CONTACT_PACKAGE_NOT_RECEIVED_OR_EMPTY\n");
            return false;
        case 1:
            /*
             * struct built completed
             */
            printf("GET_CONTACT_GET_PACKAGE_SUCCEEDED\n");
            return true;
        case 2:
            printf("GET_CONTACT_ERROR!\n");
            return false;
        default:
            printf("GET_CONTACT_UNEXPECTED_ERROR!\n");
            return false;
    }
}

/*
 * CONNECTION_FUNCTION_PART
 * -----------------------------------------------------------------------------------------------------------------
 */

void sig1(int signum) {
    char quit[] = {"signal_quit"};

    if (SIGINT == signum) {
        flag = -1;
        send(sockfd, quit, strlen(quit), 0);
        close(sockfd);
        sleep(1);
        jionret = pthread_join(th, NULL);
        if (jionret != 0) {
            printf("子线程没有被回收！");
        }
        if (jionret == 0) {
            printf("安全退出！\n");
        }
        exit(0);
    }
}

//子线程函数
void *thread_control(void *arg) {
    while (flag == 0) {
        recret = recv(sockfd, recvbuf, sizeof(recvbuf), 0); //阻塞接收，
        if (recret > 0) {
            printf("%s\n", recvbuf); // output (xia:ejfhef)
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        if (recret == 0) {
            printf("连接断开\n");
            break;
        }
    }
    printf("子线程已退出\n");
    pthread_exit(NULL);
}


bool CONNECTION() {
    signal(SIGINT, sig1);
    //第一步：创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return -1;
    }
    //第二步：connect 连接服务器
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6000);
    servaddr.sin_addr.s_addr = inet_addr("192.168.43.185"); //htonl(INADDR_ANY);

    connectfd = connect(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    if (connectfd == -1) {
        perror("connect");
        return false;
    }
    return true;
}


