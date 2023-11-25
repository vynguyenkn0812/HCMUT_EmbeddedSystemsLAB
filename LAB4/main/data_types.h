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
    eMotoSpeed = 0,      // Can Bus Task
    eSpeedSetPoint,  // HMI
    eSPISetMode,     // SPI
    Other,
}ID_t;

struct QueueData {
    ID_t eRequestID;
    char cMessage[20];
    uint32_t lDataValue;
    int8_t rejectTimes;
};

struct TaskType {
    ID_t eDataID;
    char cTaskName[20];
};

#endif