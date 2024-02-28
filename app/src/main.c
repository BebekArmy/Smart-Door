// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.
#include "hal/temperature_sensor.h"
#include "hal/general_command.h"

#include <stdio.h>
#include <stdbool.h>

int main()
{
    
    createTemperatureSensorThread();
    sleepForMs(10);
    //create for loop to 10 to read temperature with sleep of 1 second
    for(int i = 0; i < 10; i++){
        printf("Celcius Temperature: %f\n", getCelciusTemperature());
        sleepForMs(1000);
    }

    shutdownTemperatureSensor();

    return 0;
}