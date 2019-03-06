//
// Created by root on 18-5-7.
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include "mm/peripher_gps.h"
#include "vos_api.h"
#include "vos_common.h"
#include "vos_log.h"

#define USE_BEIJING_TIMEZONE

void gps_close(int fd) {
    __vos_close(fd);
}

int gps_set_termios(void) {
    struct termios terminfo;
    int fd;
    int bound = BOUND_RATE_9600;


    fd = __vos_open2(GPS_COM_NAME, O_RDWR|O_NONBLOCK|O_NOCTTY|O_NDELAY);
    terminfo.c_iflag = IGNPAR;
    terminfo.c_oflag = 0;
    terminfo.c_lflag = 0;
    terminfo.c_cc[VMIN] = 1;
    tcflush(fd, TCIFLUSH);  //clear
    tcsetattr(fd, TCSANOW, &terminfo); //set attr
    return fd;
}

void gps_info_print(gps_info *gpsinfo) {

    printf("%d-%d-%d %d:%d:%d",gpsinfo->D.year, gpsinfo->D.month, gpsinfo->D.day,
        gpsinfo->D.hour, gpsinfo->D.minute, gpsinfo->D.second);
    printf("latitude:%c_%lf, longitude:%c_%lf", gpsinfo->NS,
           gpsinfo->latitude, gpsinfo->EW, gpsinfo->longitude);
    printf("GPS num:%d, high:%lf, speed:%lf\n", gpsinfo->num, gpsinfo->high, gpsinfo->speed);

}

static int get_buf_num(int num, char *str)
{
    int i,j=0;
    int len=__vos_strlen(str);

    __CHECK_(str);

    for(i=0; i<len; i++)
    {
        if(str[i]==',')
            j++;
        if(j==num)
            return i+1;
    }
    return 0;

}

static double get_double_number(char *s) {
    char buf[128];
    int i;

    __CHECK_(s);
    i = get_buf_num(1,s);
    __vos_strncpy(buf,s,i);

    buf[i] = 0;
    return __vos_atof(buf);
}

static void BTC(date_time *gps_d) {

    gps_d->second++;
    if(gps_d->second>59)
    {
        gps_d->second=0;
        gps_d->minute++;
        if(gps_d->minute>59)
        {
            gps_d->minute=0;
            gps_d->hour++;
        }
    }
    gps_d->hour+=8;
    if(gps_d->hour>23)
    {
        gps_d->hour-=24;
        gps_d->day+=1;
        if(gps_d->month==4 ||
           gps_d->month==6 ||
           gps_d->month==9 ||
           gps_d->month==11 )
        {
            if(gps_d->day>30)
            {
                gps_d->day=1;
                gps_d->month++;
            }
        }
        else
        {
            if(gps_d->day>31)
            {
                gps_d->day=1;
                gps_d->month++;
            }
        }
        if(gps_d->year % 4 == 0 )
        {//
            if(gps_d->day > 29 && gps_d->month ==2)
            {
                gps_d->day=1;
                gps_d->month++;
            }
        }
        else
        {
            if(gps_d->day>28 &&gps_d->month ==2)
            {
                gps_d->day=1;
                gps_d->month++;
            }
        }
        if(gps_d->month>12)
        {
            gps_d->month-=12;
            gps_d->year++;
        }
    }
}


static int gps_parse_data(char *mbuf, gps_info *gpsinfo) {
    int temp = 0;
    char *buf = mbuf;
    char c = buf[5];

    __CHECK_(mbuf);
    __CHECK_(gpsinfo);
    if (c == 'A') {//"$GPGGA"
        gpsinfo->high = get_double_number(&buf[get_buf_num(9,buf)]);
        gpsinfo->num = (buf[get_buf_num(7,buf)]-'0')*10;
    }
    if(c=='C')//"GPRMC"
    {
        gpsinfo->D.hour   =(buf[ 7]-'0')*10+(buf[ 8]-'0');
        gpsinfo->D.minute =(buf[ 9]-'0')*10+(buf[10]-'0');
        gpsinfo->D.second =(buf[11]-'0')*10+(buf[12]-'0');
        temp = get_buf_num(9, buf);
        gpsinfo->D.day    =(buf[temp+0]-'0')*10+(buf[temp+1]-'0');
        gpsinfo->D.month  =(buf[temp+2]-'0')*10+(buf[temp+3]-'0');
        gpsinfo->D.year   =(buf[temp+4]-'0')*10+(buf[temp+5]-'0')+2000;
        gpsinfo->status   =buf[get_buf_num(2,buf)];
        gpsinfo->latitude =get_double_number(&buf[get_buf_num(3,buf)]);
        gpsinfo->NS       =buf[get_buf_num(4,buf)];
        gpsinfo->longitude=get_double_number(&buf[get_buf_num(5,buf)]);
        gpsinfo->EW       =buf[get_buf_num(6,buf)];
    #ifdef USE_BEIJING_TIMEZONE
            BTC(&gpsinfo->D);
    #endif
    }
    return 0;
}


int gps_read_sermios(int fd) {
    int i = 0, j = 0, nread = 0;
    bool valid_flag = false;
    char c;
    char buf[1024] = {0};
    char m_buf[1024] = {0};
    gps_info gpsinfo;

    __CHECK_(fd);
    __vos_memset((void *)&gpsinfo, sizeof(gpsinfo));

    nread = __vos_read(fd, &c, 1);
    if(nread > 0) {
        buf[i++] = c;
        for(j=0; j<sizeof(buf); j++) {
            nread = __vos_read(fd, &c, 1);
            if(nread > 0) {
                buf[i++] = c;
                j++;
                if (c == '\n') {
                    __vos_strncpy(m_buf, buf, i);
                    i = 0;
                    j = 0;
                    valid_flag = true;
                    break;
                }
            }
        }
        if(j >= sizeof(buf)) {
            __vos_err("baund rate error\n");
        }
    }
    if (valid_flag == true) {
        gps_parse_data(m_buf, &gpsinfo);
        gps_info_print(&gpsinfo);
    }
    return 0;
}





