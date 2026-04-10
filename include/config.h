#ifndef CONFIG_H
#define CONFIG_H

// Physical Robot Dimensions in mm
#define R    45.1f
#define LJ2  100.0f
#define LJ3  174.0f
#define NUM_LEGS 6

#define SDA_PIN 21
#define SCL_PIN 22
#define BR2_GPIO_PIN 25
#define BR3_GPIO_PIN 26

#define CE_PIN   4 
#define CSN_PIN  5 

#define SCK_PIN  18   
#define MISO_PIN 19 
#define MOSI_PIN 23

const float globalSpeedMultiplier = 0.25;

#endif