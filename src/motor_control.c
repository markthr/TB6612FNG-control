#include "motor_control.h"
#include <assert.h>
#include <stdint.h>

/*#include "Arduino.h" /**/

/*
* Helper function which sets the direction pins
*/
void set_state(int p1, int p2, int pwm, M_state state);
void init_m_ctrl(M_ctrl *m, int a[static 3], int b[static 3]){
    int i;
    assert(sizeof(a)/sizeof(int) == 3);
    assert(sizeof(b)/sizeof(int) == 3);
    
    *m = {a[0], a[1], a[2], b[1], b[2], b[3]};
    
    for(i = 0; i < 3; i++){
        pinMode(a[i], OUTPUT);
        pinMode(b[i], OUTPUT);
    }
}

void write_a(M_ctrl *m, uint8_t duty, M_state state){
    analogWrite(m->PWMA, duty);
    set_state(m->AIN1, m->AIN2, m->PWMA, state);
}
void write_b(M_ctrl *m, uint8_t duty, M_state state){
    analogWrite(m->PWMB, duty);
    set_state(m->BIN1, m->BIN2, m->PWMB, state);
}

void stop(M_ctrl *m){
    set_state(m->AIN1, m->AIN2, m->PWMA, OFF);
    set_state(m->BIN1, m->BIN2, m->PWMB, OFF);
}
void brake(M_ctrl *m){
    set_state(m->AIN1, m->AIN2, m->PWMA, BRK);
    set_state(m->BIN1, m->BIN2, m->PWMB, BRK);
}


void set_state(int p1, int p2, int pwm, M_state state){
    switch(state){
        case FWD :
            digitalWrite(p1, LOW);
            digitalWrite(p2, HIGH);
        case BWD :
            digitalWrite(p1, HIGH);
            digitalWrite(p2, LOW);
            break;
        case BRK :
            digitalWrite(p1, HIGH);
            digitalWrite(p2, HIGH);
            /* No break because brake transitions to off.
            * This is because brake relies on shorting the
            * motor which is not sustainable */
        case OFF :
            digitalWrite(p1, LOW);
            digitalWrite(p2, LOW);
            digitalWrite(pwm, HIGH);
            break;
    }
}
