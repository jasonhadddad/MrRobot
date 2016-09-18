
#include "main.h"
#include "LCD.h"
#include "ser.h"
#include "SPI.h"
#include "ADC.h"
#include "motor.h"

volatile unsigned int time_count;
volatile bit FLAG_1000MS;


unsigned char controlByte = 0;
signed int loop = 0;

unsigned char PB6Counter = 0;
unsigned char PB7Counter = 0;
unsigned char PB8Counter = 0;

char count = 0;
            volatile bit wasRight = 0;

        unsigned int localStepPos = 0;
        char leftWall = 0;
        char rightWall = 0;



// Interrupt service routine
void interrupt isr(void){
//Timer 1
    if(TMR0IF){
        TMR0IF = 0;
        TMR0 = TMR0_VAL;
        time_count++;

        if(time_count % 1 == 0) {
            //FLAG_10MS = 1;
            
        }

        if(time_count % 1000 == 0){
            RB4 = !RB4;     //Toggle LED           
            //    FLAG_1000MS = 1;	// Raise flag for 500ms
            time_count = 0;	// Clear time_count        
        }
        
        if (PB8 == 1)
            PB8Counter++;
        if (PB7 == 1)
            PB7Counter++;
        if (PB6 == 1)
            PB6Counter++;
        
  /*     if(getSensorData(18,1) == 0b00000001)
            FLAG_Play++;
        
        if(getSensorData(18,1) == 0b00000100)
            FLAG_Advanced++;
        
        if(getSensorData(18,1) == 0b00000101)
            FLAG_AdvPlay++;
            
   */    
        
    
                
        
    }
}


void initWallFollow(void){
//find closest point
    //assuming sensor initial position is facing west (north being forward direction)
        adcClosest = 0;
        
        
          for (loop = 0; loop < 1600; loop++){ 
              
                moveCCW(1);
                ADCMain();
                
                if (loop < 400 || loop > 1200 && adcRAW > adcClosest){         //left wall                                 
                        adcClosest = adcRAW; 
                        leftWall = 1;
                        rightWall = 0;
                        localStepPos = loop;                   
                }
                
                if (loop > 400 || loop < 1200 && adcRAW > adcClosest){         //right wall      
                    adcClosest = adcRAW;
                    leftWall = 1;
                    rightWall = 1;
                   // localStepPos = loop;      
                }
            }       
        
        
}



void main(void){
__delay_ms(5000);

//Initialise and setup
    setupSPI();
    ser_init();
    setupLCD();
    setupADC();
    
    unsigned char controlByte = 0b00001101;
    spi_transfer(controlByte);
   
    __delay_ms(1000);
    ser_putch(128);     //Startup
    __delay_ms(1000);
    ser_putch(132);     //Full mode
    __delay_ms(1000);
    
    lcdWriteToDigitBCD(500);
    
   
    while(1){       

       
        //Drive forward 4m straight line

        if (getSensorData(18,1) == 0b00000001){ //Play button
            totalDistTrav = 0; 
            DriveDirect(200,200); //Drive, 250mm/s | 250mm/s
            while (totalDistTrav < 2){
                distTrav = getSensorData(19,2);   //Distance packetID, 2 bytes expected
                totalDistTrav = (totalDistTrav + distTrav);
                                        
                lcdSetCursor(0x00);     //Print distance on first row first position
                lcdWriteToDigitBCD(totalDistTrav);  
            }            

            DriveDirect(250,250); //Drive, 250mm/s | 250mm/s
                while (totalDistTrav < 4000){
                    distTrav = getSensorData(19,2);   //Distance packetID, 2 bytes expected
                    totalDistTrav = (totalDistTrav + distTrav);                    
                    lcdSetCursor(0x00);     //Print distance on first row first position
                    lcdWriteToDigitBCD(totalDistTrav);  
                }            

                            
            DriveDirect(0,0);   //Drive, 0mm/s, straight (STOP)
           
        }
        
        //Perform 'Square' manoeuvre
        if (getSensorData(18,1) == 0b00000100){ 
     
            
            
            
            
            
            //Advanced button pressed
            
           totalDistTrav = 0;  //Resets distance traveled
                
                for (loop = 0; loop < 4; loop++){   //Loop 4 times
                   
                    while (totalangleTurned >= -85){
                        Drive(0,250,0xFF,0xFF); //Drive on spot right
                        angleTurned = getSensorData(20,2);  //Angle packetID, 2 bytes expected
                        totalangleTurned = (totalangleTurned + angleTurned);
                    }
                    
                    totalangleTurned = 0;
                    angleTurned = 0;
                    
                    Drive(0,250,0x7F,0xFF);     //Drive, 250mm/s, straight for 1m
                        
                    while (totalDistTrav < 1000){                        
                        distTrav = getSensorData(19,2);   //Distance packetID, 2 bytes expected
                        totalDistTrav = (totalDistTrav + distTrav);            
                        lcdSetCursor(0x00);     //Print distance on first row first position
                        lcdWriteToDigitBCD(totalDistTrav);                  
                    }
                
                    totalDistTrav = 0;    
                    Drive(0,0,0,0);
                
                }
            
            DriveDirect(0,0);
                 
        }
        
 
      
        
        
        
        
        if(getSensorData(18,1) == 0b00000101){  //Play and Advanced at the same time
            //left wall follow (assuming fixed sensor position)
                
                       
            unsigned int ADC_CURRENT = 0;
            unsigned int ADC_ADJUST = 0;
            unsigned int CURRENT_SPEED_L = 90;
            unsigned int ADJUSTED_SPEED_L = 0;
            unsigned int CURRENT_SPEED_R = 80;
            unsigned int ADJUSTED_SPEED_R = 0;
            unsigned int timerLoop = 0;
                
 
        //if(leftWall = 1){//left wall follow    
            unsigned int setADCdist = 250;
            unsigned int safetyCount = 0;
                    
        for(timerLoop = 0; timerLoop < 1200; timerLoop++) {     // (600/5 = 120 loops) 
                ADCMain();                                     //multiplied by 50ms delay = 6000ms                
                                              //i.e. = 1min loop updating every 50 ms                
                if(adcRAW > setADCdist){   
                    while(adcRAW > setADCdist && safetyCount < 20){   
                        ADCMain();
                        ADC_ADJUST = adcRAW - setADCdist;
                        ADJUSTED_SPEED_L = CURRENT_SPEED_L + (7/10)*ADC_ADJUST + (CURRENT_SPEED_L)/(ADC_ADJUST+10);
                        DriveDirect(CURRENT_SPEED_R,ADJUSTED_SPEED_L);       //make right faster  
                        __delay_ms(100);
                        safetyCount++;
                        }
                       safetyCount = 0;
                       wasRight != wasRight;          
                } else if (adcRAW < setADCdist){
                        while(adcRAW < setADCdist && safetyCount < 20){ 
                        ADCMain();
                        ADC_ADJUST = setADCdist - adcRAW;
                        ADJUSTED_SPEED_R = CURRENT_SPEED_R + (7/10)*ADC_ADJUST + (CURRENT_SPEED_R)/(ADC_ADJUST+10);
                        DriveDirect(ADJUSTED_SPEED_R,CURRENT_SPEED_L);       //make right faster  
                        __delay_ms(100);   
                        safetyCount++;
                        }
                       safetyCount = 0;
                    }
        }
        }
            
                                      
        }
           
    
    }


