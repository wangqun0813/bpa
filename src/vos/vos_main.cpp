//
// Created by root on 18-5-3.
//

#include <stdio.h>
#include "vos_cfg.h"
#include "vos_main.h"
#include "vos_log.h"
#include "vos_common.h"

extern node_cfg_t node_cfg_g;


int __vos_main(node_cfg_t *vos_cfg){
    return 0;
}



int __process_main(int argc, char *argv[]){

    node_cfg_t *node_cfg = &node_cfg_g;

    __vos_log_init(VOS_LOG_CONSOLE, VOS_LOG_LEVEL_WARN);

    return __vos_main(node_cfg);
}


int __vos_init(int argc, char *argv[])
{
    return __process_main(argc, argv);
}


