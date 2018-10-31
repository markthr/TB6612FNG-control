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
#include <stdint.h>
typedef struct tb6612fng {
    int AIN1;
    int AIN2;
    int PWMA;

    int BIN1;
    int BIN2;
    int PWMB;
} M_ctrl;


typedef enum {
    FWD,
    BWD,
    BRK,
    OFF
} M_state;

/*
* a and b both must contain 3 elements and be of the forms
  a = {AIN1, AIN2, PWMA}
  b = {BIN1, BIN2, PWMB}
*/
void init_m_ctrl(M_ctrl *m, int a[static 3], int b[static 3]);

void write_a(M_ctrl *m, uint8_t duty, M_state state);
void write_b(M_ctrl *m, uint8_t duty, M_state state);

void stop(M_ctrl *m);
void brake(M_ctrl *m);
#endif
