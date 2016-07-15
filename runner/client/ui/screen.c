#include <stdio.h>


int flushscreen()
{
    system("cls");

    repaint();
}


int repaint(const char *pixels)
{
    print(pixels);
}
