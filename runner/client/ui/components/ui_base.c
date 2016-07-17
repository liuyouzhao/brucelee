#include <defs.h>

#define UI_TYPE_PROGRESS 0x0001


int ui_set_layout(void* ui, void* l)
{
    *((layout**)ui) = l;
    return RT_OK;
}

int ui_get_layout(layout** l, void* ui)
{
    *l = *((layout**)ui);
    return RT_OK;
}


int ui_valid(void* ui)
{
    layout *l = *((layout**)ui);
    return l;
}
