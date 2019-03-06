//
// Created by root on 18-5-7.
//

#ifndef CARCODER_VOS_COMMON_H
#define CARCODER_VOS_COMMON_H

typedef unsigned int uint32_t ;
typedef unsigned char uint8_t ;
typedef unsigned short uint16_t ;
typedef signed int int32_t ;
typedef signed short int16_t;
typedef signed char int8_t;

#include "vos_log.h"

#define __CHECK_(exp) \
    do{if(exp){__vos_err("%s\n", #exp); return -1;}}while(0)

#define __CHECK_JMP_(exp, jmp)\
    do{if(exp){__vos_err("%s\n", #exp); goto jmp;}}while(0)

#define __CALL_TRACE_(function)\

#define __CALL_(function)\
do{\
    int __check_ret = function; \
    if (0 > __check_ret){\
        __vos_err("%s\n", #function);\
    }\
}while(0)

#define __CALL_JMP_(function, jmp)\
do{\
    int __check_ret = function; \
    if (0 > __check_ret){\
        __vos_err("%s\n", #function);\
        goto jmp;\
    }\
}while(0)

#define __CALL_RET_(function, ret)\
do{\
    ret = function;\
    if (0 > ret){\
        __vos_err("%s\n", #function);\
        return -1;\
    }\
    return ret;\
}while(0)


#endif //CARCODER_VOS_COMMON_H
