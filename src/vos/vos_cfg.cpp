//
// Created by root on 18-5-3.
//
#include <stdio.h>
#include "vos_cfg.h"


int interaction_setup(void *arg);
int process_setup(void *arg);
int peripher_setup(void *arg);
int transfer_setup(void *arg);
int control_setup(void *arg);

extern void carcoder_init(void);

module_cfg_t interaction_cfg_g = {
        MODULE_ID_1, interaction_setup
};

module_cfg_t process_cfg_g = {
        MODULE_ID_2,  process_setup
};

module_cfg_t peripher_cfg_g = {
        MODULE_ID_3, peripher_setup
};

module_cfg_t transfer_cfg_g = {
        MODULE_ID_4, transfer_setup
};

module_cfg_t control_cfg_g = {
        MODULE_ID_5, control_setup
};

thread_cfg_t thread_cfgs_g[] = {
        {THREAD_ID_1, THREAD_TYPE_MODULE, NULL, NULL, &interaction_cfg_g}, //进程通信模块
        {THREAD_ID_2, THREAD_TYPE_MODULE, NULL, NULL, &process_cfg_g}, //数据处理模块
        {THREAD_ID_3, THREAD_TYPE_MODULE, NULL, NULL, &peripher_cfg_g}, //外设模块
        {THREAD_ID_4, THREAD_TYPE_MODULE, NULL, NULL, &transfer_cfg_g},  //TCP通信模块
        {THREAD_ID_5, THREAD_TYPE_MODULE, NULL, NULL, &control_cfg_g} //控制模块
};

process_cfg_t process_cfgs_g[] = {
        {PROCESS_ID_1, "carcoder.exe", "carcoder.ini", carcoder_init, NULL, 5, thread_cfgs_g}
};


node_cfg_t node_cfg_g = {
        NODE_ID_1, process_cfgs_g, 1
};