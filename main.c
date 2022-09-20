
#include "main.h"
#include "stm32f0xx.h"

#define DELAY1 1000  //constant for main loop
#define DELAY2 800   //constant for nested loop

#define TRUE 1
#define FALSE 0

void initGPIO(void);
void delay(void);
void firstDisplay(void);
void secondDisplay(void);
void thirdDisplay(void);
void checkPB(void);
void display(void);

uint32_t bitpattern1 =  0; //turns all LEDs off
uint32_t bitpattern2 = 0b11111111; //turns all LEDs on
uint32_t bitpattern3 = 0b10101010; //turns alternating LEDs off

typedef uint8_t flag_t;
flag_t startFlag = FALSE;
flag_t firstFlag = FALSE;
flag_t secondFlag = FALSE;
flag_t thirdFlag = FALSE;

int main(void)
{
	initGPIO();

  while (1)
  {

	  display();

  }

}


void initGPIO(void)
{
	RCC-> AHBENR |= RCC_AHBENR_GPIOBEN; //enable the clock for port b
	RCC-> AHBENR |= RCC_AHBENR_GPIOAEN; //enable the clock for port a
	//GPIOA pins reset state is digital input mode
	//hence no need to set them to input mode

	GPIOB -> MODER |= 0x00005555; //makes all the LEDS digital output mode
	GPIOB -> ODR = 0; //ensure all the LEDs are off

	GPIOA -> PUPDR |= 0x00000055; //turns on the pull resistors for port a



}

void delay(void)
{
	for (volatile uint32_t i = 0; i < DELAY1; i++)
	   {

	    for (volatile uint32_t j = 0; j < DELAY2; j++);
	   }

}

void firstDisplay(void)
{
	GPIOB -> ODR = bitpattern1; //turns all LEDs off
	delay();
	GPIOB -> ODR = bitpattern2; //turns all LEDS on
	delay();
	GPIOB -> ODR = bitpattern3; //turns alternating LEDs on
	delay();

}

void secondDisplay(void)
{
	volatile uint32_t k = 0;
	while (k<8)
	{
		GPIOB -> ODR = (1<<k) ; //turn each LED on
		delay();
		k++;  //increment counter
	}
	k=0; //reset counter

}

void thirdDisplay(void)
{
	volatile uint8_t counter = 0;
	while (counter< (256))
	{
		GPIOB -> ODR = counter; //displays counter number on LEDs
		delay();
		counter++;  //increment counter
	}
	counter = 0;  //reset counter

}

void checkPB(void)
{
	uint16_t PA0_Pressed = ( ( GPIOA -> IDR & GPIO_IDR_0) == 0) ; // PA0_Pressed == 1 when SW0 is pressed
	uint16_t PA1_Pressed = ( ( GPIOA -> IDR & GPIO_IDR_1) == 0) ; // PA1_Pressed == 1 when SW1 is pressed
	uint16_t PA2_Pressed = ( ( GPIOA -> IDR & GPIO_IDR_2) == 0) ; // PA2_Pressed == 1 when SW2 is pressed
	uint16_t PA3_Pressed = ( ( GPIOA -> IDR & GPIO_IDR_3) == 0) ; // PA3_Pressed == 1 when SW3 is pressed

	if (PA0_Pressed ==1 ) //SW0 pressed raises the startFlag
	{
		startFlag = TRUE;
	}
	else if (PA1_Pressed ==1) //SW1 pressed raises the firstFlag and startFlag
	{
		startFlag = TRUE;
		firstFlag =TRUE;
	}
	else if (PA2_Pressed ==1) //SW2 pressed raises the secondFlag and startFlag
	{
		startFlag = TRUE;
		secondFlag = TRUE;
	}
	else if (PA3_Pressed==1) //SW3 pressed raises the thirdFlag and startFlag
	{
		startFlag = TRUE;
		thirdFlag = TRUE;
	}
	else{}
}
void display(void)
{
	checkPB(); //checks which switch is pressed

	if ((startFlag == TRUE)&& (firstFlag == FALSE)&& (secondFlag == FALSE)&&(thirdFlag == FALSE))
	{
		GPIOB-> ODR = 0b1; //SW0 turns LED B0 on
	}
	else if ((startFlag ==TRUE) && (firstFlag == TRUE)&& (secondFlag == FALSE)&&(thirdFlag == FALSE))
	{
		firstDisplay(); //SW1 displays function firstDisplay
	}
	else if ((startFlag ==TRUE )&& (firstFlag == FALSE)&&( secondFlag == TRUE)&&(thirdFlag == FALSE))
	{
		secondDisplay(); //SW2 displays function secondDisplay
	}
	else if ((startFlag ==TRUE) && (firstFlag == FALSE)&& (secondFlag == FALSE)&& (thirdFlag == TRUE))
	{
		thirdDisplay(); //SW3 displays function thirdDisplay
	}
	else{}
}
