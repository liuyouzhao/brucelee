typedef struct
{
    uint8_t _bg_color;
    uint8_t _color;
    
    uint8_t _content;

} paint;


int pt_create(paint **p, uint8_t bg, uint8_t color, uint8_t cont)
{
    *p = (paint*) malloc( sizeof(paint) );

    if ( *p == 0 )
    {
        return RT_ERROR;
    }

    *p->_bg_color = bg;
    *p->_color = color;
    *p->_content = cont;

    return RT_OK;
}
