// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include "hal/temperature_sensor.h"
#include "hal/general_command.h"
#include "hal/capture.h"
#include "shutdown.h"

#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

int main()
{
    printf("Starting streaming\n");

    createThreads();
    waitShutdown();
    joinThreads();
    
    return 0;
}

