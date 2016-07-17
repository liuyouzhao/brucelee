#include <stdio.h>


void draw()
{
    while(1)
    {

        graph_clear();

        graph_rect(0, 0, 80, 50, graph_color(42, 42), 219);

        graph_rect(15, 10, 50, 10, graph_color(43, 30), 219);
        graph_text(30, 14, "Welcome to play!", graph_color(43, 30)); 
        graph_text(30, 24, "BRUCE LEE GAME STEAM", graph_color(45, 30)); 

        graph_flush();
        sleep(5);
    }
}


int main()
{
    draw();
    return 0;

}

