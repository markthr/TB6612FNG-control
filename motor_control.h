#ifndef __MOTOR_CONTROL__
#define __Motor_CONTROL__

/*****************************************************************************************
                                     +-------------+
                                     |  TB6612FNG  |
                                   <-|VM       PWMA|->
                                   <-|VCC      AIN2|->
                                   <-|GND      AIN1|->
                                   <-|A01      STBY|->
                                   <-|A02      BIN1|->
                                   <-|B02      BIN2|->
                                   <-|B01      PWMB|->
                                   <-|GND       GND|->
                                     |  spark fun  |
                                     +-------------+

Purpose:    This code provides an interface for controlling reversable DC motors through 
            through the TB6612FNG chip with an arduino. Motor control is abstracted
            for ease of use although lower level functions are still available to be
            used.
           
TB6612FNG:  This chip integrates an H-bridge with PWM control over two seperate motor
            channels.

Usage:      To begin,        

*****************************************************************************************/
typedef struct tb6612fng {
    int AIN1;
    int AIN2;
    int PWMA;
    int AO1;
    int AO2;

    int BI1;
    int BI2;
    int PWMB;
    int BO1; 
    int BO2;
} M_ctrl;

void set_duty_a(float f);
void set_duty_b(float f);


typedef enum {
    FWD,
    BWD,
    BRK,
    OFF
} M_state

void set_mode(
