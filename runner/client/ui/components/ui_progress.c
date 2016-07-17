#include <stdio.h>
#include "defs.h"


#define UI_PROGRESS_DEFAULT_CAPACITY 100

/**
 * ui progress, for show a progress bar, counting procedure
 * all ui must include _layout pointer as first member.
 */
typedef struct
{
    void* _layout;
    unsigned int _cur_pro;
    unsigned int _max_pro;

    unsigned int _type;
} ui_progress;


int ui_progress_init(ui_progress **uipro)
{
    if ( uipro == 0 )
        return RT_ERROR;
    
    *uipro = (ui_progress*) malloc(sizeof(ui_progress));
    memset(*uipro->_max_pro, 0, sizeof(ui_progress));
    *uipro->_max_pro = UI_PROGRESS_DEFAULT_CAPACITY;
    *uipro->_type = UI_TYPE_PROGRESS;

    return RT_OK;
}

int ui_progress_uninit(ui_progress **uipro)
{
    if ( uipro == 0 )
        return RT_ERROR;

    free(*uipro);
}        


int ui_progress_uppro(ui_progress *uipro, const int pro)
{
    if ( !uipro )
    {
        return RT_ERROR;
    }

    uipro->_cur_pro = pro;
    return RT_OK;
}

int ui_progress_is_complete(ui_progress *uipro)
{
    return uipro->_cur_pro >= uipro->_max_pro;
}

int ui_progress_accomplish(ui_progress *uipro)
{
    uipro->_cur_pro = uipro->_max_pro;
    return RT_OK;
}
