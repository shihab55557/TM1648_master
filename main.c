#include "stm32g030xx.h"
#include "serial.h"
#include "adc.h"
#include "i2c.h"
#include "soft_i2c.h"
#include "touch.h"


// Master

void emitter_high(void){
	// rcc enable
	// configure as output 
	// put output high
	RCC->IOPENR |= RCC_IOPENR_GPIOCEN;    //GPIOC clock En
	GPIOC->MODER  &=~ GPIO_MODER_MODE15_1; //make PC15 as GPIO output
	GPIOC->MODER  |= GPIO_MODER_MODE15_0;
	GPIOC-> ODR |= (1<15);
	GPIOC->BSRR |= (1<<15);
	
	//GPIOC-> ODR &=~ (1<15);
	//GPIOC->BSRR &=~ (1<<15);
}






void delay(uint16_t ind){
						for(uint32_t i=0;i<(10000*ind);i++){
							__NOP();
						}
}




int main(void) {
	  
    uart_Init(38400);    // Initialize UART with desired baud rate
	  
		
	
	  uart_send_char("\r\nDebug Started\r\n");
	  
	  SoftI2C_Init();
	
	  for(uint32_t i=0;i<1000000;i++){
			 __NOP();
		}
		
		digit_reset();
		
		touch_init();
		
		uint8_t t_vall=0;
		
    while (1) {
			
			t_vall = SoftI2C_Read_Register(0xF0);
			uart_send_num_bin(t_vall);
			uart_send_char("\r\n");
			//touch_count();
			
			delay(1);
    }
}

