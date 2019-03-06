//
// Created by root on 18-5-7.
//

#ifndef CARCODER_PERIPHER_GPS_H
#define CARCODER_PERIPHER_GPS_H

#define GPS_COM_NAME "/dev/ttymxc3"
#define BOUND_RATE_9600 9600
#define BOUND_RATE_19200 19200
#define BOUND_RATE_38400 38400
typedef struct
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
}date_time;

typedef struct{
    date_time D;
    char status;
    double	latitude;   //纬度
    double longitude;  //经度
    char NS;           //南北极
    char EW;           //东西
    double speed;      //速度
    double high;       //高度
    int  num;//
}gps_info;

int gps_read_sermios(int fd);
int gps_set_termios(void);
void gps_close(int fd);
#endif //CARCODER_PERIPHER_GPS_H
