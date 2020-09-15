//
// Created by guangtao on 2020/9/15.
//
#include "define.h"

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
    // return package;
    char DELETE_BUFFER[30] = {'\0'};
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

bool LOGOFF_TEST_FUNCTION(char * username) {
    if (LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(username)) {
        return true;
    }
    else {
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

char ERROR[] = {"Get recover name failed!\n"};

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

bool GET_RECOVER_QUESTION(char *account_name, char *security_question, char *ans) {
    cJSON *package = PRE_STRUCTURE("get_recover_question");
    cJSON *CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(package, "content", CONTENT);
    cJSON_AddItemToObject(CONTENT, "account_name", cJSON_CreateString(account_name));

    char GRN_BUFFER[100] = {'\0'};
    send(sockfd, cJSON_PrintUnformatted(package), strlen(cJSON_PrintUnformatted(package)), 0);
    recret = recv(sockfd, GRN_BUFFER, sizeof(GRN_BUFFER), 0);
    if (recret == 0) {
        memset(ans, '\0', sizeof(ans));
        strcat(ans, ERROR);
        return false;
    }
    if (strcmp(GRN_BUFFER, "EXPECTED_SUCCESS") == 0) {
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
        memset(ans, '\0', sizeof(ans));
        strcat(ans, GRN_BUFFER);
        return true;
    } else {
        memset(ans, '\0', sizeof(ans));
        strcat(ans, ERROR);
        return false;
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

void RECOVER_BUTTON_CLICKED(char *account_name) {
    char security_question[100] = {'\0'};
    char answer_to_the_question[100] = {'\0'};
    if (GET_RECOVER_QUESTION(account_name, security_question, answer_to_the_question)
        && strcmp(answer_to_the_question, ERROR) != 0) {
        /*
         * switch to the next page
         */
        cJSON *package = PRE_STRUCTURE("recover");
        cJSON *CONTENT = cJSON_CreateObject();
        cJSON_AddItemToObject(package, "content", CONTENT);
        cJSON_AddItemToObject(CONTENT, "username", cJSON_CreateString(account_name));
        // cJSON_AddItemToObject(CONTENT, "recover_question", cJSON_CreateString(security_question));
        cJSON_AddItemToObject(CONTENT, "recover_answer", cJSON_CreateString(answer_to_the_question));
        if (PAGE_SWITCHER(package)) {
            /*
             * // popup_page
             * // popup_page
             */
        }
    } else {
        printf("ANS_AND_QUESTION_ERROR!\n");
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
    cJSON_AddItemToObject(CONTENT, "description", cJSON_CreateString(des));
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

cJSON *SAVE_DRAFT_CLIENT_TO_SERVER(char *account_name, cJSON *PACKAGE_FROM_UI) {
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
 * Since the MAINPAGE can't receive who is now logging in
 * So save the account (sender) as a global para
 * deliver this into the function
 */
bool SAVE_DRAFT_BUTTON_CLICKED(char *username, char *title, char *body) {  // API for the UI

    /*
     * Here is the space for the cJSON packing process
     * (UI) will pack it
     */
    //// global parameter -- account name
    char account_name[] = {""};
    cJSON *result = cJSON_CreateObject();
    cJSON *package = cJSON_CreateObject();
    package = SAVE_DRAFT_CLIENT_TO_SERVER(account_name, result);

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
    cJSON * PACKAGE_FROM_CLIENT = cJSON_CreateObject();
    PACKAGE_FROM_CLIENT = SENDER_CLIENT_TO_SERVER(username, PACKAGE_FROM_UI_t);
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
    if (SENDER_CLIENT_TO_UI(SENDER_BUFFER)) {
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
bool SET_CONTACT_WHOLE_PROCESS(cJSON *package) {
    char SIGNAL_BUFFER[100] = {'\0'};
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

int main() {
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
    char rec_test[5] = {"\0"};
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

    // register

    char acn[] = {"ACCOUNT_NAME"};
    char emn[] = {"TEST_ACCOUNT@test.com"};
    char pass[] = {"testpassword"};
    char nps[] = {"newpassword"};
    char recovery_question[] = {"Is this a test question?"};
    char recovery_question_answer[] = {"Yes, it is!"};
    char recipient[] = {"TEST_RECEIVER@test.com"};
    char description[] = {"default"};
    char title[] = {"THE TEST_EMAIL"};
    char body[] = {"THE TEST_BODY:\n\tHELLO: I M THE TESTER"};
    char alias[] = {"nickname_contactor"};
    cJSON *PACKAGE_FOR_SENDING = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FOR_SENDING, "recipient", cJSON_CreateString(recipient));
    cJSON_AddItemToObject(PACKAGE_FOR_SENDING, "title", cJSON_CreateString(title));
    cJSON_AddItemToObject(PACKAGE_FOR_SENDING, "body", cJSON_CreateString(body));

    cJSON *PACKAGE_FOR_SET_CONTACT = cJSON_CreateObject();
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "alias", cJSON_CreateString(alias));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "contact_name", cJSON_CreateString(recipient));
    cJSON_AddItemToObject(PACKAGE_FOR_SET_CONTACT, "account_name", cJSON_CreateString(body));

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

    // login
    switch(SIGN_WHOLE_PROCESS(emn, pass)) {
        case 0:
            printf("UNEXPECTED_ERROR");
            break;
        case 1:
            printf("EXPECTED_SUCCESS");
            break;
        case 2:
            printf("ACCOUNT_INVALID");
            break;
        case 3:
            printf("PASSWORD_INVALID");
            break;
        default:
            printf("ERROR\n");
    }

    // send
    SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(emn, PACKAGE_FOR_SENDING);

    // (fetch)
    // save draft


    // (fetch draft)
    // recover question


    // recovery


    // (get contact)
    // set contact
    if (SET_CONTACT_WHOLE_PROCESS(PACKAGE_FOR_SET_CONTACT)) {
        printf("SET_CONTACT SUCCESSFULLY\n");
    } else {
        printf("SET_CONTACT FAILED\n");
    }

    // delete
    if (LOGOFF_TEST_FUNCTION(emn)) {
        printf("LOG OFF SUCCESSFULLY\n");
    } else {
        printf("LOG OFF FAILED\n");
    }

    return 0;
}