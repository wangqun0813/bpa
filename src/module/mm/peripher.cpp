//
// Created by root on 18-5-2.
//

#include <stdio.h>
#include "vos_common.h"
#include "mm/peripher.h"
#include "mm/peripher_gps.h"


int peripher_setup(void *arg){
    int fd;

    __CALL_RET_(gps_set_termios(), fd);
    __CALL_(gps_read_sermios(fd));
    gps_close(fd);

    return 0;
}