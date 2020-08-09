#define LCDSetCS(sta) 
#define LCDSetSCLK(sta)
#define LCDSetSID(Sta)

#define LCD_WAIT_TIME 100

void LCDDelay(unsigned int t);

void LCDInit(void)
{
    LCDSetCS(0);
    LCDSetSCLK(1);
}

void LCDSendBit(unsigned char d)
{
    LCDSetSCLK(0);
    LCDSetSID((d==0?0:1));
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(1);
    LCDDelay(LCD_WAIT_TIME);
}