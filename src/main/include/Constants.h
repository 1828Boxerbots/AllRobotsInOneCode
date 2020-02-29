/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/I2C.h>
#include <frc/SPI.h>

/**
 *  We have a strict naming policy for our constants.
 * 
 *  For ports, the general rule is that you have the type, position, name, then the Robot it's on.
 *  For example:
 *  
 *  constexpr int type_(position)Name_Robot = 0;
 * 
 *  This rule applies to all motors and sensors, although there are a few exceptions.
 *  Most notably, I2C and SPI have enumerated port types, and must be static constexpr autos.
 *  For example:
 * 
 *  static constexpr auto SPI_GYRO_ROCKY = frc::SPI::Port::kOnboard;
 *  static constexpr auto I2C_LIDAR_LAIKA = frc::I2C::Port::kMXP;
 * 
 *  If the constant is not a port, it does not follow those rules exactly.
 *  So long as the name includes the purpose of the constant, it's fine.
 * 
 *  Always comment what robot the port refers to or which general purpose of the constant above it.
 *  Types: I2C, SPI, PWM, DIO, ANG (analog), RLY (relay), and USB.
 *  
 *  Finally, CONSTANTS MUST BE IN ALL CAPS.
 */


//Controllers
constexpr int USB_CONTROLLER_ONE         = 0;
constexpr int USB_CONTROLLER_TWO         = 1;

//Cameras
constexpr int USB_CAMERA_ONE             = 0;
constexpr int USB_CAMERA_TWO             = 1;

//Encoder Types
constexpr int k1X = 0;
constexpr int k2X = 1;
constexpr int k4X = 2;

//Rocky
constexpr int PWM_LEFTMOTOR_ROCKY        = 2;
constexpr int PWM_RIGHTMOTOR_ROCKY       = 3;
constexpr int PWM_TURRETMOTOR_ROCKY      = 4;
constexpr int PWM_SHOOTMOTOR_ROCKY       = 5;
constexpr int PWM_LOADMOTOR_ROCKY        = 9;
constexpr int DIO_LEFTENCODER_ROCKY_ONE  = 8;
constexpr int DIO_LEFTENCODER_ROCKY_TWO  = 9;
constexpr int DIO_RIGHTENCODER_ROCKY_ONE = 0;
constexpr int DIO_RIGHTENCODER_ROCKY_TWO = 1;

//Laika
constexpr int PWM_LEFTMOTOR_LAIKA        = 6;
constexpr int PWM_RIGHTMOTOR_LAIKA       = 2;

//Kurgan
constexpr int PWM_LEFTMOTOR_KURGAN_ONE   = 1;
constexpr int PWM_LEFTMOTOR_KURGAN_TWO   = 2;
constexpr int PWM_RIGHTMOTOR_KURGAN_ONE  = 3;
constexpr int PWM_RIGHTMOTOR_KURGAN_TWO  = 4;
constexpr int PWM_LOADMOTOR_KURGAN       = 0;
constexpr int PWM_SHOOTER_KURGAN_ONE     = 6;
constexpr int PWM_SHOOTER_KURGAN_TWO     = 5;
constexpr int PWM_SHOOTER_KURGAN_THREE   = 7;
constexpr int PWM_SHOOTER_KURGAN_FOUR    = 8;

//SLAL - Sir-Lifts-A-Lot
constexpr int PWM_LEFTMOTOR_SLAL         = 0;
constexpr int PWM_RIGHTMOTOR_SLAL        = 1;
constexpr int PWM_ARM_SLAL_ONE           = 2;
constexpr int PWM_ARM_SLAL_TWO           = 3;
constexpr int DIO_TOPSWITCH_SLAL         = 6;
constexpr int DIO_BOTTOMSWITCH_SLAL      = 7;

//Desert View
constexpr int PWM_LEFTMOTOR_DESERTVIEW            = 2;
constexpr int PWM_RIGHTMOTOR_DESERTVIEW           = 1;
constexpr int DIO_PHOTOGATE_DESERTVIEW            = 4;
constexpr int DIO_HALLEFFECT_SWITCH_DESERTVIEW    = 9;
constexpr int DIO_HALLEFFECT_LATCH_DESERTVIEW     = 8;
constexpr int DIO_HALLEFFECT_OMNIPOLAR_DESERTVIEW = 7;
constexpr int ANG_ANALOG_HALLEFFECT_DESERTVIEW    = 3;
constexpr int ANG_ANALOG_PHOTODIODE_DESERTVIEW    = 2;

//LipALoop
constexpr int PWM_RIGHTMOTOR_LIPALOOP = 4;
constexpr int PWM_LEFTMOTOR_LIPALOOP  = 3;
constexpr int PWM_ARMSERVO_LIPALOOP   = 0;
constexpr int PWM_WRISTSERVO_LIPALOOP = 1;
constexpr int PWM_HANDSERVO_LIPALOOP  = 2;

//2020 Robot
constexpr int PWM_LEFTMOTOR_ROBOT2020       = 1;
constexpr int PWM_RIGHTMOTOR_ROBOT2020      = 0;
constexpr int PWM_SHOOTMOTOR_ROBOT2020      = 3;
constexpr int PWM_LOADMOTOR_INTAKE_ROBOT2020= 5;
constexpr int PWM_LOADMOTOR_BOTTOM_ROBOT2020= 4;
constexpr int PWM_LOADMOTOR_TOP_ROBOT2020   = 6;
constexpr int PWM_ARMMOTOR_ROBOT2020        = 7;
constexpr int PWM_SPINNERMOTOR_ROBOT2020    = 8;
constexpr int PWM_HOOKMOTOR_ROBOT2020       = 9;
constexpr int DIO_ARM_ENCODER_ONE_ROBOT2020 = 9;
//constexpr int DIO_ARM_ENCODER_TWO_ROBOT2020 = 3;
constexpr int DIO_SHOOTER_ENCODER_ONE_ROBOT2020 = 4;
constexpr int DIO_SHOOTER_ENCODER_TWO_ROBOT2020 = 5;
constexpr int DIO_PHOTOGATE_ROBOT2020       = 8;
constexpr int DIO_HALLEFFECT_UPPER_ROBOT2020= 7;
constexpr int DIO_HALLEFFECT_LOWER_ROBOT2020= 6;
constexpr int RLY_SPIKE_ROBOT2020           = 1;

//Vision Bounds (Remember, the InRange function is in BGR format)
constexpr int LOW_BLUE   = 64;
constexpr int LOW_GREEN  = 52;
constexpr int LOW_RED    = 141;
constexpr int HIGH_BLUE  = 104;
constexpr int HIGH_GREEN = 75;
constexpr int HIGH_RED   = 211;

//Color Detection Bounds
constexpr double RED_LOW_R     = 0.0;
constexpr double RED_LOW_G     = 0.0;
constexpr double RED_LOW_B     = 0.0;
constexpr double RED_HIGH_R    = 0.0;
constexpr double RED_HIGH_G    = 0.0;
constexpr double RED_HIGH_B    = 0.0;
constexpr double GREEN_LOW_R   = 0.0;
constexpr double GREEN_LOW_G   = 0.0;
constexpr double GREEN_LOW_B   = 0.0;
constexpr double GREEN_HIGH_R  = 0.0;
constexpr double GREEN_HIGH_G  = 0.0;
constexpr double GREEN_HIGH_B  = 0.0;
constexpr double BLUE_LOW_R    = 0.0;
constexpr double BLUE_LOW_G    = 0.0;
constexpr double BLUE_LOW_B    = 0.0;
constexpr double BLUE_HIGH_R   = 0.0;
constexpr double BLUE_HIGH_G   = 0.0;
constexpr double BLUE_HIGH_B   = 0.0;
constexpr double YELLOW_LOW_R  = 0.0;
constexpr double YELLOW_LOW_G  = 0.0;
constexpr double YELLOW_LOW_B  = 0.0;
constexpr double YELLOW_HIGH_R = 0.0;
constexpr double YELLOW_HIGH_G = 0.0;
constexpr double YELLOW_HIGH_B = 0.0;

/**
* The Multiplexer includes Lidar, Color Sensor, and Left distance sensor.
* This is because the two distance sensors have to work together, whereas
* The other sensors can run alone. This configuration works with the multiplexer.
* This is also why the Right Distance Sensor is alone on the MXP.
*
* All frc/I2C calls require that the ports be const rather than constexpr.
* This is also true for SPI ports.
*/
static constexpr auto I2C_PORT_MULTIPLEXER_ROBOT2020 = frc::I2C::Port::kOnboard;
static constexpr auto I2C_PORT_RIGHTDISTANCESENSOR_ROBOT2020 = frc::I2C::Port::kMXP;

// Positions of the sensors on the multiplexer
constexpr int I2C_LINE_LIDAR_ROBOT2020              = 0;
constexpr int I2C_LINE_LEFTDISTANCESENSOR_ROBOT2020 = 1;
constexpr int I2C_LINE_COLORSENSOR_ROBOT2020        = 2;

// Addresses of the individual I2C sensors
constexpr int I2C_ADDR_MULTIPLEXER_ROBOT2020         = 0x70;
constexpr int I2C_ADDR_LIDAR_ROBOT2020               = 0x62;
constexpr int I2C_ADDR_LEFTDISTANCESENSOR_ROBOT2020  = 0x52;
constexpr int I2C_ADDR_RIGHTDISTANCESENSOR_ROBOT2020 = 0x52;
constexpr int I2C_ADDR_COLORSENSOR_ROBOT2020         = 0x52;


//Allowing hardware to be used
//#define NOHW
#define SEND_VIDEO

