#include "hal/general_command.h"
#include "hal/gpio.h"
#include "hal/ultrasonic.h"
#include <pthread.h>

static bool shutdown = false;
pthread_t ultrasonicDetectorThread;

long double distance_in_cm = 0;

static void *updateUltrasonicDetector(void *args)
{
    (void)args;

    while (!shutdown)
    {

        distance_in_cm = get_distance_cm();
        if (distance_in_cm < 50)
        {
            printf("Motion Detected\n");
        }
        else
        {
            printf("Distance: %.1Lfcm\n", distance_in_cm);
        }
        sleepForMs(10);
    }
    return NULL;
}

void initializeUltrasonicDetector()
{
    return;
}

void createUltrasonicDetectorThread()
{
    pthread_create(&ultrasonicDetectorThread, NULL, updateUltrasonicDetector, NULL);
}

void joinUltrasonicDetectorThread()
{
    pthread_join(ultrasonicDetectorThread, NULL);
}

void shutdownUltrasonicDetector()
{
    shutdown = true;
}
