//
// Created by root on 18-5-7.
//
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "vos_api.h"
#include "vos_common.h"


int __vos_open2(const char *pathname, int flags)
{
    int fd;
    __CALL_RET_(open(pathname, flags), fd);
}

int __vos_read(int fd, char *buf, int count) {
    return read(fd, buf, count);
}

void __vos_close(int fd) {
    close(fd);
}

void __vos_strncpy(char *dst, const char *src, size_t count) {
    strncpy(dst, src, count);
}

void __vos_memset(void *data, int size){
    memset(data, 0, size);
}

double __vos_atof(const char *s) {
    return atof(s);
}

int __vos_strlen(const char *s) {
    return strlen(s);
}