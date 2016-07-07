/*
 *  Copyright (C) 2015 YunOS Project. All rights reserved.
 */

#ifndef ID2_HTTP_H
#define ID2_HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#define ID2_GET_SEED     "/getSeed"
#define ID2_ACTIVATE_DEV "/returnId2"

int http_get_seed(const char *func, const char *arg, char *seed);
int http_get_seed_uv(char *func, char *arg, char *seed,
                     void (*cb)(const char *seed));
int http_activate_dev(const char *func, const char *arg);

#ifdef __cplusplus
}
#endif

#endif
