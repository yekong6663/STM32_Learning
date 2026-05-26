#include "stm32f10x.h"                  // Device header
#include "time.h"
uint32_t MyRTCArray[6] = {2026,1,1,0,0,0};  //2026年1月1日0时0分0秒
void MyRTC_Init(void)
{
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
		PWR_BackupAccessCmd(ENABLE);
		
		RCC_LSEConfig(RCC_LSE_ON);
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)!= SET);
		
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
		
		RTC_SetPrescaler(32768-1);   //LSE的频率是32.768Hz
		RTC_WaitForLastTask();
		
		RTC_SetCounter(1767196800-1); //2026-01-1 0:0:0的Unix时间戳
		RTC_WaitForLastTask();
		
		BKP_WriteBackupRegister(BKP_DR1,0xA5A5);
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_WaitForLastTask();
	}
}
void MyRTC_SetTime(void)
{
	time_t time;                      //一个表示Unix时间戳变量
	struct tm time_date;			  //一个表示时间时间与日期的结构体
	time_date.tm_year = MyRTCArray[0]-1900;	//年,since 1900
	time_date.tm_mon = MyRTCArray[1]-1; 	//月,since 0
	time_date.tm_mday = MyRTCArray[2];		//日
	time_date.tm_hour = MyRTCArray[3];		//时
	time_date.tm_min = MyRTCArray[4]; 		//分
	time_date.tm_sec = MyRTCArray[5]; 		//秒
	
	time = mktime(&time_date) - 8*60*60;   	//换算成东八区时间

	RTC_SetCounter(time);
	RTC_WaitForLastTask();
}
void MyRTC_ReadTime(void)
{
	time_t time;            
    struct tm time_date;	
	
	time = RTC_GetCounter()+8*60*60;		//换算成东八区时间
	RTC_WaitForLastTask();
	
	time_date = *localtime(&time);
	
	MyRTCArray[0] = time_date.tm_year+1900;
	MyRTCArray[1] = time_date.tm_mon+1 ;
    MyRTCArray[2] = time_date.tm_mday;
    MyRTCArray[3] = time_date.tm_hour;
    MyRTCArray[4] = time_date.tm_min ;
    MyRTCArray[5] = time_date.tm_sec ;
} 
