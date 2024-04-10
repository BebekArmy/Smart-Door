#include "hal/temperature_sensor.h"

#include <stdlib.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <pthread.h>

#define A2D_FILE_VOLTAGE1  "/sys/bus/iio/devices/iio:device0/in_voltage1_raw" 
#define A2D_VOLTAGE_REF_V 1.8
#define A2D_MAX_READING 4095

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

static double getTemperatureVoltage() { 
    return (temperatureReading * A2D_VOLTAGE_REF_V) / A2D_MAX_READING; 
}

double getCelciusTemperature(){
    double temperatureVoltage = getTemperatureVoltage();
    return (temperatureVoltage * 1000 - 500)/10;
}

double getFarhenheitTemperature(){
    return (getCelciusTemperature() * 9/5) + 32;
}

void createTemperatureSensorThread() {
    pthread_create(&temperatureSensorThread, NULL, updateTemperatureReading, NULL);
}

void shutdownTemperatureSensor() { 
    shutdown = true; 
    pthread_join(temperatureSensorThread, NULL);
}