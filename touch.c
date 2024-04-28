#include "stm32g030xx.h"
#include "touch.h"
#include "soft_i2c.h"

void touch_init(void){
		SoftI2C_Read_Register(0xf0);
		SoftI2C_Write_Register(0xBD, (0xFF) );
		SoftI2C_Write_Register(0xBE, (0x40) );
		SoftI2C_Write_Register(0xBF, (0b10001000) );
}

void write_num(uint8_t digit, uint8_t num){
				if(num==0){
						SoftI2C_Write_Register((192+(digit*2)), (0b00111111));
				}
				else if(num==1){
						SoftI2C_Write_Register((192+(digit*2)), (0b00000110));
				}
				else if(num==2){
						SoftI2C_Write_Register((192+(digit*2)), (0b01011011));
				}
				else if(num==3){
						SoftI2C_Write_Register((192+(digit*2)), (0b01001111));
				}
				else if(num==4){
						SoftI2C_Write_Register((192+(digit*2)), (0b01100110));
				}
				else if(num==5){
						SoftI2C_Write_Register((192+(digit*2)), (0b01101101));
				}
				else if(num==6){
						SoftI2C_Write_Register((192+(digit*2)), (0b01111101));
				}
				else if(num==7){
						SoftI2C_Write_Register((192+(digit*2)), (0b00100111));
				}
				else if(num==8){
						SoftI2C_Write_Register((192+(digit*2)), (0b01111111));
				}
				else if(num==9){
						SoftI2C_Write_Register((192+(digit*2)), (0b01101111));
				}
				/*
				if(digit==00){
						SoftI2C_Write_Register((194), (0b00000000));
						SoftI2C_Write_Register((196), (0b00000000));
				}
				else if(digit==01){
						SoftI2C_Write_Register((192), (0b00000000));
						SoftI2C_Write_Register((196), (0b00000000));
				}
				else if(digit==02){
						SoftI2C_Write_Register((192), (0b00000000));
						SoftI2C_Write_Register((194), (0b00000000));
				}
				*/
				
}


void digit_reset(void){
			SoftI2C_Write_Register((192), (0b00000000));
			SoftI2C_Write_Register((194), (0b00000000));
			SoftI2C_Write_Register((196), (0b00000000));
}



void write_number(uint8_t digit, uint8_t num){
			write_num(digit,num);
			uint8_t d1=0;
			uint8_t d2=0;
			if(num>=10){
					d1= num/10;
					d2= num-(d1*10);
					write_num(digit,d1);
				  write_num((digit+1),d2);
			}
			if(num<=9){
				SoftI2C_Write_Register((194), (0b00000000));
			}
			
			if(num==0){
					write_num(digit,0);
					num=0;
			}
}

		int t1=0;  // For inc falling edge check 
		int t2=0;  // For inc rising edge check
		
		int t3=0;  // For dec falling edge check
		int t4=0;   // For dec rising edge check
		uint8_t num=0;
	  uint8_t t_val =0;


void touch_count(void){

	
	  t_val = SoftI2C_Read_Register(0xF0);
	
	
	
			if(t_val==(0b0000000000)){
					t1=1;
			}
			
			if((t1==1)&&(t_val==(0b0010000000))){
					t2=1;
			}
			
			
			
			if(t_val==(0b0000000000)){
					t3=1;
			}
			
			if((t3==1)&&(t_val==(0b0001000000))){
					t4=1;
			}
			
			
			if((t1==1)&&(t2==1)){
				num = num+1;
				write_number(0, num);
				t1=0;
				t2=0;
			}
			
			if((t3==1)&&(t4==1)){
				if(num>0){
						num = num-1;
				}
				write_number(0, num);
				t3=0;
				t4=0;
			}
}








































