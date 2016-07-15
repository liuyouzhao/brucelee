#include <stdio.h>
#include <defs.h>

typedef struct {
    uint32_t _x;
    uint32_t _y;

    uint32_t _w;
    uint32_t _h;    

    uint32_t _z;

} layout;

int layout_create(layout **l)
{
    *l = (layout*) malloc( sizeof(layout) );

    if ( *l == 0 )
    {
        return RT_ERROR;
    }

    memset(*l, 0, sizeof(layout));

    return RT_OK;
}
