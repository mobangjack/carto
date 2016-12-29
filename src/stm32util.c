#include "stm32util.h"

void GPIO_Config(GPIO gpio, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef otype, GPIOPuPd_TypeDef pupd)
{
	GPIO_InitTypeDef io;
	// GPIO_ENABLE_CLK(gpio);
	GPIO_TypeDef* grp = GPIO_PIN_GRP(gpio);
	if (grp == GPIOA) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	}
	if (grp == GPIOB) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	}
	if (grp == GPIOC) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	}
	if (grp == GPIOD) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	}
	if (grp == GPIOE) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	}
	if (grp == GPIOF) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	}
	if (grp == GPIOG) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
	}
	if (grp == GPIOH) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
	}
	if (grp == GPIOI) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
	}
	if (grp == GPIOJ) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOJ, ENABLE);
	}
	if (grp == GPIOK) {
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOK, ENABLE);
	}
	io.GPIO_Pin = GPIO_PIN_MSK(gpio);
	io.GPIO_Mode = mode;
	io.GPIO_Speed = speed;
	io.GPIO_OType = otype;
	io.GPIO_PuPd = pupd;
	GPIO_Init(grp, &io);
}

void GPIO_IN(GPIO gpio)
{
	GPIO_Config(gpio, GPIO_Mode_IN, GPIO_Fast_Speed, GPIO_OType_OD, GPIO_PuPd_NOPULL);
}

void GPIO_OUT(GPIO gpio)
{
	GPIO_Config(gpio, GPIO_Mode_OUT, GPIO_Fast_Speed, GPIO_OType_PP, GPIO_PuPd_NOPULL);
}

void GPIO_AF(GPIO gpio, uint8_t af)
{
	GPIO_PinAFConfig(GPIO_PIN_GRP(gpio), GPIO_PIN_NUM(gpio), af);
	GPIO_Config(gpio, GPIO_Mode_AF, GPIO_Fast_Speed, GPIO_OType_PP, GPIO_PuPd_NOPULL);
}

void GPIO_INT(GPIO gpio, EXTITrigger_TypeDef trig)
{
	uint8_t pinGrp = GPIO_PIN_GRP(gpio);
	uint8_t pinNum = GPIO_PIN_NUM(gpio);
	uint8_t pinMsk = GPIO_PIN_MSK(gpio);
	GPIO_IN(gpio);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(pinGrp, pinNum);
	EXIT_Config(pinMsk, EXTI_Mode_Interrupt, trig);
}

void GPIO_Encoder(GPIO A, GPIO B, TIM_TypeDef* timx, u16 mode, u16 IC1Polarity, u16 IC2Polarity)
{
	if (timx == TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM1);
		GPIO_AF(B, GPIO_AF_TIM1);
	}
	if (timx == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM2);
		GPIO_AF(B, GPIO_AF_TIM2);
	}
	if (timx == TIM3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM3);
		GPIO_AF(B, GPIO_AF_TIM3);
	}
	if (timx == TIM4) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM4);
		GPIO_AF(B, GPIO_AF_TIM4);
	}
	if (timx == TIM5) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM5);
		GPIO_AF(B, GPIO_AF_TIM5);
	}
	/*
	if (timx == TIM6) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM6);
		GPIO_AF(B, GPIO_AF_TIM6);
	}
	*/
	/*
	if (timx == TIM7) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM7);
		GPIO_AF(B, GPIO_AF_TIM7);
	}
	*/
	if (timx == TIM8) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM8);
		GPIO_AF(B, GPIO_AF_TIM8);
	}
	if (timx == TIM9) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM9);
		GPIO_AF(B, GPIO_AF_TIM9);
	}
	if (timx == TIM10) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM10);
		GPIO_AF(B, GPIO_AF_TIM10);
	}
	if (timx == TIM11) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM11);
		GPIO_AF(B, GPIO_AF_TIM11);
	}
	if (timx == TIM12) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM12);
		GPIO_AF(B, GPIO_AF_TIM12);
	}
	if (timx == TIM13) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM13);
		GPIO_AF(B, GPIO_AF_TIM13);
	}
	if (timx == TIM14) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
		GPIO_AF(A, GPIO_AF_TIM14);
		GPIO_AF(B, GPIO_AF_TIM14);
	}
	TIM_EncoderInterfaceConfig(timx, mode, IC1Polarity, IC2Polarity);
	TIM_Cmd(timx, ENABLE);
}

void TIM_Config(TIM_TypeDef* timx, u16 prescaler, u16 counter_mode, u32 period, u16 clock_division, u8 repetition_counter)
{
	TIM_TimeBaseInitTypeDef tim;
	if (timx == TIM1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	if (timx == TIM2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	if (timx == TIM3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	if (timx == TIM4) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	if (timx == TIM5) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}
	if (timx == TIM6) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	}
	if (timx == TIM7) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	}
	if (timx == TIM8) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	}
	if (timx == TIM9) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	}
	if (timx == TIM10) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
	}
	if (timx == TIM11) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
	}
	if (timx == TIM12) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
	}
	if (timx == TIM13) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
	}
	if (timx == TIM14) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
	}
	tim.TIM_Prescaler = prescaler;
	tim.TIM_CounterMode = counter_mode;
	tim.TIM_Period = period;
	tim.TIM_ClockDivision = clock_division;
	tim.TIM_RepetitionCounter = repetition_counter;
	TIM_TimeBaseInit(timx,&tim);
}

void TIM_OC_Config(TIM_TypeDef* timx, u8 channel, u16 mode, u32 pulse)
{
	TIM_OCInitTypeDef oc;
	oc.TIM_OCMode = mode;
    oc.TIM_OutputState = TIM_OutputState_Enable;
    oc.TIM_OutputNState = TIM_OutputState_Disable;
    oc.TIM_Pulse = pulse;
    oc.TIM_OCPolarity = TIM_OCPolarity_Low;
    oc.TIM_OCNPolarity = TIM_OCPolarity_High;
    oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
    oc.TIM_OCNIdleState = TIM_OCIdleState_Set;
	if(channel & 0x01){
		TIM_OC1Init(timx,&oc);
		TIM_OC1PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel & 0x02){
		TIM_OC2Init(timx,&oc);
		TIM_OC2PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel & 0x04){
		TIM_OC3Init(timx,&oc);
		TIM_OC3PreloadConfig(timx,TIM_OCPreload_Enable);
	}
	if(channel & 0x08){
		TIM_OC4Init(timx,&oc);
		TIM_OC4PreloadConfig(timx,TIM_OCPreload_Enable);
	}
}

void NVIC_Config(u8 channel, u8 preemption_priority, u8 subpriority)
{
	NVIC_InitTypeDef nvic;
	nvic.NVIC_IRQChannel = channel;
	nvic.NVIC_IRQChannelPreemptionPriority = preemption_priority;
	nvic.NVIC_IRQChannelSubPriority = subpriority;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
}

void USART_Config(USART_TypeDef* usartx, u32 baudrate, u16 word_length, u16 stopbits, u16 parity, u16 mode, u16 flow_control)
{
	USART_InitTypeDef usart;
	if (usartx == USART1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	if (usartx == USART2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}
	if (usartx == USART3) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}
	if (usartx == USART6) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
	}
	usart.USART_BaudRate = baudrate;
	usart.USART_WordLength = word_length;
	usart.USART_StopBits = stopbits;
	usart.USART_Parity = parity;
	usart.USART_Mode = mode;
	usart.USART_HardwareFlowControl = flow_control;
	USART_Init(usartx, &usart);
}

void CAN_Config(CAN_TypeDef* canx, u16 prescaler, u8 mode, u8 sjw, u8 bs1, u8 bs2)
{
	CAN_InitTypeDef can;
	if (canx == CAN1) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	}
	if (canx == CAN2) {
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	}
	can.CAN_Prescaler = prescaler;
	can.CAN_Mode = mode;
	can.CAN_SJW = sjw;
	can.CAN_BS1 = bs1;
	can.CAN_BS2 = bs2;
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_RFLM = DISABLE;
	can.CAN_TXFP = ENABLE;
	CAN_Init(canx, &can);
}

void CAN_Filter_Config(u16 id_high, u16 id_low, u16 mask_id_high, u16 mask_id_low, u16 fifo, u8 number)
{
	CAN_FilterInitTypeDef can_filter;
	can_filter.CAN_FilterIdHigh = id_high;
	can_filter.CAN_FilterIdLow = id_low;
	can_filter.CAN_FilterMaskIdHigh = mask_id_high;
	can_filter.CAN_FilterMaskIdLow = mask_id_low;
	can_filter.CAN_FilterFIFOAssignment = fifo;
	can_filter.CAN_FilterNumber = number;
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&can_filter);
}

void DMA_Config(DMA_Stream_TypeDef* DMAy_Streamx, u32 channel, u32 pba, u32 mba, u32 dir, u32 bufSize)
{
	DMA_InitTypeDef dma;
	dma.DMA_Channel = channel;
	dma.DMA_PeripheralBaseAddr = pba;
	dma.DMA_Memory0BaseAddr = mba;
	dma.DMA_DIR = dir;
	dma.DMA_BufferSize = bufSize;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_Mode = DMA_Mode_Circular;
	dma.DMA_Priority = DMA_Priority_VeryHigh;
	dma.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	dma.DMA_MemoryBurst = DMA_Mode_Normal;
	dma.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMAy_Streamx,&dma);
}

void EXIT_Config(u32 line, EXTIMode_TypeDef mode, EXTITrigger_TypeDef trigger)
{
	EXTI_InitTypeDef exti;
	exti.EXTI_Line = line;
	exti.EXTI_Mode = mode;
	exti.EXTI_Trigger = trigger;
	exti.EXTI_LineCmd = ENABLE;
	EXTI_Init(&exti);
}

