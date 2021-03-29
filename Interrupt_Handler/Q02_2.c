#include <stm32f4xx.h>

void EXTI0_IRQHandler(void){
	NVIC_DisableIRQ(6);
}

void EXTI1_IRQHandler(void){
	NVIC_DisableIRQ(7);
}

void EXTI2_IRQHandler(void){
	NVIC_DisableIRQ(8);
}

void SysTick_Handler(void){
	SysTick->CTRL &= ~0x01;		// DISABLE Systick timer
	NVIC_SetPendingIRQ(7);	//generate the INT2
	NVIC_SetPendingIRQ(8);	//generate the INT3
}

int main(){
	NVIC_SetPriorityGrouping(5);	//[5:0]: subpriority

	NVIC_SetPriority(6, 0x60>>4);	// INT1
	NVIC_SetPriority(7, 0x40>>4);	// INT2
	NVIC_SetPriority(8, 0x00>>4);	// INT3
	NVIC_SetPriority(-1, 0x20>>4);	// INT4

	NVIC_EnableIRQ(6);		//INT1 Enable
	NVIC_EnableIRQ(7);		//INT2 Enable
	NVIC_EnableIRQ(8);		//INT3 Enable

	SysTick->LOAD = 20;
	SysTick->CTRL = 0x07;	//INT4 Enable

	NVIC_SetPendingIRQ(6);	//generate the INT1
}
