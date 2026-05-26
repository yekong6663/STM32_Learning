#include "stm32f10x.h"    
uint16_t ADValue[4];
void MyDMA_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIOStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADCStruct;
	ADCStruct.ADC_ContinuousConvMode = ENABLE;
	ADCStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADCStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADCStruct.ADC_Mode = ADC_Mode_Independent;
	ADCStruct.ADC_NbrOfChannel = 4;
	ADCStruct.ADC_ScanConvMode = ENABLE;
	ADC_Init(ADC1,&ADCStruct);
	
	DMA_InitTypeDef DMAStruct;
	DMAStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMAStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMAStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMAStruct.DMA_MemoryBaseAddr = (uint32_t)ADValue;
	DMAStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMAStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMAStruct.DMA_Mode = DMA_Mode_Circular;
	DMAStruct.DMA_BufferSize = 4;
	DMAStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMAStruct.DMA_M2M = DMA_M2M_Disable;
	DMAStruct.DMA_Priority = DMA_Priority_Medium;
	DMA_Init(DMA1_Channel1,&DMAStruct);
		
	DMA_Cmd(DMA1_Channel1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET ) ;
    ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET) ;
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

