#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#define MAX_BUF_LEN 256
#define EOT 3
#define CR 13
#define GPSP 29
#define LBRAC 91
#define ESC 27
#define A 65
#define B 66
#define C 67
#define D 68


char buf[MAX_BUF_LEN] = {0};
int tail = 0;

void* pthread_func(void* none)
{
    while(1)
    {
        char c = 0;
        system ("/bin/stty raw");
        c = getchar();

        printf("OUT!\n");

        buf[tail] = c;
        tail ++;
        system ("/bin/stty cooked");
    }
}

void screen_clear()
{
    printf("\033[H\033[J");
}

void screen_gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}


int main()
{
    char h[64] = {0};
    int i = 0;
    int hmax = 10;
    char c = 0;
    memset(h, 'O', 10);
    screen_clear();
    int n = 0;

    int gpsp = 0;
    int gpmid = 0;

#if 0
    while(1)
    {
        c = getchar();
        printf("%d ", c);
    }
#endif


    while(1)
    {

        char left[MAX_BUF_LEN] = {0};
        char right[MAX_BUF_LEN] = {0};
        if(tail >= 1)
        {
            memcpy(left, buf, tail);
            memcpy(right, buf + tail, strlen(buf) - tail);
        }


        system ("/bin/stty cooked");
        screen_gotoxy(100, 100);
        screen_clear();
        printf("\033[40;32m--------------------------------------\033[0m\n");
        printf("%d\n", tail);
        printf(":%s\n", buf);
        printf("\033[40;32m--------------------------------------\033[0m\n");
        printf("\033[40;32m[%s]\033[0m\n", h + ((i ++) % 10));

        system ("/bin/stty raw");
        c = getchar();
        switch(c)
        {
            case EOT:
                goto user_exit;
            case CR:
                tail = 0;
                memset(buf, 0, MAX_BUF_LEN);
                break;
            case ESC:
                gpsp = c;
                break;
            case LBRAC:
                gpmid = gpsp ? LBRAC : 0;
                break;
            default:
#if 0
                sprintf(buf + n, "%d", c);
                n += 2;
#else
                
                if(gpsp && gpmid)
                {
                    gpsp = gpmid = 0;
                    continue;
                }
                buf[tail++] = c;
#endif              
        }

    }


user_exit:
    system ("/bin/stty cooked");
    return 0;
}
