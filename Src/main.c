//Locate Peripheral base address
#define PERIPH_BASE           (0x40000000UL)                    /*!< Peripheral base address */

#define AHB1PERIPH_OFFSET     (0X20000UL)                       /*!< AHB1 peripheral offset */
#define AHB1PERIPH_BASE       (PERIPH_BASE + AHB1PERIPH_OFFSET) /*!< AHB1 peripheral base address */

#define GPIOA_OFFSET          (0x0000UL)                       /*!< GPIOA offset */
#define GPIOA_BASE            (AHB1PERIPH_BASE + GPIOA_OFFSET) /*!< GPIOA base address */

#define RCC_OFFSET            (0x3800UL)                       /*!< RCC offset */
#define RCC_BASE              (AHB1PERIPH_BASE + RCC_OFFSET)   /*!< RCC base address */

// Locate the RCC registers in the memory map

// RCC AHB1ENR register address
#define AHB1ENR_OFFSET        (0x30UL)
#define RCC_AHB1ENR_R         (*(volatile unsigned int*)(RCC_BASE + AHB1ENR_OFFSET))

// Shift value to enable GPIOA clock
#define GPIOAEN               (1U<<0)

// GPIOA MODER register
#define MODER_OFFSET          (0x00UL)
#define GPIOA_MODER_R         (*(volatile unsigned int*)(GPIOA_BASE + MODER_OFFSET))

// Input data register
#define IDR_OFFSET            (0x08UL)
#define IDR_BASE              (GPIOA_BASE + IDR_OFFSET)
#define GPIOA_IDR_R           (*(volatile unsigned int*)(GPIOA_BASE + IDR_OFFSET))

// Output data register
#define ODR_OFFSET            (0x0CUL)
#define GPIOA_OD_R            (*(volatile unsigned int*)(GPIOA_BASE + ODR_OFFSET))

// GPIOA pin 5
#define GPIOA_PIN5            (1U<<5)
#define LED_PIN               GPIOA_PIN5

int main(void){
    // Enabling clock acces to GPIOA
    RCC_AHB1ENR_R |= GPIOAEN;

    // Set PA5 as output

    // Set bit 10 to 1
    GPIOA_MODER_R |= (1U<<10);
    // Set bit 11 to 0
    GPIOA_MODER_R &= ~(1U<<11);

    while(1){
        // Read the value of PA0
        if(GPIOA_IDR_R & 1U){
            // Set PA5 to 1
            GPIOA_OD_R |= LED_PIN;
        }else{
            // Set PA5 to 0
            GPIOA_OD_R &= ~LED_PIN;
        }
    }
}
