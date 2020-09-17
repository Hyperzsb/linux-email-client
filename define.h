//
// Created by guangtao on 2020/9/15.
//

#ifndef CLIENT_NEW_DEFINE_H
#define CLIENT_NEW_DEFINE_H

#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <z3.h>
#include <regex.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <gtk/gtk.h>
#include <cJSON.h>
#include <pango/pango.h>
#include <signal.h>
#include <arpa/inet.h>

struct EMAIL_CONTENT {
    char title[100];    // the title of the mail
    char body[10000];   // the mail's body
    char contactor[100];    //  the mailing people
    char time[100];
    char f_title[100];
    char file[20000];
};

struct CONTACT_INFO {
    char remark[100];
    char username[100];
};

extern bool RECOVERY_BUTTON_CLICKED_(char *ans, char *passwd);

extern int FETCH_FROM_UI_TO_CLIENT_TO_SERVER(cJSON *COMMAND_PACKAGE, char *type);

extern void quyinhao(char *str);

extern cJSON *PRE_STRUCTURE(char *command);

extern void BUTTON_CLICKED_TO_SET_CONTACT(struct cJSON *package);

extern bool SET_CONTACT_WHOLE_PROCESS(cJSON *package);

extern bool ADD_CONTACT(char *remark, char *username);

extern void SENDER_UI_DATA_SUBMIT_BUTTON_CLICKED(char *username, cJSON *PACKAGE_FROM_UI_t);

extern bool SENDER_CLIENT_TO_UI(char *SIGNAL_FROM_SERVER);

extern cJSON *SENDER_CLIENT_TO_SERVER(char *username, cJSON *PACKAGE_FROM_UI);

extern int flag_transmit(char *username, char *nickname, char *password, char *des, char *seq_question, char *ans);

extern bool email_addr_format(char *email_account);

extern bool GET_RECOVER_QUESTION(char *account_name, char *question);

extern int SIGN_WHOLE_PROCESS(char *account_name, char *password);

extern bool LOGOFF_DEACTIVIATE_ACCOUNT_BUTTON_CLICKED(char *email_addr);

extern cJSON *SAVE_DRAFT_CLIENT_TO_SERVER(char *recipient, cJSON *PACKAGE_FROM_UI);

extern bool SAVE_DRAFT_BUTTON_CLICKED(char *recipient, char *title, char *body);

extern bool PAGE_SWITCHER(cJSON *package);

extern int QUESTION_GET_BUTTON_CLICKED(char *account_name, char *ans, char *new_password);

extern void RECOVER_BUTTON_CLICKED(char *account_name);

extern int SIGNIN_FROM_SERVER_TO_CLIENT(char *SIGNAL);

extern cJSON *SIGNIN_FROM_CLIENT_TO_SERVER(char *account_name, char *password);

extern char *GET_RECOVER_QUESTION_ORIGIN(char *account_name, char *security_question);

extern bool CONNECTION();

extern void *thread_control(void *arg);

extern void sig1(int signum);

extern int CHAR_TO_INT(char *num_target);

extern int FETCH_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(cJSON *package, char *type);

extern void int_to_string(int num, char *str);

extern int GET_CONTACT_CONTENT_PACKAGE_FROM_SERVER_TO_CLIENT(cJSON *package);

extern int FETCH_DRAFT_PACKAGE_FROM_SERVER_TO_CLIENT(cJSON *package);

extern int FETCH_DRAFT_FROM_UI_TO_CLIENT_TO_SERVER(cJSON *COMMAND_PACKAGE);

extern int GET_CONTACT_FROM_UI_TO_CLIENT_TO_SERVER(cJSON *COMMAND_PACKAGE);

extern void MEMORY_SET_GET_CONTACT_BUFFER();

extern bool FETCH_DRAFT_BUTTON_CLICKED();

extern bool FETCH_BUTTON_CLICKED(cJSON *COMMAND_PACKAGE, char *type);

extern void PAGE_INPUT_GETTER(char *name, char *ans, char *passwd);

extern bool LOGOFF_TEST_FUNCTION(char *username);

extern bool GET_CONTACT_BUTTON_CLICKED();


extern int sockfd;// = -1;
extern int recret;// = -1;

//static int sendret = -1;
extern int flag;// = 0;
extern char recvbuf[100];// = {0};        //收数据的数组

//static int setsocketret = -1;
//static int bindfd = -1;
extern int connectfd;// = -1;
//static int sendfd = -1;
//static char sendbuf[100] = {0};        //发送数据的数组
extern struct sockaddr_in servaddr; //  = {0};
extern pthread_t th;// = -1;  //线程标识号
extern int jionret;// = -1;

extern char fl[20050];

extern int size_inbox;
extern int size_contact;
extern int size_sent;
extern int size_draft;

extern char ERROR[100];
extern char LOGGER[100];
struct EMAIL_CONTENT EMAIL_FROM_PACKAGE[600];
struct EMAIL_CONTENT SENT_FROM_PACKAGE[600];
struct EMAIL_CONTENT DRAFT_FROM_PACKAGE[600];
struct EMAIL_CONTENT DUSTBIN_FROM_PACKAGE[600];
struct CONTACT_INFO FRIEND_LIST[600];

extern void SAVE_AC();

extern char FILE_PATH[300];

int EMAIL_NUM;
int FRIEND_NUM;

extern void MEMORY_SET_EMAIL_FETCH_BUFFER(struct EMAIL_CONTENT *EMAIL);

#endif //CLIENT_NEW_DEFINE_H
