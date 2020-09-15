#include "check.h"

int check(char *a, char *b)//登录验证
{

    int flag1 = 0;
    int flag2 = 0;
    int len = strlen(b);
    if (len < 6 || len > 12) Fail_login_1();
    else {
        for (int i = 0; i < len; i++) {
            if (b[i] >= '0' && b[i] <= '9')
                flag1 = 1;
            if ((b[i] >= 'a' && b[i] <= 'z') || (b[i] >= 'A' && b[i] <= 'Z'))
                flag2 = 1;
        }
        if (flag1 * flag2 == 0) Fail_login_1();
        else {
            //sendto_sql连接数据库，0用户名不存在，1密码不正确，2进入邮箱主界面，else系统错误
            //int send=sendto_sql();
            int send = 3;
            if (send == 0) {
                Fail_login_2();
            } else if (send == 1) {
                Fail_login_3();
            } else if (send == 2) {
                //前往邮件主页面
            } else System_false();

        }
    }
}

int reset_judge(char *a, char *b)//重设密码合法性判断
{
    int flag1 = 0;
    int flag2 = 0;
    int len = strlen(b);
    if (len < 6 || len > 12) Fail_login_1();
    else {
        for (int i = 0; i < len; i++) {
            if (b[i] >= '0' && b[i] <= '9')
                flag1 = 1;
            if ((b[i] >= 'a' && b[i] <= 'z') || (b[i] >= 'A' && b[i] <= 'Z'))
                flag2 = 1;
        }
        if (flag1 * flag2 == 0) Fail_login_1();
        else {
            //把新密码传给数据库（）；
            reset_password_success();
        }
    }

}	
