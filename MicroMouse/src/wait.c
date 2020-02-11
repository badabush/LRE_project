#include <wait.h>
//Systick interrupt handler, interrupts at "interrupt rate" per second
//Currently set to interrupt at millisecond intervals
void SysTick_Handler(void){
	Milliseconds++; //Increment millisecond variable
	if(Milliseconds%1000 == 999){ //If 1000 milliseconds have passed, increment seconds
		Seconds++;
	}
}

//Delay function for millisecond delay
void DelayMil(uint32_t MilS){
	volatile uint32_t MSStart = Milliseconds;
	while((Milliseconds - MSStart)<MilS) asm volatile("nop");
}

//Delay function for second delay
void DelaySec(uint32_t S){
	volatile uint32_t Ss = Seconds;
	while((Seconds - Ss)<S) asm volatile("nop");
}
