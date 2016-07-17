#include <stdio.h>
/*
40: black-b                      30: black
41: 红                           31: 红
42: 绿                           32: 绿
43: 黄                           33: 黄
44: 蓝                           34: 蓝
45: 紫                           35: 紫
46: 深绿                         36: 深绿
47: 白色                         37: 白色
 */
#define SPACE 32


short graph_color(int bg, int fg)
{
    short rt = 0;
    rt = rt | fg;
    rt = rt | (bg << 8 & 0xFF00);
    return rt;
}


void graph_clear()
{
    printf("\033[H\033[J");
}

void graph_flush()
{
    printf("\033[?25l");
    printf("\n");
}

void graph_gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

/*
 * color: 0xFFEE, FF stands for background color, EE is color
 */
void graph_rect(int x, int y, int w, int h, short color, char frame)
{
    unsigned char bg = 40;
    unsigned char fg = 37;
    int i = 0;
    int j = 0;
    char c = 0;
    char *pbuf = 0;
    pbuf = (char*) malloc(w * sizeof(char));

    /*
     * Initailize color settings
     */
    if(color != 0)
    {
        bg = (color >> 8) & 0x00FF;
        fg = color & 0x00FF;
    }

    /*
       =================
       |               |
       |               |
       =================
       == top&bottom frames
       || left&right frames
     */
    for( ; i < h; i ++ )
    {
        graph_gotoxy(x, y + i);
        /// draw top & bottom frame
        if(i == 0 || i == h - 1)
        {
            memset(pbuf, frame, w * sizeof(char));
            printf("\033[%d;%dm%s\033[0m", bg, fg, pbuf);
        }
        else /// draw middle parts
        {
            memset(pbuf, SPACE, w * sizeof(char)); 
            pbuf[0] = frame;
            pbuf[w - 1] = frame;
            printf("\033[%d;%dm%s\033[0m", bg, fg, pbuf);
        }
   //     printf("\n");
    }
    free(pbuf);
}

void graph_text(int x, int y, const char* text, short color)
{
    unsigned char bg = 40;
    unsigned char fg = 37;


    if(color != 0)
    {
        bg = (color >> 8) & 0x00FF;
        fg = color & 0x00FF;
    }
    graph_gotoxy(x, y);
    printf("\033[%d;%dm%s\033[0m", bg, fg, text);
}
