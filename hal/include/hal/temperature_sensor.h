#ifndef _TEMPERATURE_SENSOR_H_
#define _TEMPERATURE_SENSOR_H_

/* Module to initialize and cleanup the light sensor thread.
Supports updating (repeatedly reading in_voltage1_raw) and getting a voltage from the light sensor
in its digital form (e.g. 4095) or real world analog form (e.g. 1.2V).
*/

#include <stdint.h>

int getTemperatureReading();
double getCelcius();
void createTemperatureSensorThread();
void shutdownTemperatureSensor();


#endif