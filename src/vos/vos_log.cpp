//
// Created by root on 18-5-7.
//

#include "vos_log.h"
#include "vos_common.h"

uint32_t  vos_log_ctrl_g   = VOS_LOG_CONSOLE;
uint32_t  vos_log_level_g  = VOS_LOG_LEVEL_DEBUG;
FILE  *vos_log_file_g  = NULL;



void __vos_log_ctrl(uint32_t log_ctrl) {
    vos_log_ctrl_g = log_ctrl;
}

int __vos_log_init(uint32_t log_ctrl, uint32_t log_level) {
    vos_log_ctrl_g = log_ctrl;
    vos_log_level_g = log_level;

    vos_log_file_g = fopen("vos.log", "wt");
    if(vos_log_file_g == NULL) {
        printf("open vos.log fail.\n");
        return -1;
    }
    return 0;
}
