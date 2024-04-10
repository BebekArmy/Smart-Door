#ifndef _ULTRASONIC_DETECTOR_H_
#define _ULTRASONIC_DETECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <time.h>
#include <stdbool.h>

void addEmail(const char *email);
void clearEmails();

void initializeUltrasonicDetector();
void createUltrasonicDetectorThread();
void shutdownUltrasonicDetector();
void joinUltrasonicDetectorThread();



#endif