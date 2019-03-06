//
// Created by root on 18-5-7.
//


#ifndef CARCODER_VOS_LOG_H
#define CARCODER_VOS_LOG_H

#include <stdio.h>
#include "vos_cfg.h"
#include "vos_common.h"

#define VOS_LOG_LOG_FILE  (1UL<<0)
#define VOS_LOG_CONSOLE   (1UL<<1)
#define VOS_LOG_USER_FILE (1UL<<2)

#define VOS_LOG_LEVEL_NONE  (0UL)
#define VOS_LOG_LEVEL_ERR   (1UL)
#define VOS_LOG_LEVEL_WARN  (2UL)
#define VOS_LOG_LEVEL_INFO  (3UL)
#define VOS_LOG_LEVEL_DEBUG (4UL)

extern uint32_t vos_log_ctrl_g;
extern uint32_t vos_log_level_g;
extern FILE *vos_log_file_g;

#define __vos_log(fmt, args...) \
do{\
    if ((vos_log_ctrl_g & VOS_LOG_CONSOLE) != 0){\
        printf("[%s, %d]: "fmt, __FILE__, __LINE__, ##args);\
    }\
    if ((vos_log_ctrl_g & VOS_LOG_LOG_FILE) != 0){\
        fprintf(vos_log_file_g, "[%s, %d]: "fmt, __FILE__, __LINE__, ##args);\
    }\
}while(0)

#define __vos_err(fmt, args...)\
do{\
    if (vos_log_level_g >= VOS_LOG_LEVEL_ERR)\
        __vos_log("<err> "fmt, ##args);\
}while(0)

#define __vos__warn(fmt, args...)\
do{\
    if (vos_log_level_g >= VOS_LOG_LEVEL_WARN)\
        __vos_log("<warn> "fmt, ##args);\
}while(0);

#define __vos_info(fmt, args...)\
do{\
    if (vos_log_level_g >= VOS_LOG_LEVEL_INFO)\
        __vos_log("<info> "fmt, ##args);\
}while(0);

#define __vos_debug(fmt, args...)\
do{\
    if (vos_log_level_g >= VOS_LOG_LEVEL_DEBUG)\
        __vos_log("<debug> "fmt, ##args);\
}while(0);

int __vos_log_init(uint32_t log_ctrl, uint32_t log_level);
void __vos_log_ctrl(uint32_t log_ctrl);

#endif //CARCODER_VOS_LOG_H
