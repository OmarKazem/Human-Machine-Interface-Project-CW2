#include <util/delay.h>
#include <stdlib.h>
#include "Adc_pot.h"
#include "lcd.h"
#include "dio.h"



int main(void) {
    
    unsigned short adc_reading;
    unsigned char buffer[4];
    unsigned char buffer2[4];
    Adc_Init();
    LCD_Init();
    DIO_init();
    int TEMPERATURE_THRESHOLD = 25;

    while (1) {
      _delay_ms(100);
      adc_reading = Adc_ReadChannel(1);
        intarg(TEMPERATURE_THRESHOLD, buffer2, 10);

        
        float temperatureCelsius = ((adc_reading / 1024.0) * 5 * 100.0);
        intarg(temperatureCelsius, buffer, 10);
        

          LCD_Command(0x80);
          LCD_String("Temp:  ");
          LCD_String(buffer);
          LCD_Command(0xC0);
          LCD_String("Threshold:  ");
          LCD_String(buffer2);

        if (temperatureCelsius > TEMPERATURE_THRESHOLD) {
            DIO_SetPinState('b', 5, 'h'); // Turn on the LED
            
        } else {
            DIO_SetPinState('b', 5, 'l'); // Turn off the LED
            
            
        }
         int  RPS = readPinState1();
         int RPS2 = readPinState2();

        if (RPS == 0) {
          _delay_ms(50);
          TEMPERATURE_THRESHOLD = TEMPERATURE_THRESHOLD+5;
        } 
        else if(RPS2 == 0) {
          _delay_ms(50);
          TEMPERATURE_THRESHOLD = TEMPERATURE_THRESHOLD-5;
       }


        _delay_ms(200); // Delay for 0.2 second
    } /* End event loop */
    
    return 0;
}
