//
// Created by guangtao on 2020/9/11.
//

#ifndef INFO_ACC_INFO_ACC_H
#define INFO_ACC_INFO_ACC_H
#include "PRE_CONDITIONS.h"

#define CLIENTS_INFO_PATH "../clients.csv"

struct account {
    char passwd[PASSWORD_LENGTH];
    char usrname[USERNAME_LENGTH];
    char nickname[NICKNAME_LENGTH];
    char securityQuestion[SEQ_QUESTION_LENGTH];
    char securityQuAnswer[SEQ_QUANSWER_LENGTH];
    char description[DESCRIPTION_LENGTH];
};

extern const char* Question_Convert(int SEQ_NUM);
extern bool DeleteAccount(struct account client);
extern void ErrorReturn(int caseNum); //
extern bool ID_checker(char *client_name);
extern bool PS_checker(char *password);
extern void Register__(struct account client);
extern struct account CreateAccount();
extern bool PasswdCheck(char *passwd, struct account client);
extern bool QuestionCheck(char *answer, struct account client);
extern void PasswdChanging(char *NewPsw, struct account client);
extern void QuestionChanging(int NewQueNUm, struct account client);
extern void QuAnswerChanging(char *NewAns, struct account client);
extern struct account StrToAcc(char *p, char *usr, char *SQ, char *SQA);

#endif //INFO_ACC_INFO_ACC_H
