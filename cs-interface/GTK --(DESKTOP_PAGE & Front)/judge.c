#include "judge.h"

int judge(char *a, char *b) {

    int flag1 = 0;
    int flag2 = 0;
    int len = strlen(a);
    if (len < 6 || len > 12)
        return 0;
    else {
        for (int i = 0; i < len; i++) {
            if (a[i] >= '0' && a[i] <= '9')
                flag1 = 1;
            if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z'))
                flag2 = 1;
        }
        if (flag1 * flag2 == 0)
            return 0;
        else {
            if (strcmp(a, b) == 0)
                return 1;
            else
                return 0;
        }
    }
}
