#ifndef __STM32_UTIL_H__
#define __STM32_UTIL_H__

#include "stm32f4xx.h"

typedef uint32_t GPIO;

#define GPIO_PIN_GRP(gpio) ((GPIO_TypeDef *)(((GPIO)(gpio)) & 0xffffff00))
#define GPIO_PIN_NUM(gpio) (((GPIO)(gpio)) & 0x000000ff)
#define GPIO_PIN_MSK(gpio) (((uint16_t)1) << GPIO_PIN_NUM(gpio))
#define IS_VALID_GPIO_PIN_GRP(grp) ((grp == GPIOA) | \
		(grp == GPIOB) | \
		(grp == GPIOC) | \
		(grp == GPIOD) | \
		(grp == GPIOE) | \
		(grp == GPIOF) | \
		(grp == GPIOG) | \
		(grp == GPIOH) | \
		(grp == GPIOI) | \
		(grp == GPIOJ) | \
		(grp == GPIOK))
#define IS_VALID_GPIO_PIN_NUM(pin) (((pin) >= 0) && ((pin) <= 15))
#define IS_VALID_GPIO(gpio) (IS_VALID_GPIO_PIN_GRP(GPIO_PIN_GRP(gpio)) \
		&& IS_VALID_GPIO_PIN_NUM(GPIO_PIN_NUM(gpio)))

#define UINT32(X) (((uint32_t)X) & 0x000000ff)
#define GPIO_BASE(X,Y) (GPIO##X##_BASE | UINT32(Y))

#define PA0 GPIO_BASE(A,0)
#define PA1 GPIO_BASE(A,1)
#define PA2 GPIO_BASE(A,2)
#define PA3 GPIO_BASE(A,3)
#define PA4 GPIO_BASE(A,4)
#define PA5 GPIO_BASE(A,5)
#define PA6 GPIO_BASE(A,6)
#define PA7 GPIO_BASE(A,7)
#define PA8 GPIO_BASE(A,8)
#define PA9 GPIO_BASE(A,9)
#define PA10 GPIO_BASE(A,10)
#define PA11 GPIO_BASE(A,11)
#define PA12 GPIO_BASE(A,12)
#define PA13 GPIO_BASE(A,13)
#define PA14 GPIO_BASE(A,14)
#define PA15 GPIO_BASE(A,15)

#define PB0 GPIO_BASE(B,0)
#define PB1 GPIO_BASE(B,1)
#define PB2 GPIO_BASE(B,2)
#define PB3 GPIO_BASE(B,3)
#define PB4 GPIO_BASE(B,4)
#define PB5 GPIO_BASE(B,5)
#define PB6 GPIO_BASE(B,6)
#define PB7 GPIO_BASE(B,7)
#define PB8 GPIO_BASE(B,8)
#define PB9 GPIO_BASE(B,9)
#define PB10 GPIO_BASE(B,10)
#define PB11 GPIO_BASE(B,11)
#define PB12 GPIO_BASE(B,12)
#define PB13 GPIO_BASE(B,13)
#define PB14 GPIO_BASE(B,14)
#define PB15 GPIO_BASE(B,15)

#define PC0 GPIO_BASE(C,0)
#define PC1 GPIO_BASE(C,1)
#define PC2 GPIO_BASE(C,2)
#define PC3 GPIO_BASE(C,3)
#define PC4 GPIO_BASE(C,4)
#define PC5 GPIO_BASE(C,5)
#define PC6 GPIO_BASE(C,6)
#define PC7 GPIO_BASE(C,7)
#define PC8 GPIO_BASE(C,8)
#define PC9 GPIO_BASE(C,9)
#define PC10 GPIO_BASE(C,10)
#define PC11 GPIO_BASE(C,11)
#define PC12 GPIO_BASE(C,12)
#define PC13 GPIO_BASE(C,13)
#define PC14 GPIO_BASE(C,14)
#define PC15 GPIO_BASE(C,15)

#define PD0 GPIO_BASE(D,0)
#define PD1 GPIO_BASE(D,1)
#define PD2 GPIO_BASE(D,2)
#define PD3 GPIO_BASE(D,3)
#define PD4 GPIO_BASE(D,4)
#define PD5 GPIO_BASE(D,5)
#define PD6 GPIO_BASE(D,6)
#define PD7 GPIO_BASE(D,7)
#define PD8 GPIO_BASE(D,8)
#define PD9 GPIO_BASE(D,9)
#define PD10 GPIO_BASE(D,10)
#define PD11 GPIO_BASE(D,11)
#define PD12 GPIO_BASE(D,12)
#define PD13 GPIO_BASE(D,13)
#define PD14 GPIO_BASE(D,14)
#define PD15 GPIO_BASE(D,15)

#define PE0 GPIO_BASE(E,0)
#define PE1 GPIO_BASE(E,1)
#define PE2 GPIO_BASE(E,2)
#define PE3 GPIO_BASE(E,3)
#define PE4 GPIO_BASE(E,4)
#define PE5 GPIO_BASE(E,5)
#define PE6 GPIO_BASE(E,6)
#define PE7 GPIO_BASE(E,7)
#define PE8 GPIO_BASE(E,8)
#define PE9 GPIO_BASE(E,9)
#define PE10 GPIO_BASE(E,10)
#define PE11 GPIO_BASE(E,11)
#define PE12 GPIO_BASE(E,12)
#define PE13 GPIO_BASE(E,13)
#define PE14 GPIO_BASE(E,14)
#define PE15 GPIO_BASE(E,15)

#define PF0 GPIO_BASE(F,0)
#define PF1 GPIO_BASE(F,1)
#define PF2 GPIO_BASE(F,2)
#define PF3 GPIO_BASE(F,3)
#define PF4 GPIO_BASE(F,4)
#define PF5 GPIO_BASE(F,5)
#define PF6 GPIO_BASE(F,6)
#define PF7 GPIO_BASE(F,7)
#define PF8 GPIO_BASE(F,8)
#define PF9 GPIO_BASE(F,9)
#define PF10 GPIO_BASE(F,10)
#define PF11 GPIO_BASE(F,11)
#define PF12 GPIO_BASE(F,12)
#define PF13 GPIO_BASE(F,13)
#define PF14 GPIO_BASE(F,14)
#define PF15 GPIO_BASE(F,15)

#define PG0 GPIO_BASE(G,0)
#define PG1 GPIO_BASE(G,1)
#define PG2 GPIO_BASE(G,2)
#define PG3 GPIO_BASE(G,3)
#define PG4 GPIO_BASE(G,4)
#define PG5 GPIO_BASE(G,5)
#define PG6 GPIO_BASE(G,6)
#define PG7 GPIO_BASE(G,7)
#define PG8 GPIO_BASE(G,8)
#define PG9 GPIO_BASE(G,9)
#define PG10 GPIO_BASE(G,10)
#define PG11 GPIO_BASE(G,11)
#define PG12 GPIO_BASE(G,12)
#define PG13 GPIO_BASE(G,13)
#define PG14 GPIO_BASE(G,14)
#define PG15 GPIO_BASE(G,15)

#define PH0 GPIO_BASE(H,0)
#define PH1 GPIO_BASE(H,1)
#define PH2 GPIO_BASE(H,2)
#define PH3 GPIO_BASE(H,3)
#define PH4 GPIO_BASE(H,4)
#define PH5 GPIO_BASE(H,5)
#define PH6 GPIO_BASE(H,6)
#define PH7 GPIO_BASE(H,7)
#define PH8 GPIO_BASE(H,8)
#define PH9 GPIO_BASE(H,9)
#define PH10 GPIO_BASE(H,10)
#define PH11 GPIO_BASE(H,11)
#define PH12 GPIO_BASE(H,12)
#define PH13 GPIO_BASE(H,13)
#define PH14 GPIO_BASE(H,14)
#define PH15 GPIO_BASE(H,15)

#define PI0 GPIO_BASE(I,0)
#define PI1 GPIO_BASE(I,1)
#define PI2 GPIO_BASE(I,2)
#define PI3 GPIO_BASE(I,3)
#define PI4 GPIO_BASE(I,4)
#define PI5 GPIO_BASE(I,5)
#define PI6 GPIO_BASE(I,6)
#define PI7 GPIO_BASE(I,7)
#define PI8 GPIO_BASE(I,8)
#define PI9 GPIO_BASE(I,9)
#define PI10 GPIO_BASE(I,10)
#define PI11 GPIO_BASE(I,11)
#define PI12 GPIO_BASE(I,12)
#define PI13 GPIO_BASE(I,13)
#define PI14 GPIO_BASE(I,14)
#define PI15 GPIO_BASE(I,15)

#define PJ0 GPIO_BASE(J,0)
#define PJ1 GPIO_BASE(J,1)
#define PJ2 GPIO_BASE(J,2)
#define PJ3 GPIO_BASE(J,3)
#define PJ4 GPIO_BASE(J,4)
#define PJ5 GPIO_BASE(J,5)
#define PJ6 GPIO_BASE(J,6)
#define PJ7 GPIO_BASE(J,7)
#define PJ8 GPIO_BASE(J,8)
#define PJ9 GPIO_BASE(J,9)
#define PJ10 GPIO_BASE(J,10)
#define PJ11 GPIO_BASE(J,11)
#define PJ12 GPIO_BASE(J,12)
#define PJ13 GPIO_BASE(J,13)
#define PJ14 GPIO_BASE(J,14)
#define PJ15 GPIO_BASE(J,15)

#define PK0 GPIO_BASE(K,0)
#define PK1 GPIO_BASE(K,1)
#define PK2 GPIO_BASE(K,2)
#define PK3 GPIO_BASE(K,3)
#define PK4 GPIO_BASE(K,4)
#define PK5 GPIO_BASE(K,5)
#define PK6 GPIO_BASE(K,6)
#define PK7 GPIO_BASE(K,7)
#define PK8 GPIO_BASE(K,8)
#define PK9 GPIO_BASE(K,9)
#define PK10 GPIO_BASE(K,10)
#define PK11 GPIO_BASE(K,11)
#define PK12 GPIO_BASE(K,12)
#define PK13 GPIO_BASE(K,13)
#define PK14 GPIO_BASE(K,14)
#define PK15 GPIO_BASE(K,15)

#define GPIO_CHECK_CLK(gpio,grp) \
	if(GPIO_PIN_GRP(gpio)==grp) \
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_##grp, ENABLE)

#define GPIO_ENABLE_CLK(gpio) { \
		GPIO_CHECK_CLK(gpio,GPIOA); \
		GPIO_CHECK_CLK(gpio,GPIOB); \
		GPIO_CHECK_CLK(gpio,GPIOC); \
		GPIO_CHECK_CLK(gpio,GPIOD); \
		GPIO_CHECK_CLK(gpio,GPIOE); \
		GPIO_CHECK_CLK(gpio,GPIOF); \
		GPIO_CHECK_CLK(gpio,GPIOG); \
		GPIO_CHECK_CLK(gpio,GPIOH); \
		GPIO_CHECK_CLK(gpio,GPIOI); \
		GPIO_CHECK_CLK(gpio,GPIOJ); \
		GPIO_CHECK_CLK(gpio,GPIOK); \
	}

#define GPIO_SET(gpio)    GPIO_SetBits(GPIO_PIN_GRP(gpio), GPIO_PIN_MSK(gpio))
#define GPIO_RST(gpio)    GPIO_ResetBits(GPIO_PIN_GRP(gpio), GPIO_PIN_MSK(gpio))
#define GPIO_TOG(gpio)    GPIO_ToggleBits(GPIO_PIN_GRP(gpio), GPIO_PIN_MSK(gpio))
#define GPIO_READ_IN(gpio)   GPIO_ReadInputDataBit(GPIO_PIN_GRP(gpio), GPIO_PIN_MSK(gpio))
#define GPIO_READ_OUT(gpio)   GPIO_ReadOutputDataBit(GPIO_PIN_GRP(gpio), GPIO_PIN_MSK(gpio))
#define GPIO_WRITE(gpio,v)  GPIO_WriteBit(GPIO_PIN_GRP(gpio), GPIO_PIN_MSK(gpio), (v) > 0 ? Bit_SET : Bit_RESET)

void GPIO_Config(GPIO gpio, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd);
void TIM_Config(TIM_TypeDef* timx, u16 prescaler, u16 counter_mode, u32 period, u16 clock_division, u8 repetition_counter);
void TIM_OC_Config(TIM_TypeDef* timx, u8 channel, u16 mode, u16 optState, u16 optNewState, u32 pulse, u16 polarity, u16 newPolarity, u16 idleState, u16 newIdleState);
void NVIC_Config(u8 channel, u8 preemption_priority, u8 subpriority);
void USART_Config(USART_TypeDef* usartx, u32 baudrate, u16 word_length, u16 stopbits, u16 parity, u16 mode, u16 flow_control);
void CAN_Config(CAN_TypeDef* canx, u16 prescaler, u8 mode, u8 sjw, u8 bs1, u8 bs2, FunctionalState ttcm, FunctionalState abom, FunctionalState awum, FunctionalState nart, FunctionalState rflm, FunctionalState txfp);
void CAN_Filter_Config(u16 id_high, u16 id_low, u16 mask_id_high, u16 mask_id_low, u16 fifo, u8 number, u8 mode, u8 scale);
void DMA_Config(DMA_Stream_TypeDef* DMAy_Streamx, u32 channel, u32 pba, u32 mba, u32 dir, u32 bufSize);
void EXIT_Config(u32 line, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger);

#define GPIO_AF(gpio,speed,otype,pupd) GPIO_Config(gpio, GPIO_Mode_AF, speed, otype, pupd)
#define GPIO_IN(gpio,speed,otype,pupd) GPIO_Config(gpio, GPIO_Mode_IN, speed, otype, pupd)
#define GPIO_OUT(gpio,speed,otype,pupd) GPIO_Config(gpio, GPIO_Mode_OUT, speed, otype, pupd)

#endif

