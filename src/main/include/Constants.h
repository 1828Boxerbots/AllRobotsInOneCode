/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

//Controllers
constexpr int USB_CONTROLLER_ONE        = 0;
constexpr int USB_CONTROLLER_TWO        = 1;

//Rocky
constexpr int PWM_LEFTMOTOR_ROCKY       = 2;
constexpr int PWM_RIGHTMOTOR_ROCKY      = 3;
constexpr int PWM_SHOOTMOTOR_ROCKY      = 5;
constexpr int PWM_TURRETMOTOR_ROCKY     = 4;
constexpr int PWM_LOADMOTOR_ROCKY       = 9;

//Laika
constexpr int PWM_LEFTMOTOR_LAIKA_ONE   = 1;
constexpr int PWM_LEFTMOTOR_LAIKA_TWO   = 2;
constexpr int PWM_RIGHTMOTOR_LAIKA_ONE  = 3;
constexpr int PWM_RIGHTMOTOR_LAIKA_TWO  = 4;

//Kurgan
constexpr int PWM_LEFTMOTOR_KURGAN_ONE  = 1;
constexpr int PWM_LEFTMOTOR_KURGAN_TWO  = 2;
constexpr int PWM_RIGHTMOTOR_KURGAN_ONE = 3;
constexpr int PWM_RIGHTMOTOR_KURGAN_TWO = 4;
constexpr int PWM_LOADMOTOR_KURGAN      = 0;
constexpr int PWM_SHOOTER_KURGAN_ONE    = 6;
constexpr int PWM_SHOOTER_KURGAN_TWO    = 5;
constexpr int PWM_SHOOTER_KURGAN_THREE  = 7;
constexpr int PWM_SHOOTER_KURGAN_FOUR   = 8;

//SLAL - Sir-Lifts-A-Lot
constexpr int PWM_LEFTMOTOR_SLAL        = 0;
constexpr int PWM_RIGHTMOTOR_SLAL       = 1;
constexpr int PWM_ARM_SLAL_ONE          = 2;
constexpr int PWM_ARM_SLAL_TWO          = 3;
constexpr int DIO_TOPSWITCH_SLAL        = 6;
constexpr int DIO_BOTTOMSWITCH_SLAL     = 7;

//Desert View
constexpr int PWM_LEFTMOTOR_DESERTVIEW = 2;
constexpr int PWM_RIGHTMOTOR_DESERTVIEW = 1;


//Allowing hardware to be used
//#define NOHW

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */
