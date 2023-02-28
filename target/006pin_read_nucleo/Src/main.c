#include <stdint.h>

uint32_t *pClkCtrlReg   = (uint32_t*)0x40023830;
uint32_t *pPortAModeReg = (uint32_t*)0x40020000;
uint32_t *pPortBModeReg = (uint32_t*)0x40020400;
uint32_t *pPortAOutReg  = (uint32_t*)0x40020014;
uint32_t *pPortBInReg   = (uint32_t*)0x40020410;



int main(void)
{
	//enable the clock for GPIOA peripherals in the AHB1ENR
    *pClkCtrlReg = *pClkCtrlReg | 1;
	//2. configure the mode of the IO pin as output
	//a. clear the 9th and 10th bit positions (CLEAR)
    *pPortAModeReg = *pPortAModeReg & ~( 3 << 10);
	//Configure PB2 as input mode (GPIOA MODE REGISTER)
	//a. clear the 3rd and 4th bit positions (CLEAR)
    *pPortBModeReg = *pPortBModeReg & ~( 3 << 4);

    //read PB2 Input
    uint8_t pinStatus = (uint8_t) (*pPortBInReg & 0x4);
//    uint32_t pinStatus = *pPortBInReg;

	//b. make 10th bit position as 1 (SET)
    *pPortAModeReg = *pPortAModeReg | ( 1 << 10);
    while (1){

        if(pinStatus == 1)
        {
            *pPortAOutReg = *pPortAOutReg | ( 1 << 5);
        }
        else
        {
            *pPortAOutReg = *pPortAOutReg & ~( 1 << 5);
        }
    }

}


//#include <stdint.h>
//
//#define RCC_BASE_ADDRESS        0x40023800
//#define GPIOA_BASE_ADDRESS      0x40020000
//#define GPIOB_BASE_ADDRESS      0x40020400
//
//#define RCC_AHB1ENR_OFFSET      0x30
//#define GPIOA_MODER_OFFSET      0x00
//#define GPIOB_MODER_OFFSET      0x00
//#define GPIOB_IDR_OFFSET        0x10
//#define GPIOA_BSRR_OFFSET       0x18
//
//#define RCC_AHB1ENR_GPIOAEN     (1 << 0)
//#define RCC_AHB1ENR_GPIOBEN     (1 << 1)
//
//#define GPIO_MODER_INPUT        0x00
//#define GPIO_MODER_OUTPUT       0x01
//
//int main(void)
//{
//  // Enable the clock for GPIOA and GPIOB
//  volatile uint32_t *rcc_ahb1enr = (volatile uint32_t *)(RCC_BASE_ADDRESS + RCC_AHB1ENR_OFFSET);
//  *rcc_ahb1enr |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
//
//  // Configure PB2 as an input and PA5 as an output
//  volatile uint32_t *gpiob_moder = (volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIOB_MODER_OFFSET);
//  *gpiob_moder &= ~(GPIO_MODER_OUTPUT << 4);  // clear PB2
//  *gpiob_moder |= GPIO_MODER_INPUT << 4;      // set PB2 as input
//
//  volatile uint32_t *gpioa_moder = (volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIOA_MODER_OFFSET);
//  *gpioa_moder |= GPIO_MODER_OUTPUT << 10;    // set PA5 as output
//
//  while (1)
//  {
//    // Read the input value of PB2
//    volatile uint32_t *gpiob_idr = (volatile uint32_t *)(GPIOB_BASE_ADDRESS + GPIOB_IDR_OFFSET);
//    uint32_t input_value = (*gpiob_idr & (1 << 2)) ? 1 : 0;
//
//    // Set the output value of PA5 accordingly
//    volatile uint32_t *gpioa_bsrr = (volatile uint32_t *)(GPIOA_BASE_ADDRESS + GPIOA_BSRR_OFFSET);
//    if (input_value)
//    {
//      *gpioa_bsrr = 1 << 5;  // set PA5 high
//    }
//    else
//    {
//      *gpioa_bsrr = 1 << 21; // set PA5 low
//    }
//  }
//}
//
//
