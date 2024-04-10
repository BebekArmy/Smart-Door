#include "hal/general_command.h"
#include "hal/gpio.h"
#include "hal/ultrasonic.h"
#include <pthread.h>
#include <time.h>

#define MAX_EMAIL_LENGTH 100
#define EMAIL_COUNT 5

static bool shutdown = false;
pthread_t ultrasonicDetectorThread;

char emails[EMAIL_COUNT][MAX_EMAIL_LENGTH];

long double distance_in_cm = 0;

void addEmail(const char *email) {
    for (int i = 0; i < EMAIL_COUNT; i++)
    {
        if (strlen(emails[i]) == 0)
        {
            strcpy(emails[i], email);
            break;
        }
    }
}

void clearEmails() {
    for (int i = 0; i < EMAIL_COUNT; i++)
    {
        memset(emails[i], 0, MAX_EMAIL_LENGTH);
    }
}

void sendWarningEmail() {
    //get current time and compose the warning message using the current time
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char message[100];
    sprintf(message, "Someone is at your door at %d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    for (int i = 0; i < EMAIL_COUNT; i++)
    {
        if (strlen(emails[i]) != 0)
        {
            sendEmail("Smart Door Warning", message, emails[i]);
        }
    }
    
}


static void *updateUltrasonicDetector(void *args)
{
    (void)args;


    while (!shutdown)
    {

        // distance_in_cm = get_distance_cm();
        // if (distance_in_cm < 50)
        // {
        //     printf("Motion Detected\n");
        // }
        // else
        // {
        //     printf("Distance: %.1Lfcm\n", distance_in_cm);
        // }
        // sleepForMs(10);
        //sendWarningEmail();
        sleepForMs(5000);
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
