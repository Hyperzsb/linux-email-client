#include "define.h"
#include "UI2.h"

//#include"file_select.h"


//struct CONTACT_CONTENT{
//    char nickname[50];
//    char address[50];
//};

//struct EMAIL_CONTENT recv_content[100];
//struct CONTACT_CONTENT contact_content[100];

Information Info;
Information secure;//储存用户信息的结构
GtkWidget *window_v;//创建验证窗口指针
Information aa;
GtkWidget *window_r;


GtkWidget *table_read;
GtkWidget *window;
GtkWidget *table_main;
GtkWidget *label_greet;
GtkWidget *table_write;
GtkWidget *table_inbox;
GtkWidget *table_recv;
GtkWidget *table_contact;
GtkWidget *table_sent;
GtkWidget *table_draft;
GtkWidget *table_dustbin;

GtkWidget *entry_addressee;
GtkWidget *entry_subject;
GtkWidget *textview;
GtkWidget *button_acc_body;

char FILE_PATH[300] = {"/home/guangtao/桌面/client_new/1.txt"};

char ERROR[100] = {"Get recover name failed!\n"};
char LOGGER[100] = {'\0'};

int sockfd = -1;
int recret = -1;
char fl[20050] = {'\0'};
//static int sendret = -1;
int flag = 0;
char recvbuf[100] = {0};        //收数据的数组

//static int setsocketret = -1;
//static int bindfd = -1;
int connectfd = -1;
//static int sendfd = -1;
//static char sendbuf[100] = {0};        //发送数据的数组
struct sockaddr_in servaddr = {0};
pthread_t th = -1;  //线程标识号
int jionret = -1;

//
int size_inbox = 20;
int size_contact = 20;
int size_sent = 20;
int size_draft = 20;
//
int state;                                    //current table
int current_pos = 0;
int button_chosen = -1;            //the number of button been chosed

void SAVE_AC() {
    FILE *fp = fopen(FILE_PATH, "w");
    if (fp == NULL) {
        printf("File:\t%s ERROR!\n", FILE_PATH);
        return;
    }else{
        fprintf(fp, fl);
    }
}

int main(int argc, char *argv[]) {
    //初始化
    gtk_init(&argc, &argv);
    //主窗口
    GtkWidget *window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Flower Mailbox");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window),1500,1100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(window, FALSE);
    load_css();
    //字体大小

    PangoFontDescription *font2 = pango_font_description_from_string ("Sans-serif");
    pango_font_description_set_size (font2, 50* PANGO_SCALE);

//确定各模块坐标
    GtkWidget *fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window),fixed);

    GtkWidget *socket_button = gtk_button_new_with_label("SOCKET CONNECTION");
    gtk_fixed_put(GTK_FIXED(fixed),socket_button,350,350);
    gtk_widget_set_size_request(socket_button,800,200);
    gtk_widget_modify_font(socket_button,font2);

    g_signal_connect(G_OBJECT(socket_button),"clicked",G_CALLBACK(socket_button_clicked),(gpointer)window);

    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
