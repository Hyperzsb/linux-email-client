//
// Created by guangtao on 2020/9/15.
//

#ifndef CLIENT_NEW_DEFINE_H
#define CLIENT_NEW_DEFINE_H

#include "cJSON.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <z3.h>
#include <regex.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>
#include <cJSON.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>

extern cJSON *PRE_STRUCTURE(char *command);
extern void BUTTON_CLICKED_TO_SET_CONTACT(struct cJSON *package);
extern bool SET_CONTACT_WHOLE_PROCESS(cJSON *package);
extern void SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(char * username, cJSON *PACKAGE_FROM_UI_t);
extern bool SENDER_CLIENT_TO_UI(char *SIGNAL_FROM_SERVER);
extern cJSON *SENDER_CLIENT_TO_SERVER(char *account_name, cJSON *PACKAGE_FROM_UI);
extern int flag_transmit(char *username, char *nickname, char *password, char *des, char *seq_question, char *ans);
extern bool email_addr_format(char *email_account);
extern bool GET_RECOVER_QUESTION(char *account_name, char *security_question, char *ans);
extern int SIGN_WHOLE_PROCESS(char *account_name, char *password);
extern bool LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(char *email_addr);
extern cJSON *SAVE_DRAFT_CLIENT_TO_SERVER(char *account_name, cJSON *PACKAGE_FROM_UI);
extern bool SAVE_DRAFT_BUTTON_CLICKED(char *username, char *title, char *body);
extern bool PAGE_SWITCHER(cJSON *package);
extern void RECOVER_BUTTON_CLICKED(char *account_name);
extern int SIGNIN_FROM_SERVER_TO_CLIENT(char *SIGNAL);
extern cJSON *SIGNIN_FROM_CLIENT_TO_SERVER(char *account_name, char *password);
extern char *GET_RECOVER_QUESTION_ORIGIN(char *account_name, char *security_question);
extern bool CONNECTION();
extern void *thread_control(void *arg);
extern void sig1(int signum);


static int sockfd = -1;
static int recret = -1;

static int sendret = -1;
static int flag = 0;
static char recvbuf[100] = {0};        //收数据的数组

static int setsocketret = -1;
static int bindfd = -1;
static int connectfd = -1;
static int sendfd = -1;
static char sendbuf[100] = {0};        //发送数据的数组
static struct sockaddr_in servaddr = {0};
static pthread_t th = -1;  //线程标识号
static int jionret = -1;

#endif //CLIENT_NEW_DEFINE_H
