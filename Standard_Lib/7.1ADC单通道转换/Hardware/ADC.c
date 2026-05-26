#include "stm32f10x.h"                  // Device header
void AD_Init(void)  //ADC_Init函数名已经被占用
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	GPIO_InitTypeDef GPIOStruct;
	GPIOStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIOStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIOStruct);
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADCStruct;
	ADCStruct.ADC_ContinuousConvMode = DISABLE;
	ADCStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADCStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADCStruct.ADC_Mode = ADC_Mode_Independent;
	ADCStruct.ADC_NbrOfChannel = 1;
	ADCStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1,&ADCStruct);
	
	ADC_Cmd(ADC1,ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while (ADC_GetResetCalibrationStatus(ADC1) == SET ) ;
    ADC_StartCalibration(ADC1);
	while (ADC_GetCalibrationStatus(ADC1) == SET) ;
}
uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}
