#include "info-acc.h"
#include <string.h>
#include <stdio.h>
/*
 * for checking if the answer of this question is valid or not
 */
bool QuestionCheck(char *answer, struct account client) {
    char ans[SEQ_QUANSWER_LENGTH] = {'\0'};
    strcat(ans, client.securityQuAnswer);
    return strcmp(answer, ans) == 0 ? true : false;
}

void QuAnswerChanging(char *NewAns, struct account client) {
    memset(client.securityQuAnswer, '\0', sizeof(client.securityQuAnswer));
    strcat(client.securityQuAnswer, NewAns);
}

/*
 * to validate the password
 */
bool PasswdCheck(char *passwd, struct account client) {
    char key[PASSWORD_LENGTH];
    strcat(key, client.passwd);
    return strcmp(key, passwd) == 0 ? true : false;
}

void PasswdChanging(char *NewPsw, struct account client) {
    memset(client.passwd, '\0', sizeof(client.passwd));
    strcat(client.passwd, NewPsw);
}
///---------------------------------------///
/*
 * to format the password
 *
bool PS_checker(char *password) {
    char passwd[PASSWORD_LENGTH];
    strcat(passwd, password);
    //////////////
}

*
 * to format the identity

bool ID_checker(char *client_name) { //
    char username[USERNAME_LENGTH];
    strcat(username, client_name);
    if (username) { //
        return true;
    } else return false;
}
*/
///---------------------------------------///
/*
 * cast from strings to account (struct)
 */
struct account StrToAcc(char *p, char *usr, char *SQ, char *SQA) {
    struct account client;
    strcat(client.passwd, p);
    strcat(client.usrname, usr);
    strcat(client.securityQuestion, SQ);
    strcat(client.securityQuAnswer, SQA);
    return client;
}

void Register_(struct account client) {
    CreateAccount(client);
}

void QuestionChanging(int NewQueNum, struct account client) {
    // char origin[SEQ_QUESTION_LENGTH] = {'\0'};
    // strcat(origin, client.securityQuestion);
    memset(client.securityQuestion, '\0', sizeof(client.securityQuestion));
    strcat(client.securityQuestion, Question_Convert(NewQueNum));
}

const char* Question_Convert(int SEQ_NUM) {
    switch (SEQ_NUM) {
        case 1:
            return Q_A;
        case 2:
            return Q_B;
        case 3:
            return Q_C;
        case 4:
            return Q_D;
        case 5:
            return Q_E;
        default:
            return Q_A;
    }
}

bool DeleteAccount(struct account client) {
    return true;
}

struct account CreateAccount() {
    // user_name initiate
    struct account client;
    memset(client.usrname, '\0', sizeof(client.usrname));
    memset(client.passwd, '\0', sizeof(client.passwd));
    memset(client.securityQuAnswer, '\0', sizeof(client.securityQuAnswer));
    memset(client.securityQuestion, '\0', sizeof(client.securityQuestion));
    memset(client.description, '\0', sizeof(client.description));
    memset(client.nickname, '\0', sizeof(client.nickname));
    char usr[USERNAME_LENGTH];
    printf("please input your name: \n");
    scanf("%s", usr);

    // password initiate
    char p[PASSWORD_LENGTH];
    printf("please input your password: \n");
    scanf("%s", p);

    // security question set
    int SEQ_NUM = 0;
    char SQ[SEQ_QUESTION_LENGTH];
    printf("please input your Security Question No. : \n");
    scanf("%d", &SEQ_NUM);
    strcat(SQ, Question_Convert(SEQ_NUM));
    printf("The Seq_question is: %s\n", SQ);

    // answer to the question set
    char SQA[SEQ_QUANSWER_LENGTH];
    printf("please input your Answer: \n");
    scanf("%s", SQA);

    strcat(client.usrname, usr);
    strcat(client.passwd, p);
    strcat(client.securityQuestion, SQ);
    strcat(client.securityQuAnswer, SQA);



    return client;
}
