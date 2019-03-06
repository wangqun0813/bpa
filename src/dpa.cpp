//
// Created by root on 18-5-2.
//

#include <stdio.h>
#include "cpu/control.h"
#include "mm/peripher.h"
#include "inter/process.h"
#include "net/transfer.h"
#include "proto/interaction.h"
#include "vos_memory.h"
#include "vos_api.h"
#include "vos_common.h"
#include "vos_log.h"
#include "vos_main.h"



extern int interaction_setup(void *arg);
extern int process_setup(void *arg);
extern int peripher_setup(void *arg);
extern int transfer_setup(void *arg);
extern int control_setup(void *arg);

void carcoder_init()
{
    printf("carcoder init\n");
}

int main(int argc, char *argv[]) {
    __vos_init(argc, argv);

    carcoder_init();
    interaction_setup(argv);
    peripher_setup(argv);
    transfer_setup(argv);
    process_setup(argv);
    control_setup(argv);
    vos_test();
    printf("Hello, World!\n");
    return 0;
}