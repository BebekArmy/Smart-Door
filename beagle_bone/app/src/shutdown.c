#include "hal/temperature_sensor.h"
#include "hal/general_command.h"
#include "hal/capture.h"

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

pthread_mutex_t shutdownMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t shutdownCond = PTHREAD_COND_INITIALIZER;

void createThreads()
{
    //createTemperatureSensorThread();

    openConnectionT();
    open_device();
    init_device();
    start_capturing();
    mainloop();
}

void joinThreads()
{
    //shutdownTemperatureSensor();

    stop_capturing();
    uninit_device();
    close_device();
    fprintf(stderr, "\n");
    closeConnectionT();
}

void waitShutdown()
{
    pthread_mutex_lock(&shutdownMutex);
    pthread_cond_wait(&shutdownCond, &shutdownMutex);
    pthread_mutex_unlock(&shutdownMutex);
}

void signalShutdown()
{
    pthread_mutex_lock(&shutdownMutex);
    pthread_cond_signal(&shutdownCond);
    pthread_mutex_unlock(&shutdownMutex);
}