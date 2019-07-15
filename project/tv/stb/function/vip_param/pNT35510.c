#include "dIO.h"
#include "dTypes.h"
#include "dDebug.h"

#define FAN_EN D_GPIO_PORT8_BIT4
#define SPI_SDI D_GPIO_PORT8_BIT3
#define SPI_SCK D_GPIO_PORT8_BIT2
#define SPI_CS D_GPIO_PORT8_BIT1
#define SPI_RST D_GPIO_PORT8_BIT0 

#define MUTE_IO D_GPIO_PORT4_BIT7 


#define SPI_MODE_MASTER

static D_Handle SPISCK = D_INVALID_HANDLE;
static D_Handle SPISDI = D_INVALID_HANDLE;
static D_Handle SPIRST = D_INVALID_HANDLE;
static D_Handle SPICS = D_INVALID_HANDLE;
static D_Handle SPICD = D_INVALID_HANDLE;
static D_Handle FANEN = D_INVALID_HANDLE;
static D_Handle MUTEIO = D_INVALID_HANDLE;

//#define TimeCal
#ifdef TimeCal
static unsigned long start_time;
static unsigned long stop_time;

#endif

void mute_gpio_set(void)
{
	volatile D_U32 j;

	d_gpio_set(MUTEIO);
	for(j=0;j<5000;j++);//100us	
	d_gpio_clear(MUTEIO);
	for(j=0;j<400;j++);//5us	
	d_gpio_set(MUTEIO);
	for(j=0;j<400;j++);//5us	
	d_gpio_clear(MUTEIO);
}

void spi_gpio_init(void)
{
	D_U32 j;

	FANEN = d_gpio_open(FAN_EN, D_PIO_BIT_OUTPUT);
	if (FANEN	== D_INVALID_HANDLE)
		D_ERROR("SPI FANEN GPIO OPEN FAILED\n");
	d_gpio_clear(FANEN);
	
	MUTEIO = d_gpio_open(MUTE_IO, D_PIO_BIT_OUTPUT);
	if (MUTEIO	== D_INVALID_HANDLE)
		D_ERROR("SPI MUTEIO GPIO OPEN FAILED\n");	
	d_gpio_set(MUTEIO);

	SPISCK = d_gpio_open(SPI_SCK, D_PIO_BIT_OUTPUT);
    if (SPISCK  == D_INVALID_HANDLE)
        D_ERROR("SPI SCK GPIO OPEN FAILED\n");
    d_gpio_set(SPISCK);
	
	SPISDI = d_gpio_open(SPI_SDI, D_PIO_BIT_OUTPUT);
    if (SPISDI  == D_INVALID_HANDLE)
        D_ERROR("SPI SDI GPIO OPEN FAILED\n");
    d_gpio_set(SPISDI);
	
	SPICS = d_gpio_open(SPI_CS, D_PIO_BIT_OUTPUT);
    if (SPICS == D_INVALID_HANDLE)
        D_ERROR("SPI CS GPIO OPEN FAILED\n");
    d_gpio_set(SPICS);
		
 	SPIRST = d_gpio_open(SPI_RST, D_PIO_BIT_OUTPUT);
    if (SPIRST  == D_INVALID_HANDLE)
        D_ERROR("SPI RST GPIO OPEN FAILED\n");
   d_gpio_set(SPIRST);
		
}

void DelayMS(D_U32 ms)
{
    d_task_wait(ms);
}
void DelayUS(void)
{
	volatile D_U32 j;
	for(j=0;j<2500;j++);

//	for(j=0;j<5000;j++);
}

void lcd_1638_sck(D_U8 on)
{
    if(on)
        d_gpio_set(SPISCK);
    else
        d_gpio_clear(SPISCK);
}

void lcd_1638_sdi(D_U8 on)
{
    if(on)
        d_gpio_set(SPISDI);
    else
        d_gpio_clear(SPISDI);
}
void lcd_1638_reset(D_U8 on)
{
    if(on)
        d_gpio_set(SPIRST);
    else
        d_gpio_clear(SPIRST);
}

void lcd_1638_cs(D_U8 on)
{
    if(on)
        d_gpio_set(SPICS);
    else
        d_gpio_clear(SPICS);
}

void Spi_Write_Byte(D_U8 data)
{
	D_U8 i;
	
//    lcd_1638_cs(0);
	for(i=0;i<8;i++)
	{
		lcd_1638_sck(0);
		DelayUS();		
		if (data&0x80)
		{
			lcd_1638_sdi(1);
		}
		else
		{
			lcd_1638_sdi(0);
		}
		//TFT_PIN_SCLK_LOW();
		lcd_1638_sck(1);
		DelayUS();
		data<<=1;
	}
//    lcd_1638_cs(1);
}

void SPI_WriteComm(D_U16 SPI_CMD)
{
	lcd_1638_cs(0);
	DelayUS();
	Spi_Write_Byte(0x20);
	Spi_Write_Byte((SPI_CMD&0xFF00) >> 8);
	lcd_1638_cs(1);
	DelayUS();
	lcd_1638_cs(0);
	DelayUS();
	Spi_Write_Byte(0x00);
	Spi_Write_Byte(SPI_CMD & 0x00FF);
	lcd_1638_cs(1);
	DelayUS();	
}

void SPI_WriteData(D_U8 SPI_DATA)
{
	lcd_1638_cs(0);
	DelayUS();
	Spi_Write_Byte(0x40);
	Spi_Write_Byte(SPI_DATA);
	lcd_1638_cs(1);
	DelayUS();	
}

void SPI_WriteCommData(D_U16 SPI_CMD,D_U8 SPI_DATA)
{
	SPI_WriteComm(SPI_CMD);
    SPI_WriteData(SPI_DATA);
}

void lcd_1638_init(void)
{
	d_gpio_clear(SPIRST);
	D_DUMP("ShenChao NT35510_LCD_INIT ...\r\n");
	d_task_wait(70);
	d_gpio_set(SPIRST);
	d_task_wait(150);
	//TFT_PIN_RESET_HIGH();
	//Delay(100);
#if 1
	//TFT_PIN_SCS_LOW();

	//************* Start Initial Sequence **********//
	/*code by tony start*/
	SPI_WriteComm(0x1100);
	//TFT_PIN_SCS_HIGH();
	d_task_wait(300);
	//TFT_PIN_SCS_LOW();
	SPI_WriteComm(0x2000);
#ifdef TTL_PANEL_24B
	SPI_WriteComm(0x3A00);	  SPI_WriteData(0x77);// 66 => 18bit, 77 => 24bit
#else
	SPI_WriteComm(0x3A00);	  SPI_WriteData(0x66);
#endif
#if 1
	SPI_WriteComm(0x3600);	  SPI_WriteData(0x20);
	//colum
	SPI_WriteComm(0x2A00);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2A01);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2A02);	  SPI_WriteData(0x03);
	SPI_WriteComm(0x2A03);	  SPI_WriteData(0x1F);
	//page
	SPI_WriteComm(0x2B00);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2B01);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2B02);	  SPI_WriteData(0x01);
	SPI_WriteComm(0x2B03);	  SPI_WriteData(0xDF);
#endif	
	SPI_WriteComm(0x2C00);
	/*
	WriteComm(0x5300);	  WriteData(0x00);//BCTRL OFF
	WriteComm(0x5500);	  WriteData(0x00);//CABC OFF
		WriteComm(0x5100);	  WriteData(0xFF);//Brightness full
	*/
	/*code by tony end*/
	//LV2 Page 1 enable
	SPI_WriteCommData(0xF000,0x55);
	SPI_WriteCommData(0xF001,0xAA);
	SPI_WriteCommData(0xF002,0x52);
	SPI_WriteCommData(0xF003,0x08);
	SPI_WriteCommData(0xF004,0x01);
	//AVDD Set AVDD 5.2V
	SPI_WriteCommData(0xB000,0x0A);
	SPI_WriteCommData(0xB001,0x0A);
	SPI_WriteCommData(0xB002,0x0A);
	//AVDD ratio
	SPI_WriteCommData(0xB600,0x44);
	SPI_WriteCommData(0xB601,0x44);
	SPI_WriteCommData(0xB602,0x44);
	//AVEE	-5.2V
	SPI_WriteCommData(0xB100,0x0A);
	SPI_WriteCommData(0xB101,0x0A);
	SPI_WriteCommData(0xB102,0x0A);
	//AVEE ratio
	SPI_WriteCommData(0xB700,0x24);
	SPI_WriteCommData(0xB701,0x34);
	SPI_WriteCommData(0xB702,0x34);
	//VCL  -2.5V
	SPI_WriteCommData(0xB200,0x00);
	SPI_WriteCommData(0xB201,0x00);
	SPI_WriteCommData(0xB202,0x00);
	//VCL ratio
	SPI_WriteCommData(0xB800,0x34);
	SPI_WriteCommData(0xB801,0x34);
	SPI_WriteCommData(0xB802,0x34);
	//VGL_REG -10V
	SPI_WriteCommData(0xB500,0x08);
	SPI_WriteCommData(0xB501,0x08);
	SPI_WriteCommData(0xB502,0x08);
	SPI_WriteCommData(0xC200,0x03);
	//VGH 15V  (Free pump)
	SPI_WriteCommData(0xBF00,0x01);
	SPI_WriteCommData(0xB300,0x09);
	SPI_WriteCommData(0xB301,0x06);
	SPI_WriteCommData(0xB302,0x06);
	//VGH ratio
	SPI_WriteCommData(0xB900,0x34);
	SPI_WriteCommData(0xB901,0x24);
	SPI_WriteCommData(0xB902,0x24);
	//VGLX ratio
	SPI_WriteCommData(0xBA00,0x14);
	SPI_WriteCommData(0xBA01,0x14);
	SPI_WriteCommData(0xBA02,0x14);
	//VGMP/VGSP 4.5V/0V
	SPI_WriteCommData(0xBC00,0x00);
	SPI_WriteCommData(0xBC01,0x78);
	SPI_WriteCommData(0xBC02,0x00);
	//VGMN/VGSN -4.5V/0V
	SPI_WriteCommData(0xBD00,0x00);
	SPI_WriteCommData(0xBD01,0x78);
	SPI_WriteCommData(0xBD02,0x00);
	//VCOM	-1.25V
	SPI_WriteCommData(0xBE00,0x00);
	SPI_WriteCommData(0xBE01,0x95);
	//Gamma Setting
	SPI_WriteCommData(0xD100,0x00);
	SPI_WriteCommData(0xD101,0x06);
	SPI_WriteCommData(0xD102,0x00);
	SPI_WriteCommData(0xD103,0x07);
	SPI_WriteCommData(0xD104,0x00);
	SPI_WriteCommData(0xD105,0x0E);
	SPI_WriteCommData(0xD106,0x00);
	SPI_WriteCommData(0xD107,0x22);
	SPI_WriteCommData(0xD108,0x00);
	SPI_WriteCommData(0xD109,0x3B);
	SPI_WriteCommData(0xD10A,0x00);
	SPI_WriteCommData(0xD10B,0x71);
	SPI_WriteCommData(0xD10C,0x00);
	SPI_WriteCommData(0xD10D,0x9F);
	SPI_WriteCommData(0xD10E,0x00);
	SPI_WriteCommData(0xD10F,0xE2);
	SPI_WriteCommData(0xD110,0x01);
	SPI_WriteCommData(0xD111,0x12);
	SPI_WriteCommData(0xD112,0x01);
	SPI_WriteCommData(0xD113,0x57);
	SPI_WriteCommData(0xD114,0x01);
	SPI_WriteCommData(0xD115,0x88);
	SPI_WriteCommData(0xD116,0x01);
	SPI_WriteCommData(0xD117,0xCE);
	SPI_WriteCommData(0xD118,0x02);
	SPI_WriteCommData(0xD119,0x07);
	SPI_WriteCommData(0xD11A,0x02);
	SPI_WriteCommData(0xD11B,0x08);
	SPI_WriteCommData(0xD11C,0x02);
	SPI_WriteCommData(0xD11D,0x39);
	SPI_WriteCommData(0xD11E,0x02);
	SPI_WriteCommData(0xD11F,0x6C);
	SPI_WriteCommData(0xD120,0x02);
	SPI_WriteCommData(0xD121,0x87);
	SPI_WriteCommData(0xD122,0x02);
	SPI_WriteCommData(0xD123,0xA6);
	SPI_WriteCommData(0xD124,0x02);
	SPI_WriteCommData(0xD125,0xBA);
	SPI_WriteCommData(0xD126,0x02);
	SPI_WriteCommData(0xD127,0xD2);
	SPI_WriteCommData(0xD128,0x02);
	SPI_WriteCommData(0xD129,0xE2);
	SPI_WriteCommData(0xD12A,0x02);
	SPI_WriteCommData(0xD12B,0xF7);
	SPI_WriteCommData(0xD12C,0x03);
	SPI_WriteCommData(0xD12D,0x06);
	SPI_WriteCommData(0xD12E,0x03);
	SPI_WriteCommData(0xD12F,0x1E);
	SPI_WriteCommData(0xD130,0x03);
	SPI_WriteCommData(0xD131,0x55);
	SPI_WriteCommData(0xD132,0x03);
	SPI_WriteCommData(0xD133,0xFF);
	SPI_WriteCommData(0xD200,0x00);
	SPI_WriteCommData(0xD201,0x06);
	SPI_WriteCommData(0xD202,0x00);
	SPI_WriteCommData(0xD203,0x07);
	SPI_WriteCommData(0xD204,0x00);
	SPI_WriteCommData(0xD205,0x0E);
	SPI_WriteCommData(0xD206,0x00);
	SPI_WriteCommData(0xD207,0x22);
	SPI_WriteCommData(0xD208,0x00);
	SPI_WriteCommData(0xD209,0x3B);
	SPI_WriteCommData(0xD20A,0x00);
	SPI_WriteCommData(0xD20B,0x71);
	SPI_WriteCommData(0xD20C,0x00);
	SPI_WriteCommData(0xD20D,0x9F);
	SPI_WriteCommData(0xD20E,0x00);
	SPI_WriteCommData(0xD20F,0xE2);
	SPI_WriteCommData(0xD210,0x01);
	SPI_WriteCommData(0xD211,0x12);
	SPI_WriteCommData(0xD212,0x01);
	SPI_WriteCommData(0xD213,0x57);
	SPI_WriteCommData(0xD214,0x01);
	SPI_WriteCommData(0xD215,0x88);
	SPI_WriteCommData(0xD216,0x01);
	SPI_WriteCommData(0xD217,0xCE);
	SPI_WriteCommData(0xD218,0x02);
	SPI_WriteCommData(0xD219,0x07);
	SPI_WriteCommData(0xD21A,0x02);
	SPI_WriteCommData(0xD21B,0x08);
	SPI_WriteCommData(0xD21C,0x02);
	SPI_WriteCommData(0xD21D,0x39);
	SPI_WriteCommData(0xD21E,0x02);
	SPI_WriteCommData(0xD21F,0x6C);
	SPI_WriteCommData(0xD220,0x02);
	SPI_WriteCommData(0xD221,0x87);
	SPI_WriteCommData(0xD222,0x02);
	SPI_WriteCommData(0xD223,0xA6);
	SPI_WriteCommData(0xD224,0x02);
	SPI_WriteCommData(0xD225,0xBA);
	SPI_WriteCommData(0xD226,0x02);
	SPI_WriteCommData(0xD227,0xD2);
	SPI_WriteCommData(0xD228,0x02);
	SPI_WriteCommData(0xD229,0xE2);
	SPI_WriteCommData(0xD22A,0x02);
	SPI_WriteCommData(0xD22B,0xF7);
	SPI_WriteCommData(0xD22C,0x03);
	SPI_WriteCommData(0xD22D,0x06);
	SPI_WriteCommData(0xD22E,0x03);
	SPI_WriteCommData(0xD22F,0x1E);
	SPI_WriteCommData(0xD230,0x03);
	SPI_WriteCommData(0xD231,0x55);
	SPI_WriteCommData(0xD232,0x03);
	SPI_WriteCommData(0xD233,0xFF);

	SPI_WriteCommData(0xD300,0x00);
	SPI_WriteCommData(0xD301,0x06);
	SPI_WriteCommData(0xD302,0x00);
	SPI_WriteCommData(0xD303,0x07);
	SPI_WriteCommData(0xD304,0x00);
	SPI_WriteCommData(0xD305,0x0E);
	SPI_WriteCommData(0xD306,0x00);
	SPI_WriteCommData(0xD307,0x22);
	SPI_WriteCommData(0xD308,0x00);
	SPI_WriteCommData(0xD309,0x3B);
	SPI_WriteCommData(0xD30A,0x00);
	SPI_WriteCommData(0xD30B,0x71);
	SPI_WriteCommData(0xD30C,0x00);
	SPI_WriteCommData(0xD30D,0x9F);
	SPI_WriteCommData(0xD30E,0x00);
	SPI_WriteCommData(0xD30F,0xE2);
	SPI_WriteCommData(0xD310,0x01);
	SPI_WriteCommData(0xD311,0x12);
	SPI_WriteCommData(0xD312,0x01);
	SPI_WriteCommData(0xD313,0x57);
	SPI_WriteCommData(0xD314,0x01);
	SPI_WriteCommData(0xD315,0x88);
	SPI_WriteCommData(0xD316,0x01);
	SPI_WriteCommData(0xD317,0xCE);
	SPI_WriteCommData(0xD318,0x02);
	SPI_WriteCommData(0xD319,0x07);
	SPI_WriteCommData(0xD31A,0x02);
	SPI_WriteCommData(0xD31B,0x08);
	SPI_WriteCommData(0xD31C,0x02);
	SPI_WriteCommData(0xD31D,0x39);
	SPI_WriteCommData(0xD31E,0x02);
	SPI_WriteCommData(0xD31F,0x6C);
	SPI_WriteCommData(0xD320,0x02);
	SPI_WriteCommData(0xD321,0x87);
	SPI_WriteCommData(0xD322,0x02);
	SPI_WriteCommData(0xD323,0xA6);
	SPI_WriteCommData(0xD324,0x02);
	SPI_WriteCommData(0xD325,0xBA);
	SPI_WriteCommData(0xD326,0x02);
	SPI_WriteCommData(0xD327,0xD2);
	SPI_WriteCommData(0xD328,0x02);
	SPI_WriteCommData(0xD329,0xE2);
	SPI_WriteCommData(0xD32A,0x02);
	SPI_WriteCommData(0xD32B,0xF7);
	SPI_WriteCommData(0xD32C,0x03);
	SPI_WriteCommData(0xD32D,0x06);
	SPI_WriteCommData(0xD32E,0x03);
	SPI_WriteCommData(0xD32F,0x1E);
	SPI_WriteCommData(0xD330,0x03);
	SPI_WriteCommData(0xD331,0x55);
	SPI_WriteCommData(0xD332,0x03);
	SPI_WriteCommData(0xD333,0xFF);

	SPI_WriteCommData(0xD400,0x00);
	SPI_WriteCommData(0xD401,0x06);
	SPI_WriteCommData(0xD402,0x00);
	SPI_WriteCommData(0xD403,0x07);
	SPI_WriteCommData(0xD404,0x00);
	SPI_WriteCommData(0xD405,0x0E);
	SPI_WriteCommData(0xD406,0x00);
	SPI_WriteCommData(0xD407,0x22);
	SPI_WriteCommData(0xD408,0x00);
	SPI_WriteCommData(0xD409,0x3B);
	SPI_WriteCommData(0xD40A,0x00);
	SPI_WriteCommData(0xD40B,0x71);
	SPI_WriteCommData(0xD40C,0x00);
	SPI_WriteCommData(0xD40D,0x9F);
	SPI_WriteCommData(0xD40E,0x00);
	SPI_WriteCommData(0xD40F,0xE2);
	SPI_WriteCommData(0xD410,0x01);
	SPI_WriteCommData(0xD411,0x12);
	SPI_WriteCommData(0xD412,0x01);
	SPI_WriteCommData(0xD413,0x57);
	SPI_WriteCommData(0xD414,0x01);
	SPI_WriteCommData(0xD415,0x88);
	SPI_WriteCommData(0xD416,0x01);
	SPI_WriteCommData(0xD417,0xCE);
	SPI_WriteCommData(0xD418,0x02);
	SPI_WriteCommData(0xD419,0x07);
	SPI_WriteCommData(0xD41A,0x02);
	SPI_WriteCommData(0xD41B,0x08);
	SPI_WriteCommData(0xD41C,0x02);
	SPI_WriteCommData(0xD41D,0x39);
	SPI_WriteCommData(0xD41E,0x02);
	SPI_WriteCommData(0xD41F,0x6C);
	SPI_WriteCommData(0xD420,0x02);
	SPI_WriteCommData(0xD421,0x87);
	SPI_WriteCommData(0xD422,0x02);
	SPI_WriteCommData(0xD423,0xA6);
	SPI_WriteCommData(0xD424,0x02);
	SPI_WriteCommData(0xD425,0xBA);
	SPI_WriteCommData(0xD426,0x02);
	SPI_WriteCommData(0xD427,0xD2);
	SPI_WriteCommData(0xD428,0x02);
	SPI_WriteCommData(0xD429,0xE2);
	SPI_WriteCommData(0xD42A,0x02);
	SPI_WriteCommData(0xD42B,0xF7);
	SPI_WriteCommData(0xD42C,0x03);
	SPI_WriteCommData(0xD42D,0x06);
	SPI_WriteCommData(0xD42E,0x03);
	SPI_WriteCommData(0xD42F,0x1E);
	SPI_WriteCommData(0xD430,0x03);
	SPI_WriteCommData(0xD431,0x55);
	SPI_WriteCommData(0xD432,0x03);
	SPI_WriteCommData(0xD433,0xFF);

	SPI_WriteCommData(0xD500,0x00);
	SPI_WriteCommData(0xD501,0x06);
	SPI_WriteCommData(0xD502,0x00);
	SPI_WriteCommData(0xD503,0x07);
	SPI_WriteCommData(0xD504,0x00);
	SPI_WriteCommData(0xD505,0x0E);
	SPI_WriteCommData(0xD506,0x00);
	SPI_WriteCommData(0xD507,0x22);
	SPI_WriteCommData(0xD508,0x00);
	SPI_WriteCommData(0xD509,0x3B);
	SPI_WriteCommData(0xD50A,0x00);
	SPI_WriteCommData(0xD50B,0x71);
	SPI_WriteCommData(0xD50C,0x00);
	SPI_WriteCommData(0xD50D,0x9F);
	SPI_WriteCommData(0xD50E,0x00);
	SPI_WriteCommData(0xD50F,0xE2);
	SPI_WriteCommData(0xD510,0x01);
	SPI_WriteCommData(0xD511,0x12);
	SPI_WriteCommData(0xD512,0x01);
	SPI_WriteCommData(0xD513,0x57);
	SPI_WriteCommData(0xD514,0x01);
	SPI_WriteCommData(0xD515,0x88);
	SPI_WriteCommData(0xD516,0x01);
	SPI_WriteCommData(0xD517,0xCE);
	SPI_WriteCommData(0xD518,0x02);
	SPI_WriteCommData(0xD519,0x07);
	SPI_WriteCommData(0xD51A,0x02);
	SPI_WriteCommData(0xD51B,0x08);
	SPI_WriteCommData(0xD51C,0x02);
	SPI_WriteCommData(0xD51D,0x39);
	SPI_WriteCommData(0xD51E,0x02);
	SPI_WriteCommData(0xD51F,0x6C);
	SPI_WriteCommData(0xD520,0x02);
	SPI_WriteCommData(0xD521,0x87);
	SPI_WriteCommData(0xD522,0x02);
	SPI_WriteCommData(0xD523,0xA6);
	SPI_WriteCommData(0xD524,0x02);
	SPI_WriteCommData(0xD525,0xBA);
	SPI_WriteCommData(0xD526,0x02);
	SPI_WriteCommData(0xD527,0xD2);
	SPI_WriteCommData(0xD528,0x02);
	SPI_WriteCommData(0xD529,0xE2);
	SPI_WriteCommData(0xD52A,0x02);
	SPI_WriteCommData(0xD52B,0xF7);
	SPI_WriteCommData(0xD52C,0x03);
	SPI_WriteCommData(0xD52D,0x06);
	SPI_WriteCommData(0xD52E,0x03);
	SPI_WriteCommData(0xD52F,0x1E);
	SPI_WriteCommData(0xD530,0x03);
	SPI_WriteCommData(0xD531,0x55);
	SPI_WriteCommData(0xD532,0x03);
	SPI_WriteCommData(0xD533,0xFF);

	SPI_WriteCommData(0xD600,0x00);
	SPI_WriteCommData(0xD601,0x06);
	SPI_WriteCommData(0xD602,0x00);
	SPI_WriteCommData(0xD603,0x07);
	SPI_WriteCommData(0xD604,0x00);
	SPI_WriteCommData(0xD605,0x0E);
	SPI_WriteCommData(0xD606,0x00);
	SPI_WriteCommData(0xD607,0x22);
	SPI_WriteCommData(0xD608,0x00);
	SPI_WriteCommData(0xD609,0x3B);
	SPI_WriteCommData(0xD60A,0x00);
	SPI_WriteCommData(0xD60B,0x71);
	SPI_WriteCommData(0xD60C,0x00);
	SPI_WriteCommData(0xD60D,0x9F);
	SPI_WriteCommData(0xD60E,0x00);
	SPI_WriteCommData(0xD60F,0xE2);
	SPI_WriteCommData(0xD610,0x01);
	SPI_WriteCommData(0xD611,0x12);
	SPI_WriteCommData(0xD612,0x01);
	SPI_WriteCommData(0xD613,0x57);
	SPI_WriteCommData(0xD614,0x01);
	SPI_WriteCommData(0xD615,0x88);
	SPI_WriteCommData(0xD616,0x01);
	SPI_WriteCommData(0xD617,0xCE);
	SPI_WriteCommData(0xD618,0x02);
	SPI_WriteCommData(0xD619,0x07);
	SPI_WriteCommData(0xD61A,0x02);
	SPI_WriteCommData(0xD61B,0x08);
	SPI_WriteCommData(0xD61C,0x02);
	SPI_WriteCommData(0xD61D,0x39);
	SPI_WriteCommData(0xD61E,0x02);
	SPI_WriteCommData(0xD61F,0x6C);
	SPI_WriteCommData(0xD620,0x02);
	SPI_WriteCommData(0xD621,0x87);
	SPI_WriteCommData(0xD622,0x02);
	SPI_WriteCommData(0xD623,0xA6);
	SPI_WriteCommData(0xD624,0x02);
	SPI_WriteCommData(0xD625,0xBA);
	SPI_WriteCommData(0xD626,0x02);
	SPI_WriteCommData(0xD627,0xD2);
	SPI_WriteCommData(0xD628,0x02);
	SPI_WriteCommData(0xD629,0xE2);
	SPI_WriteCommData(0xD62A,0x02);
	SPI_WriteCommData(0xD62B,0xF7);
	SPI_WriteCommData(0xD62C,0x03);
	SPI_WriteCommData(0xD62D,0x06);
	SPI_WriteCommData(0xD62E,0x03);
	SPI_WriteCommData(0xD62F,0x1E);
	SPI_WriteCommData(0xD630,0x03);
	SPI_WriteCommData(0xD631,0x55);
	SPI_WriteCommData(0xD632,0x03);
	SPI_WriteCommData(0xD633,0xFF);

	//LV2 Page 0 enable
	SPI_WriteCommData(0xF000,0x55);
	SPI_WriteCommData(0xF001,0xAA);
	SPI_WriteCommData(0xF002,0x52);
	SPI_WriteCommData(0xF003,0x08);
	SPI_WriteCommData(0xF004,0x00);

	////480x800
	//SPI_WriteCommData(0xB500, 0x50);
	//Display control
	SPI_WriteCommData(0xB100, 0xFC);
	SPI_WriteCommData(0xB101, 0x00);

	//Source hold time
	SPI_WriteCommData(0xB600,0x05);

	//Gate EQ control
	SPI_WriteCommData(0xB700,0x70);
	SPI_WriteCommData(0xB701,0x70);

	//Source EQ control (Mode 2)
	SPI_WriteCommData(0xB800,0x01);
	SPI_WriteCommData(0xB801,0x03);
	SPI_WriteCommData(0xB802,0x03);
	SPI_WriteCommData(0xB803,0x03);

	//Frame rate
	SPI_WriteCommData(0xBD00,0x01); //800x480 60Hz
	SPI_WriteCommData(0xBD01,0x84);
	SPI_WriteCommData(0xBD02,0x08);//SPI_WriteCommData(0xBD02,0x80);
	SPI_WriteCommData(0xBD03,0x1c);//SPI_WriteCommData(0xBD03,0x30);
	SPI_WriteCommData(0xBD04,0x00);

	//Inversion mode  (2-dot)
	SPI_WriteCommData(0xBC00,0x00);
	SPI_WriteCommData(0xBC01,0x00);
	SPI_WriteCommData(0xBC02,0x00);

	//Timing control 4H w/ 4-delay
	SPI_WriteCommData(0xC900,0x00);
	SPI_WriteCommData(0xC901,0x02);
	SPI_WriteCommData(0xC902,0x50);
	SPI_WriteCommData(0xC903,0x50);
	SPI_WriteCommData(0xC904,0x50);

	//SPI_WriteCommData(0x3500,0x00);
	SPI_WriteComm(0x3500); SPI_WriteData(0x00);// M
	SPI_WriteComm(0x4400); SPI_WriteData(0x01);// M
	SPI_WriteComm(0x4401); SPI_WriteData(0x22);// M

	//TFT_PIN_SCS_HIGH();
	d_task_wait(120);
	//TFT_PIN_SCS_LOW();
	SPI_WriteComm(0x2900); //SPI_WriteData(0x00);
	//Delay(10);
	//SPI_WriteComm(0x2C00); //SPI_WriteData(0x00);
	//TFT_PIN_SCS_HIGH();

	//Delay(150);
	//TFT_PIN_SCS_LOW();
	SPI_WriteCommData(0x3600,0x20); //SPI_WriteData(0x00);
	//Delay(10);
	//SPI_WriteComm(0x2C00); //SPI_WriteData(0x00);
	//TFT_PIN_SCS_HIGH();
	//SPI_WriteComm(0x2800); //SPI_WriteData(0x00);
	//SPI_WriteComm(0x2200); //SPI_WriteData(0x00);   
	
#endif	
}

void lcd_1638_mute (D_Bool mute)
{
	if(mute)d_gpio_set(MUTEIO);
	else mute_gpio_set();
}


void lcd_1638_stand_by (void)
{
	SPI_WriteComm(0x1000);
	lcd_1638_mute(D_TRUE);
	d_gpio_clear(FANEN);
}
void lcd_1638_stand_wake_up (void)
{
	lcd_1638_init();
	lcd_1638_mute(D_FALSE);
	d_gpio_set(FANEN);
}


void SPI_WriteData_test(D_U8 mode)
{

	SPI_WriteComm(0x3600);	  SPI_WriteData(0x20);
	//colum
	SPI_WriteComm(0x2A00);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2A01);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2A02);	  SPI_WriteData(0x03);
	SPI_WriteComm(0x2A03);	  SPI_WriteData(0x1F);
	//page
	SPI_WriteComm(0x2B00);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2B01);	  SPI_WriteData(0x00);
	SPI_WriteComm(0x2B02);	  SPI_WriteData(0x01);
	SPI_WriteComm(0x2B03);	  SPI_WriteData(0xDF);
	
}

