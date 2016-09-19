#include "main.h"
#include "motor.h"
#include "spi.h"

void setCW(void){
    SELECT_SM();
        __delay_ms(100);
       
    spi_transfer(0b00010010);//11001000
    __delay_ms(100);
}

void setCCW(void){ 
    SELECT_SM();
        __delay_ms(100);
      spi_transfer(0b00010000); //10001000
    __delay_ms(100);  
}


/*void moveCW(void){
    //This run of the funcstion will cause stepCount to be negative.
    //Only relevant for printing stepCount to LCD
    if (stepCount == 0) negativeFlag = 1;       
    lcdWriteStepCount(currentStep);
    stepCount--;            //Decrement stepCount
    
    //Energises windings sequentially based on current step
    switch(currentStep){
        
        case 7: PORTC = STEP6;
        currentStep--;
        break;
        
        case 6: PORTC = STEP5;
        currentStep--;
        break;
        
        case 5: PORTC = STEP4;
        currentStep--;
        break;
        
        case 4: PORTC = STEP3;
        currentStep--;
        break;
        
        case 3: PORTC = STEP2;
        currentStep--;
        break;
        
        case 2: PORTC = STEP1;
        currentStep--;
        break;
        
        case 1: PORTC = STEP0;
        currentStep--;
        break;
        
        case 0: PORTC = STEP7;
        currentStep = 7;
        break;
        
        default: PORTC = 0b00111001;
        break;    
    } 
     
    __delay_ms(3);

}

void moveCCW(void){
    //This run of function will cause stepCount to be pos again, so resets flag
    if (stepCount == (-1)) negativeFlag = 0;    
    
    stepCount++;            //Increment stepCount
    lcdWriteStepCount(currentStep);
    //Energises windings sequentially based on current step    
    switch(currentStep){
        case 0: PORTC = STEP1;
        currentStep++;
        break;
        
        case 1: PORTC = STEP2;
        currentStep++;
        break;
        
        case 2: PORTC = STEP3;
        currentStep++;
        break;
        
        case 3: PORTC = STEP4;
        currentStep++;
        break;
        
        case 4: PORTC = STEP5;
        currentStep++;
        break;
        
        case 5: PORTC = STEP6;
        currentStep++;
        break;
        
        case 6: PORTC = STEP7;
        currentStep++;
        break;
        
        case 7: PORTC = STEP0;
        currentStep = 0;
        break;
        
        default: PORTC = 0b00111001;
        break;    
    }
    
    __delay_ms(3);
    
    
    
}
*/
