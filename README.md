1. LCD引脚
	- 1---VSS - 模块的电源地
	- 2---VDD - 模块的电源正端
	- 3---V0 - LCD驱动电压输入端
	- 4---RS（CS） H/L 并行的指令/数据选择信号；串行的片选信号
	- 5---R/W（SID） H/L 并行的读写选择信号；串行的数据口
	- 6---E（CLK） H/L 并行的使能信号；串行的同步时钟
	- 7---DB0 H/L 数据0
	- 8---DB1 H/L 数据1
	- 9---DB2 H/L 数据2
	- 10--DB3 H/L 数据3
	- 11--DB4 H/L 数据4
	- 12--DB5 H/L 数据5
	- 13--DB6 H/L 数据6
	- 14--DB7 H/L 数据7
	- 15--PSB H/L 并/串行接口选择：H-并行；L-串行
	- 16--NC 空脚
	- 17--/RET H/L 复位 低电平有效
	- 18--NC 空脚
	- 19--LED\_A （LED+5V） 背光源正极
	- 20--LED\_K （LED-OV）背光源和负极
2. 串行用到的引脚及作用
	- 1---VSS-地
	- 2---VDD-正极
	- 3---V0-LCD对比度
	- 4---RS(CS)-串行片选
	- 5---R/W(SID)-串行数据口
	- 6---E(CLK)-串行同步时钟
	- 15--PSB-低电平LCD进入串行通信莫斯
	- 19--背光正极
	- 20--背光负极
- 参考信息：
	[lcd12864引脚图及功能](http://www.elecfans.com/xianshi/jishu/20171106575409.html)
	[STM32 LCD12864 串行通信模式 (从原理让你理解)]https://blog.csdn.net/as480133937/article/details/97650805)
	[74HC595引脚图时序图工作原理及pdf中文资料](http://www.51hei.com/chip/3978.html)
