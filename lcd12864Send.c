#define LCDSetCS(sta)
#define LCDSetSCLK(sta)
#define LCDSetSID(Sta)
#define LCDGetSID 1

#define LCD_WAIT_TIME 100
enum LCD_WR
{
    LCD_Write,
    LCD_Read
};

enum LCD_RS
{
    LCD_Cmd,
    LCD_Dat
};

#define Busy 0x80 //用于检测LCD状态字中的Busy标识
void WriteDataLCD(unsigned char WDLCD);
void WriteCommandLCD(unsigned char WCLCD, BuysC);
unsigned char ReadDataLCD(void);
unsigned char ReadStatusLCD(void);
void LCDInit(void);
void LCDClear(void);
void LCDFlash(void);
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData);
void DisplayImage(unsigned char code *DData);
void Delay5Ms(void);
void Delay400Ms(void);

void LCDDelay(unsigned int t);

void LCDInit(void)
{
    LCDSetCS(0);
    LCDSetSCLK(1);
}

char LCDTraByte(enum LCD_WR RW, enum LCD_RS RS, unsigned char d)
{
    int cnt;
    char res;
    LCDSetCS(1);
    if ((RW != LCD_Read) || (RW != LCD_Write)(RS != LCD_Cmd) || (RS != LCD_Dat))
    {
        return 0;
    }
    //起始信号
    LCDSetSCLK(0);
    for (cnt = 0; cnt < 5, cnt++)
    {
        LCDSetSID(1);
        LCDDelay(LCD_WAIT_TIME);
        LCDSetSCLK(1);
        LCDDelay(LCD_WAIT_TIME);
        LCDSetSCLK(0);
    }

    // 发送读写，数据命令以及头结束位
    LCDSetSID(RW == LCD_Write ? 0 : 1);
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(1);
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(0);
    LCDSetSID(RS == LCD_Dat ? 0 : 1);
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(1);
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(0);
    LCDSetSID(0);
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(1);
    LCDDelay(LCD_WAIT_TIME);
    LCDSetSCLK(0);

    if (LCD_Write == RW)
    {
        // 发送数据高四位
        for (cnt = 0; cnt < 8; cnt++)
        {
            if (cnt < 4)
            {
                LCDSetSID((d & (0x80 >> cnt)) == 0 ? 0 : 1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(0);
            }
            else
            {
                LCDSetSID(0);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(0);
            }
        }
        // 发送数据低四位
        for (cnt = 0; cnt < 8; cnt++)
        {
            if (cnt < 4)
            {
                LCDSetSID((d & (0x8 >> cnt)) == 0 ? 0 : 1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(0);
            }
            else
            {
                LCDSetSID(0);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(0);
            }
        }
    }
    else if (LCD_Read == RW)
    {
        res = 0;
        // 接收数据高四位
        for (cnt = 0; cnt < 8; cnt++)
        {
            if (cnt < 4)
            {
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                if (LCDGetSID)
                {
                    res |= (0x80 >> cnt);
                }
                LCDSetSCLK(0);
            }
            else
            {
                LCDSetSID(0);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(0);
            }
        }
        // 接收数据低四位
        for (cnt = 0; cnt < 8; cnt++)
        {
            if (cnt < 4)
            {
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                if (LCDGetSID)
                {
                    res |= (0x8 >> cnt);
                }
                LCDSetSCLK(0);
            }
            else
            {
                LCDSetSID(0);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(1);
                LCDDelay(LCD_WAIT_TIME);
                LCDSetSCLK(0);
            }
        }
    }
    LCDSetCS(0);
    return res;
}
//写数据
void WriteDataLCD(unsigned char WDLCD)
{
    ReadStatusLCD(); //检测忙
    LCDTraByte(LCD_Write, LCD_Dat, WDLCD);
}

//写指令
void WriteCommandLCD(unsigned char WCLCD, BuysC) //BuysC为0时忽略忙检测
{
    if (BuysC)
        ReadStatusLCD(); //根据需要检测忙
    LCDTraByte(LCD_Write, LCD_Cmd, WDLCD);
}

//读数据
unsigned char ReadDataLCD(void)
{
    return LCDTraByte(LCD_Read, LCD_Dat, WDLCD);
}

//读状态
unsigned char ReadStatusLCD(void)
{
    int res = 0;
    do
    {
        res = LCDTraByte(LCD_Read, LCD_Cmd, WDLCD);
    } while (res & Busy); //检测忙信号
    return (res);
}

void LCDInit(void) //LCM初始化
{
    // 等待自检
    LCDDelay(LCD_WAIT_TIME);
    WriteCommandLCD(0x30, 1); //显示模式设置,开始要求每次检测忙信号
    WriteCommandLCD(0x01, 1); //显示清屏
    WriteCommandLCD(0x06, 1); // 显示光标移动设置
    WriteCommandLCD(0x0C, 1); // 显示开及光标设置
}
void LCDClear(void) //清屏
{
    WriteCommandLCD(0x01, 1); //显示清屏
    WriteCommandLCD(0x34, 1); // 显示光标移动设置
    WriteCommandLCD(0x30, 1); // 显示开及光标设置
}
void LCDFlash(void) //闪烁效果
{
    WriteCommandLCD(0x08, 1); //显示清屏
    Delay400Ms();
    WriteCommandLCD(0x0c, 1); // 显示开及光标设置
    Delay400Ms();
    WriteCommandLCD(0x08, 1); //显示清屏
    Delay400Ms();
    WriteCommandLCD(0x0c, 1); // 显示开及光标设置
    Delay400Ms();
    WriteCommandLCD(0x08, 1); //显示清屏
    Delay400Ms();
}
//按指定位置显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    if (Y < 1)
        Y = 1;
    if (Y > 4)
        Y = 4;
    X &= 0x0F; //限制X不能大于16，Y不能大于1
    switch (Y)
    {
    case 1:
        X |= 0X80;
        break;
    case 2:
        X |= 0X90;
        break;
    case 3:
        X |= 0X88;
        break;
    case 4:
        X |= 0X98;
        break;
    }
    WriteCommandLCD(X, 0); //这里不检测忙信号，发送地址码
    WriteDataLCD(DData);
}

//按指定位置显示一串字符
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
    unsigned char ListLength, X2;
    ListLength = 0;
    X2 = X;
    if (Y < 1)
        Y = 1;
    if (Y > 4)
        Y = 4;
    X &= 0x0F; //限制X不能大于16，Y在1-4之内
    switch (Y)
    {
    case 1:
        X2 |= 0X80;
        break; //根据行数来选择相应地址
    case 2:
        X2 |= 0X90;
        break;
    case 3:
        X2 |= 0X88;
        break;
    case 4:
        X2 |= 0X98;
        break;
    }
    WriteCommandLCD(X2, 1);           //发送地址码
    while (DData[ListLength] >= 0x20) //若到达字串尾则退出
    {
        if (X <= 0x0F) //X坐标应小于0xF
        {
            WriteDataLCD(DData[ListLength]); //
            ListLength++;
            X++;
            Delay5Ms();
        }
    }
}

//图形显示122*32
void DisplayImage(unsigned char code *DData)
{
    unsigned char x, y, i;
    unsigned int tmp = 0;
    for (i = 0; i < 9;)
    { //分两屏，上半屏和下半屏，因为起始地址不同，需要分开
        for (x = 0; x < 32; x++)
        { //32行
            WriteCommandLCD(0x34, 1);
            WriteCommandLCD((0x80 + x), 1); //列地址
            WriteCommandLCD((0x80 + i), 1); //行地址，下半屏，即第三行地址0X88
            WriteCommandLCD(0x30, 1);
            for (y = 0; y < 16; y++)
                WriteDataLCD(DData[tmp + y]); //读取数据写入LCD
            tmp += 16;
        }
        i += 8;
    }
    WriteCommandLCD(0x36, 1); //扩充功能设定
    WriteCommandLCD(0x30, 1);
}

//5ms延时
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while (TempCyc--)
        ;
}

//400ms延时
void Delay400Ms(void)
{
    unsigned char TempCycA = 5;
    unsigned int TempCycB;
    while (TempCycA--)
    {
        TempCycB = 7269;
        while (TempCycB--)
            ;
    };
}