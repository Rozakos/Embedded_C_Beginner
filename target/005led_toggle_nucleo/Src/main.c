#include <stdint.h>

uint32_t *pClkCtrlReg =   (uint32_t*)0x40023830;
uint32_t *pPortAModeReg = (uint32_t*)0x40020000;
uint32_t *pPortAOutReg =  (uint32_t*)0x40020014;



int main(void)
{
	//enable the clock for GPIOA peripherals in the AHB1ENR
    *pClkCtrlReg = *pClkCtrlReg | 1;
	//2. configure the mode of the IO pin as output
	//a. clear the 9th and 10th bit positions (CLEAR)
    *pPortAModeReg = *pPortAModeReg & ~( 3 << 10);
	//b. make 10th bit position as 1 (SET)
    *pPortAModeReg = *pPortAModeReg | ( 1 << 10);
    while (1){

        *pPortAOutReg = *pPortAOutReg | ( 1 << 5);

        for (uint32_t i = 0; i<=200000; i++);

        *pPortAOutReg = *pPortAOutReg & ~( 1 << 5);

        for (uint32_t i = 0; i<=200000; i++);
    }

}
