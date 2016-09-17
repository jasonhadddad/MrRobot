#include "main.h"
#include "motor.h"

volatile unsigned int stepState = 0;

void moveCW(unsigned int numberOfSteps) {   //CW Routine
        
    volatile unsigned int i = 0;                                                         
    volatile unsigned int stepsRemaining = numberOfSteps;
    while (i < numberOfSteps) {                                             
        if (stepState == 0) {                                                  
            PORTC = STEP0;                                                     
        }
        else if (stepState == 1) {                                           
            PORTC = STEP1;
        }
        else if (stepState == 2) {                                              
            PORTC = STEP2; 
        }
        else if (stepState == 3) {
            PORTC = STEP3;
        }
        else if (stepState == 4) {
            PORTC = STEP4;
        }
        else if (stepState == 5) {
            PORTC = STEP5;
        }
        else if (stepState == 6) {
            PORTC = STEP6;
        }
        else if (stepState == 7) {
            PORTC = STEP7;
        }  
        __delay_ms(5);    
        
        i++;                                                                   
        stepState++;       
        if (stepState > 7) {                                                 
            stepState = 0;                                                     
        }
    }
    }

void moveCCW(unsigned int numberOfSteps) { //CCW routine
      
    volatile unsigned int i = 0;                                                         
    volatile unsigned int stepsRemaining = numberOfSteps;
    while (i < numberOfSteps) {              
        
        if (stepState == 0) {                                                  
            PORTC = STEP0;   
        }
        else if (stepState == 1) {                                           
            PORTC = STEP1;
        }
        else if (stepState == 2) {                                              
            PORTC = STEP2; 
        }
        else if (stepState == 3) {
            PORTC = STEP3;
        }
        else if (stepState == 4) {
            PORTC = STEP4;
        }
        else if (stepState == 5) {
            PORTC = STEP5;
        }
        else if (stepState == 6) {
            PORTC = STEP6;
        }
        else if (stepState == 7) {
            PORTC = STEP7;
        }  
        __delay_ms(5);    
        
        i++;   
        if (stepState != 0){
        stepState--;       
        } else {
                       stepState = 7;
        }
    }
    }

void scanRoutine(void){
    __delay_ms(1000);
    
    volatile unsigned int i = 0;                                                         
    while (i < 400) {              
        
        if (stepState == 0) {                                                  
            PORTC = STEP0;   
        }
        else if (stepState == 1) {                                           
            PORTC = STEP1;
        }
        else if (stepState == 2) {                                              
            PORTC = STEP2; 
        }
        else if (stepState == 3) {
            PORTC = STEP3;
        }
        else if (stepState == 4) {
            PORTC = STEP4;
        }
        else if (stepState == 5) {
            PORTC = STEP5;
        }
        else if (stepState == 6) {
            PORTC = STEP6;
        }
        else if (stepState == 7) {
            PORTC = STEP7;
        }  
        __delay_ms(5);    
        
        i++;   
        
        
            if (stepState != 0){
            stepState--;       
            } else {
        stepState = 7;
            }
    }
}