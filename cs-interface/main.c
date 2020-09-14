#include "PRE_CONDITIONS.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>

#include "cJSON_PACKAGES.h"

int sendret = -1;
int recvret = -1;
int flag = 0;
char recvbuf[100] = {0};        //收数据的数组

int setsocketret = -1;
int bindfd = -1;
int connectfd = -1;
int sendfd = -1;
char sendbuf[100] = {0};        //发送数据的数组
struct sockaddr_in servaddr = {0};
pthread_t th = -1;  //线程标识号
int sockfd = -1;
int jionret = -1;

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
        recvret = recv(sockfd, recvbuf, sizeof(recvbuf), 0); //阻塞接收，
        if (recvret > 0) {
            printf("%s\n", recvbuf); // output (xia:ejfhef)
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        if (recvret == 0) {
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

int main(int argc, char *argv[]) {
    /*
    cJSON * test_package = cJSON_CreateObject();
    struct account test_client;
    test_client = CreateAccount();
    /
    test_package = cJSON_PACKAGE_MAKE_REGISTER(test_client.usrname,
                                               test_client.passwd,
                                               test_client.nickname,
                                               test_client.description,
                                               test_client.securityQuestion,
                                               test_client.securityQuAnswer);

    test_package = cJSON_PACKAGE_MAKE_DELETE(test_client.usrname);
    printf("%s\n", cJSON_Print(test_package));
    */
    // BUTTON_CLICKED SHALL BE A FUNCTION FOR CONNECTING THE SERVER
    // IF IT DOES NOT WORK, THE LOOPS WILL KEEP GOING BACK TO WHERE THE POINT IS;
    /*
connection_point:
    if (BUTTON_CLICKED() == 1) {
        if (CONNECTION() == false) {
            goto connection_point;
        }
    } else {
        goto connection_point;
    }
     */////////////////////
    // IF CONNECTION IS DONE, SWITCH TO THE INIT PAGE
    //////SWITCHER_TO_LOGIN_AND_REGISTER_PAGE();

    //UPPER PART IS FOR CONNECTION AND SWITCH TO LOGIN PAGE
    //-----------------------------------------------------------------------//
    //子线程读
    /////pthread_create(&th, NULL, thread_control, NULL);
   ///// int times = 100;
    //主线程写
    /////while (true) {////
        /*
        scanf("%s", sendbuf);
        send(sockfd, sendbuf, strlen(sendbuf), 0);
        memset(sendbuf, 0, sizeof(sendbuf));
        */
    ///    if (times--) break;/////
    if (CONNECTION() == false) {
        printf("CONNECTION FAILED.\n");
    }

    cJSON * test = cJSON_CreateObject();
    test = PRE_STRUCTURE("fetch_mail");
    cJSON * CONTENT = cJSON_CreateObject();
    cJSON_AddItemToObject(test, "content", CONTENT);

    send(sockfd, cJSON_PrintUnformatted(test), strlen(cJSON_PrintUnformatted(test)), 0);
    int REC = 0, REC_ORIGIN = 0;
    // char rec_test[5] = {"\0"};
    char rec_origin[100] = {'\0'};
    REC_ORIGIN = recv(sockfd, rec_origin, sizeof(rec_origin), 0);

    if (REC_ORIGIN > 0) {
        printf("%s\n", rec_origin);
    }
    else {
        printf("receive nothing\n");
    }
    memset(rec_origin, '\0', sizeof(rec_origin));
    REC = recv(sockfd, rec_origin, sizeof(rec_origin), 0);
    if (REC > 0) {
        printf("%s\n", rec_origin);
    }
    else {
        printf("receive nothing\n");
    }

    return 0;
}

