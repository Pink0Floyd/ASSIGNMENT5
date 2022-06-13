/**
* \file base.h
* \brief Base file
*
* This file contain the basic includes and macros for general porpouse
*
* \author Filipe Loureiro & Miguel Silva
* \date 13/06/22
* \version 5.1
* \bug No bugs detected
*/

#ifndef _BASE_H
#define _BASE_H

#include <zephyr.h>
#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <sys/printk.h>
#include <sys/__assert.h>
#include <string.h>
#include <timing/timing.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <drivers/adc.h>
#include <hal/nrf_saadc.h>
#include <drivers/pwm.h>
//Console use
#include <console/console.h>

float saturation(float value,float min,float max);

#endif