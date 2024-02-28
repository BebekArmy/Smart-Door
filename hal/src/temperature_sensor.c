#include "hal/temperature_sensor.h"

#include <stdlib.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <pthread.h>

#define A2D_FILE_VOLTAGE1  "/sys/bus/iio/devices/iio:device0/in_voltage1_raw" 

static bool shutdown = false;
static int temperatureReading = 0;
static pthread_t temperatureSensorThread;


void *updateTemperatureReading(void *args) { 
    // Open file 
    (void)args;
    while(!shutdown){
        FILE *f = fopen(A2D_FILE_VOLTAGE1, "r"); 
        if (!f) { 
            printf("ERROR: Unable to open voltage input file. Cape loaded?\n"); 
            printf("       Check /boot/uEnv.txt for correct options.\n"); 
            exit(-1); 
        } 
        // Get reading 
        
        int itemsRead = fscanf(f, "%d", &temperatureReading); 
        //print itemsRead
        if (itemsRead < 0) { 
                printf("ERROR: Unable to read values from voltage input file.\n"); 
                exit(-1); 
        } 
        fclose(f); 
    }
    
    return NULL;
}

int getTemperatureReading() { 
    return temperatureReading; 
}

double getCelcius(){
    return temperatureReading;
}

void createTemperatureSensorThread() {
    pthread_create(&temperatureSensorThread, NULL, updateTemperatureReading, NULL);
}

void shutdownLightSensor() { 
    shutdown = true; 
    pthread_join(temperatureSensorThread, NULL);
}