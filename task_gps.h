#ifndef _TASK_GPS_H_
#define _TASK_GPS_H_


#include "FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "gps.h"

#define TASK_GPS_STACK_SIZE (256)





extern GPSData gpsData;

void taskGps(void *pData);

double gpsToDouble(bool neg, int16_t bp, int16_t ap);

#ifdef __cplusplus
}
#endif


#endif
