//
// Created by root on 18-5-7.
//

#ifndef CARCODER_VOS_API_H
#define CARCODER_VOS_API_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int __vos_read(int fd, char *buf, int count);
int __vos_open2(const char *pathname, int flags);
void __vos_strncpy(char *dst, const char *src, size_t count);
void __vos_memset(void *data, int size);
double __vos_atof(const char *s);
int __vos_strlen(const char *s);
void __vos_close(int fd);

#endif //CARCODER_VOS_API_H
