/*
 * servo_control.c
 *
 * Created: 12/1/2019 2:47:44 PM
 *  Author: dmay3
 */ 
#include "grbl.h"

#define SERVO_MAX 37800
#define SERVO_MIN 35000

static uint32_t location1 = SERVO_MAX;

void servo_init()
{
	SERVO_PWM_DDR |= (1<<5);
	
	//Output Mode WGM = 1110 - FAST PWM
	//Prescaler is set to /8
	//Inverted Mode
	SERVO_TCCRA |= 1<<WGM31 | 1<<COM4C0 | 1<<COM3C1;
	SERVO_TCCRB |= 1<<WGM33 | 1<<WGM32 | 1<<CS31;
	
	//50 Hz == 20mS == (F_CPU/8)/50
	ICR3 = 40000;
	
	//Max 5000
	OCR3C = SERVO_MAX;
	

}


int servo_update( int steps )
{
	int oldLocaton = location1;
	location1 -= steps;
	
	if( location1 < SERVO_MIN )
	{
		location1 = SERVO_MIN;
	}
	if( location1 >= SERVO_MAX )
	{
		location1 = SERVO_MAX;
	}
	OCR3C = location1;
	
	return(oldLocaton-location1);
}