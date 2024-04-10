#include "hal/temperature_sensor.h"
#include "hal/general_command.h"
#include "hal/capture.h"

#include "hal/button.h"
#include "hal/servo.h"
#include "hal/led.h"

#include "hal/ultrasonic.h"
#include "ultrasonic_detector.h"
#include "button_locker.h"
#include "udp.h"

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

pthread_mutex_t shutdownMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t shutdownCond = PTHREAD_COND_INITIALIZER;

void createThreads()
{
    // createTemperatureSensorThread();

    // initialize_led();
    // initialize_button();
    // initializeUltrasonic();

    // create_button_thread();
    // createUltrasonicThread();
     createUltrasonicDetectorThread();
    // createButtonLockerThread();

    // openConnectionT();
    // open_device();
    // init_device();
    // start_capturing();
    // mainloop();

    createUDPThread();

}

void joinThreads()
{
    // shutdownTemperatureSensor();

    // shutdown_button();
    // shutdownButtonLocker();
    // shutdownUltrasonic();
    // shutdownUltrasonicDetector();

    // join_button_thread();
    // joinButtonLockerThread();
    // joinUltrasonicThread();
    // joinUltrasonicDetectorThread();

    // stop_capturing();
    // uninit_device();
    // close_device();
    // fprintf(stderr, "\n");
    // closeConnectionT();

    joinUDPThread();
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