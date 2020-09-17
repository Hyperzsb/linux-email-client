//
// Created by guangtao on 2020/9/16.
//

#ifndef CLIENT_NEW_UI_H
#define CLIENT_NEW_UI_H

#include "define.h"

/*
 * data_struct for logging in
 */
typedef struct {
    GtkWidget *emailname;//邮箱名
    GtkWidget *petname;//昵称
    GtkWidget *password;//密码
    GtkWidget *confirm;//密码确认
    GtkWidget *description;
    GtkWidget *security_question;//密保问题
    GtkWidget *answer;//问题答案
} Information;

extern Information secure;//储存用户信息的结构
extern GtkWidget *window_v;//创建验证窗口指针
extern Information aa;
extern GtkWidget *window_r;
extern Information Register;;

extern int main_mail(int argc, char *argv[]);

extern void logout_button(GtkButton* button, gpointer data);
extern void write_button(GtkButton* button, gpointer data);
extern void get_button_num(GtkButton* button, gpointer data);
extern void get_page_num(GtkNotebook* notebook, gpointer page, guint page_n, gpointer user_data);
extern void open_email(GtkButton* button, gpointer data);
extern void reply_email(GtkButton* button, gpointer data);
extern void fresh_button(GtkButton* button, gpointer data);
extern void add_contactor_button(GtkButton* button, gpointer data);
extern void add_contactor_confirm(GtkButton* button, gpointer data);
extern void search_email_button(GtkButton* button, gpointer data);
extern void clear_input(GtkButton* button, gpointer data);

GtkWidget* window;
GtkWidget* table_main;
GtkWidget* notebook;
GtkWidget* table_home;
GtkWidget* table_write;
GtkWidget* table_inbox;
GtkWidget* table_contact;
GtkWidget* table_sent;
GtkWidget* table_draft;
GtkWidget* table_dustbin;
GtkWidget* scrolled_inbox;
GtkWidget* scrolled_contact;
GtkWidget* scrolled_sent;
GtkWidget* scrolled_draft;
GtkWidget* scrolled_dustbin;
GtkWidget* scrolledtext;

GtkWidget* entry_addressee;
GtkWidget* entry_subject;
GtkWidget* textview;
GtkWidget* entry_remark;
GtkWidget* entry_username;
GtkWidget* entry_search;

int state;
int button_num;
int page_num;
int flag_search;

extern char a[20], b[20];

extern void reset_judge(char *password, char *confirm, char *answer);

extern void button_clicked(GtkWidget *widget, Information *a);

extern int reset_password_window(char *ques);

extern int register_main();

extern int judge(char *passwd, char *correct);

extern Information Info;//储存用户信息的结构

extern void load_css(void);

extern void socket_button_clicked(GtkWidget *widget, gpointer data);

extern void ok_clicked(GtkWidget *a, gpointer *data);

extern GtkWidget *create_window();

extern void System_false();

extern void Fail_login_1();

extern void Fail_login_2();

extern void Fail_login_3();

extern void Fail_reset();

extern void reset_password_success();

extern void Fail_remove();

extern void remove_success();

extern void main_window(GtkWidget *a);

extern void remove_button_clicked(GtkWidget *widget, gpointer data);

extern void forget_button_clicked(GtkWidget *widget, gpointer data);

extern void register_button_clicked(GtkWidget *widget, gpointer data);

extern void login_button_clicked(GtkWidget *widget, gpointer data);

extern void check(char *a, char *b);

extern void register_success();

extern void password_error();

extern void username_error();

extern GtkWidget *createwindow();

extern void submit_button_clicked(GtkWidget *widget, gpointer data);

extern int Verification_window();

extern void okclicked(GtkWidget *a, gpointer *data);

extern void recv_button(GtkButton *button, gpointer data);

static GtkWidget *entry1;//输入行1，用户名
static GtkWidget *entry2;//输入行2，密保问题
static GtkWidget *entry3;//输入行3，密报答案

#endif //CLIENT_NEW_UI_H
