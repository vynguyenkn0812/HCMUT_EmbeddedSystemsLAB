#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdio.h>

#define QUEUE_SIZE          10
#define QUEUE_WAITS         200
#define QUEUE_SEND_WAITS    300
#define QUEUE_SEND_DELAY    500

#define REJECTS_TIMES       3

typedef enum  
{
    eMotoSpeed,      // Can Bus Task
    eSpeedSetPoint,  // HMI
    eOtherTask,
}ID_t;

typedef struct {
    ID_t eDataID;  
    int32_t lDataValue;
    char ctaskName[20];
    int8_t rejectTimes;
} Data_t;

#endif 