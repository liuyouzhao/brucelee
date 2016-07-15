#include <string.h>

#define MAX_QUEUE_LENGTH 128

#define NONE         "\033[m" 
#define RED          "\033[0;32;31m" 
#define LIGHT_RED    "\033[1;31m" 
#define GREEN        "\033[0;32;32m" 
#define LIGHT_GREEN  "\033[1;32m" 
#define BLUE         "\033[0;32;34m" 
#define LIGHT_BLUE   "\033[1;34m" 
#define DARY_GRAY    "\033[1;30m" 
#define CYAN         "\033[0;36m" 
#define LIGHT_CYAN   "\033[1;36m" 
#define PURPLE       "\033[0;35m" 
#define LIGHT_PURPLE "\033[1;35m" 
#define BROWN        "\033[0;33m" 
#define YELLOW       "\033[1;33m" 
#define LIGHT_GRAY   "\033[0;37m" 
#define WHITE        "\033[1;37m"

typedef struct
{
    void *ui;
    void *next;
    
} render_queue_node;

typedef struct
{
    void *head;
    void *tail;
   
    uint32_t len;

} render_queue;


int render_insert_ui(render_queue *queue, void* ui)
{
    render_queue_node *insert = 0;
    void *cur = queue->head;
    layout *l = 0; 
    layout *tl = 0;

    if(queue == 0 || queue->len >= MAX_QUEUE_LENGTH || !ui_valid(ui))
    {
        return RT_ERROR;
    }

    insert = (render_queue_node*) malloc(sizeof(render_queue_node));
    insert->ui = ui;
    insert->next = 0;


    if(queue->head == 0)
    {
        queue->head = queue->tail = insert;
        queue->len ++;
        return RT_OK;
    }

    ui_get_layout(&l, ui);
    while (cur->next)
    {
        ui_get_layout(&tl, cur->next->ui);
        if(l->_z > tl->_z || l->_y < tl->_y || (l->_y == tl->_y && l->_x < tl->_x))
            break;
        cur = cur->next;
    }

    insert->next = cur->next;
    cur->next = insert;
    queue->tail = len == 1 ? cur->next : queue->tail;
    len ++;

    return RT_OK;
}

int render_remove_ui(render_queue *queue, void* ui)
{
    void* cur = queue->head;
    void* del = cur;

    if(cur == ui)
    {
        queue->head = queue->head->next;
        queue->tail = queue->head == 0 ? 0 : queue->tail;
        free(del);
        return RT_OK;
    }

    while (cur)
    {
        if (cur->next == ui)
        {
            del = cur->next;
            cur->next = cur->next->next;
            free(del);
            return RT_OK;
        }
        cur = cur->next;
    }

    return RT_ERROR;

}

int render_progress(screen *s, ui_progress *ui, paint *pt)
{
    uint8_t *canvas = s->buf;
    layout *l = ui->_layout;
}
