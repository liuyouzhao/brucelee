#include <stdio.h>

int main()
{
    const char* src = "hello brucelee!";
    char outter[256] = {0};
    md5_sum(src, strlen(src), outter); 
    printf("hello brucelee! md5 is: %s\n", outter);
    return 0;
}
