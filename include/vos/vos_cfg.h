//
// Created by root on 18-5-3.
//

#ifndef CARCODER_VOS_CFG_H
#define CARCODER_VOS_CFG_H

#define MAX_PROCESS_ID 2
#define MAX_THREAD_ID 5

#include "vos_common.h"


typedef int(*task_entry_t)(void *arg);
typedef int(*module_entry_t)(void *arg);



typedef enum{
    NODE_ID_1
}NODE_IDS;

typedef enum{
    PROCESS_ID_1 = 10,
    PROCESS_ID_2

}PROCESS_IDS;

typedef enum{
    THREAD_ID_1 = 100,
    THREAD_ID_2,
    THREAD_ID_3,
    THREAD_ID_4,
    THREAD_ID_5
}THREAD_IDS;

typedef enum{
    MODULE_ID_1 = 1000,
    MODULE_ID_2,
    MODULE_ID_3,
    MODULE_ID_4,
    MODULE_ID_5
}MODULE_IDS;


typedef enum{
    THREAD_TYPE_MODULE,
    THREAD_TYPE_TASK,
}THREAD_TYPE;

typedef struct {
    uint32_t task_id; //任务ID
    uint8_t task_type;//任务类型

    task_entry_t entry; //任务操作，回调函数
    void *arg; //参数

    //uint32_t  node_id; //虚拟系统ID
    //uint32_t  process_id; //进程ID
    //uint32_t  thread_id; //线程ID
    //uint32_t  module_id; //模块ID

    //快速查找
    void *thread_info; //线程信息, 目前用于找到ipc通道,后续做成消息路由表,就可以不需要了

}task_info_t;//任务信息


typedef struct
{
    void *thread_info; //线程信息

    uint32_t  module_id;//模块ID
    module_entry_t module_entry;
}module_info_t; //模块信息

typedef struct
{
    void *process_info; //进程信息

    uint32_t  thread_id; //线程ID
    uint8_t   thread_type; //线程类型
    void *handle; //

    //msgQ_t msgQueue;  //消息队列
    //void   *ipcChannel; //进程通道
    void   *msg_poll; //通信控制

//    uint32_t   cpu;

    module_info_t *module_info;
    //   task_info_t   *taskInfo; //任务信息, 对于运行模块的线程, 指向当前任务

    uint8_t   run;
}thread_info_t; //线程信息


typedef struct{
    void *node_info;
    uint32_t process_id;
    void (*init)(void);
    thread_info_t thread_infos[MAX_THREAD_ID+1];
    uint8_t run;

}process_base_info_t;


typedef struct{
    uint32_t node_id;
    process_base_info_t process_infos[MAX_PROCESS_ID+1];
    uint8_t  run;

}node_info_t;


//////////////////////////////////////////////////////////
typedef struct{
    uint32_t module_id;
    module_entry_t module_entry;

}module_cfg_t;

typedef struct {
    uint32_t task_id;
    uint8_t task_type;
    task_entry_t entry;
    void *arg;

}task_cfg_t;//任务配置


typedef struct{
    uint32_t thread_id;
    uint32_t thread_type;
    void *ipc_channel;
    task_cfg_t *task_cfg;
    module_cfg_t *module_cfg;

}thread_cfg_t;


typedef struct{
    uint32_t process_id;
    const char *img;
    const char *config;
    void (*init)(void);
    void *ipc_channel;
    uint32_t thread_num;
    thread_cfg_t *thread_cfgs;

}process_cfg_t;


typedef struct{
    uint32_t  node_id;
    process_cfg_t  *process_cfgs;
    uint32_t  process_num;

}node_cfg_t;

#endif //CARCODER_VOS_CFG_H
