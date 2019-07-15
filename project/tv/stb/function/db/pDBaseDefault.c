/**@defgroup db 数据库定制应用
*@{*/
/** @file
* @brief 数据库恢复出厂设置模块
* @author 刘伟峰
* @date 2013-04-01 刘伟峰: 建立文件
*/

#include "dVarString.h"
#include "dMem.h"
#include "pMem.h"
#include "dMMan.h"
#include "dDBaseInternal.h"
#include "dDBase.h"
#include "dDebug.h"
#include "pDBaseDefault.h"


#ifdef P_DBASE_DVBS 

/** @brief 定义预置天线数 */
#define DEFAULT_ANTE_NUM	sizeof(default_ante_list)/sizeof(default_ante_list[0])
/** @brief DVBS预置天线列表（元素依次为频率1、频率2、LNBType、天线的列表序号） */
const static D_U16 default_ante_list[][4]	=
{
	{5150,	0,0,1},			
	{5750,	0,0,2},		
	{5950,	0,0,3},		
	{9750,	0,0,4},		
	{10000,	0,0,5},
	{10050,	0,0,6},
	{10450,	0,0,7},
	{10600,	0,0,8},
	{10700,	0,0,9},
	{10750,	0,0,10},
	{11250,	0,0,11},
	{11300,	0,0,12},
	{5150,	5750,1,13}, 		
	{5750,	5150,1,14},		
	{9750,	10600,2,15},		
};

/** @brief 定义预置卫星数 */
#define DEFAULT_SAT_NUM		sizeof(default_sat_list)/sizeof(default_sat_list[0])
/** @brief DVBS预置卫星列表（元素依次为卫星所在的天线列表序号、经度、卫星的列表序号）*/
const static D_S32 default_sat_list[][3] = 
{
	{15,  1300,1},
	{15,  2600,2},
	{15, -17300,3},
	{15,   500,4},
	{15,   700,5},
	{15,   710,6},
	{15,   900,7},
	{15,  1000,8},
	{15,  1600,9},
	{15,  1600,10},
	{15,  1920,11},
	{15,  2350,12},
	{15,  2550,13},
	{15,  2600,14},
	{1,  2610,15},
	{15,  2820,16},
	{15,  3050,17},
	{15,  3300,18},
	{15,  3600,19},
	{15,  3900,20},
	{1,  4010,21},
	{15,  4200,22},
	{15,  5700,23},
	{15,  6000,24},
	{15,  6200,25},
	{15,  6850,26},
	{1,  6860,27},
	{1,  7650,28},
	{15,  7650,29},
	{1,  7850,30},
	{15,  7850,31},
	{15,  8000,32},
	{15,  8300,33},
	{1,  8310,34},
	{1,  8750,35},
	{1,  8800,36},
	{15,  8800,37},
	{1,  9000,38},
	{15,  9000,39},
	{1,  9150,40},
	{15,  9150,41},
	{15,  9500,42},
	{1, 10050,43},
	{15, 10050,44},
	{1, 10550,45},
	{15, 10550,46},
	{1, 10800,47},
	{1, 11050,48},
	{1, 11300,49},
	{15, 11300,50},
	{1, 11550,51},
	{15, 11600,52},
	{1, 12000,53},
	{1, 12200,54},
	{15, 12200,55},
	{15, 12400,56},
	{1, 12800,57},
	{15, 12800,58},
	{1, 13400,59},
	{15, 13400,60},
	{15, 13800,61},
	{1, 13800, 62},
	{15, 14400,63},
	{1, 14600,64},
	{15, 14600,65},
	{15, 14800,66},
	{15, -12700,67},
	{15, -13500,68},
	{1, -14260,69},
	{15, -14850,70},
	{15, -15000,71},
	{15, -15800,72},
	{15, -16200,73},
	{15, -16500,74},
	{15, -16750,75},
	{15, -16900,76},
	{15, -17200,77},
	{15, -17500,78},
	{15, -17600,79},
	{15, -17610,80},
	{15, -17900,81},
	{1, 13200,82},
	{15, 13200,83},
	{15,    0,84},
	{15,    0,85},
	{15,    0,86},
	{15,    0,87},
	{15,    0,88},
};

/** @brief DVBS预置卫星名称列表 */
const static D_Char default_sat_name_list[][36] = 
{
	{"Hotbird"},
	{"Badr/Arab"},
	{"Nile01/02"},
	{"Sirius2/3"},
	{"Eutelsat_E"},
	{"Eutelsat_SA"},
	{"Eurobird_E"},
	{"Eutelsat_W1"},
	{"EutelW2"},
	{"EutelW2_EA"},
	{"Astra1B2C"},
	{"Astra1D/3A"},
	{"Eurobird2"},
	{"BadrC/3"},
	{"Badr_C_E_Af"},
	{"Astra_2A_B"},
	{"Arabsat_2b"},
	{"Eurobird3"},
	{"Eutelsat_W4"},
	{"Hellassat2"},
	{"ExpressAM1"},
	{"Turk1C"},
	{"NSSK_ku"},
	{"Intel904KU"},
	{"Intel902KU"},
	{"IntelSat710"},
	{"CintelSat7"},
	{"Telstar10C"},
	{"Telstar10Ku"},
	{"Thaicom23C"},
	{"Thaicom23Ku"},
	{"Express_AM2"},
	{"INSAT_3B4A"},
	{"Insat2E3B"},
	{"ChinaStar1"},
	{"St1C"},
	{"St1Ku"},
	{"Yamal102c"},
	{"Yamal102"},
	{"Measat_1C"},
	{"Measat_1Ku"},
	{"NSS_6"},
	{"Asia2C"},
	{"Asia2Ku"},
	{"Asia3SC"},
	{"Asia3SKu"},
	{"Telkom_1C"},
	{"Sino1C"},
	{"PalapaC2C"},
	{"PalapaC2Ku"},
	{"ChntelSat6B"},
	{"Korea3"},
	{"Thaicom1A"},
	{"AsiaSat_4C"},
	{"AsiaSat_4Ku"},
	{"JCSAT_4A"},
	{"JCSat3C"},
	{"JCSat3Ku"},
	{"Apstar6C"},
	{"Apstar6Ku"},
	{"TelStar_Ku"},
	{"TelStar_C"},
	{"Superbird"},
	{"AgilaC"},
	{"AgilaKu"},
	{"MEASAT_2"},
	{"Intel707Ku"},
	{"IntelSat1R"},
	{"C_NSS10"},
	{"IntelSat801"},
	{"Hispasat"},
	{"NSS_7"},
	{"IntelSat901"},
	{"Telstar_12"},
	{"Atlantic"},
	{"Express3A"},
	{"AtlanticB2"},
	{"AtlanticB3"},
	{"AmosEurope"},
	{"AmosMideast"},
	{"Thor_2_3"},
	{"Vietnam_2c"},
	{"Vietnam_2ku"},
	{"USER1"},
	{"USER2"},
	{"USER3"},
	{"USER4"},
	{"USER5"},
};

/** @brief 定义DVBS下的预置TS数目 */
#define DEFAULT_DVBS_TS_NUM	sizeof(default_dvbs_ts_list)/sizeof(default_dvbs_ts_list[0])
/** @brief DVBS预置TS列表（元素依次为TS所在的卫星列表序号、频率、符号率、极化方式、TS的列表序号） */
const static D_U32 default_dvbs_ts_list[][5] = 
{
	{1,12020,28800,1,1},
	{1,12060,28800,1,2},
	{1,12100,28800,1,3},
	{1,12140,28800,1,4},
	{1,11840,28800,0,5},
	{1,11880,28800,0,6},
	{1,11920,28800,0,7},
	{1,11960,28800,0,8},
	{1,12180,28800,1,9},
	{1,12220,28800,1,10},
	{1,12260,28800,1,11},
	{1,12300,28800,1,12},
	{1,12340,27500,1,13},
	{1,12380,27500,1,14},
	{1,12400,27500,1,15},
	{1,12420,27500,0,16},
	{1,12440,27500,0,17},
	{1,12460,27500,0,18},
	{1,12470,27500,1,19},
	{1,12480,27500,1,20},
	{1,12490,27500,1,21},
};

/** @brief 定义预置服务数目 */
#define DEFAULT_SRV_NUM	sizeof(default_srv_list)/sizeof(default_srv_list[0])
/** @brief 预置服务列表（元素依次为服务所在的TS列表序号、服务类型、P_PID、V_PID、A1_PID、A2_PID） */
const static D_U32 default_srv_list[][6] = 
{
	{1,0,137,521,676,0},
	{1,0,133,517,660,0},
	{1,0,130,514,648,0},
	{1,0,131,515,652,0},
	{1,0,128,1160,1120,0},
	{1,0,129,1260,1220,0},
	{1,0,1110,1110,1120,0},
	{1,0,1510,1510,1520,0},
	{1,0,1010,1010,1011,0},
	{1,0,1060,1060,1061,0},
	{1,0,8190,1070,1071,0},
	{1,0,8190,1070,1081,0},
	{1,0,1090,1090,1091,0},
	{1,0,1120,1120,1121,0},
	{1,0,1300,1300,1301,0},
	{1,0,2020,2020,2021,0},
	{1,0,1360,1360,1320,0},
	{1,0,58,58,59,0},
	{1,0,656,656,657,0},
	{1,0,664,661,662,0},
	{1,0,704,701,702,0},
	{1,0,711,711,712,0},
	{1,0,723,721,722,0},
	{1,0,7160,7160,7120,0},
	{1,0,7160,7160,7122,0},
	{1,0,7160,7160,7222,0},
	{1,0,7460,7460,7420,0},
	{1,0,7960,7960,7920,0},
	{1,0,2020,2020,2021,0},
	{1,0,2030,2030,2031,0},
	{1,0,2040,2040,2041,0},
	{1,0,2050,2050,2051,0},
	{1,0,33,33,34,0},
	{1,0,256,256,258,0},
	{1,0,128,512,640,0},
	{1,0,129,513,641,0},
	{1,0,130,514,642,0},
	{1,0,131,515,643,0},
	{1,0,33,33,34,0},
	{1,0,65,65,66,0},
	{1,0,33,33,36,0},
	{1,0,258,3601,3604,0},
	{1,0,8177,308,256,0},
	{1,0,8178,35,36,0},
	{1,0,256,256,258,0},
	{1,0,501,501,502,0},
	{1,0,301,302,303,0},
	{1,0,8190,516,656,0},
	{1,0,129,513,660,0},
	{1,0,130,514,670,0},
	{1,0,131,515,680,0},
	{1,0,132,516,690,0},
	{1,0,133,517,700,0},
	{1,0,134,518,710,0},
	{1,0,135,519,720,0},
	{1,0,8160,8160,8120,0},
	{1,0,128,512,650,0},
	{1,0,129,513,660,0},
	{1,0,130,514,670,0},
	{1,0,32,32,33,0},
	{1,0,3301,3301,3302,0},
	{1,0,4105,4105,4106,0},
	{1,0,8190,308,256,0},
	{1,0,49,49,924,0},
	{1,0,785,785,60,0},
	{1,0,791,791,841,0},
	{1,0,40,40,39,0},
	{1,0,128,512,650,0},
	{1,0,514,514,670,0},
	{1,0,515,515,680,0},
	{1,0,516,516,690,0},
	{1,0,134,518,710,0},
	{1,0,8190,308,256,0},
	{1,0,101,101,201,0},
	{1,1,791,791,841,0},
	{1,1,40,40,39,0},
	{1,1,128,512,650,0},
	{1,1,514,514,670,0},
	{1,1,515,515,680,0},
	{1,1,516,516,690,0},
	{1,1,134,518,710,0},
	{1,1,8190,308,256,0},
	{1,1,101,101,201,0},
};

/** @brief 预置服务名称列表 */
const static D_Char default_srv_name_list[][36] = 
{
	{"凤凰卫视资讯台"},
	{"凤凰卫视中文台"},
	{"星空卫视"},
	{"音乐台中国频道"},
	{"新加坡亚洲新闻台"},
	{"新加坡亚洲新闻台"},
	{"香港无线8频道"},
	{"华娱卫视"},
	{"香港世界网络频道"},
	{"今日俄罗斯"},
	{"Muslim TV1"},
	{"Muslim TV2"},
	{"半岛电视台国际"},
	{"法国国营电视5台"},
	{"DW-TVASIEN"},
	{"DW-TV ASIA+"},
	{"NHK World"},
	{"中华卫视神州台"},
	{"预备频道潮商卫视"},
	{"阳光卫视"},
	{"新亚东风"},
	{"莲花卫视"},
	{"凤凰卫视香港台"},
	{"美国之音"},
	{"IBB VOA FFE"},
	{"VOA Radio"},
	{"美国之音"},
	{"VOA IOR"},
	{"Isaac TV"},
	{"Paigham TV"},
	{"蓝海电视"},
	{"DM Digital"},
	{"Awrz TV"},
	{"Shamshad TV"},
	{"Hum TV"},
	{"Masala TV"},
	{"Style 360"},
	{"Hum TV USA"},
	{"A-Plus"},
	{"A-Lite"},
	{"AAJ NEWS"},
	{"TV ONE"},
	{"Waseb TV"},
	{"NEWS ONE"},
	{"Shamshad TV"},
	{"B4U音乐台"},
	{"B4U电影台"},
	{"STAR UTSAV"},
	{"Sahara NAT"},
	{"Sahara NCR"},
	{"Sahara MUM"},
	{"Sahara UP"},
	{"Sahara BIH"},
	{"Aalami Sahara"},
	{"Sahara MP"},
	{"VOA Persian"},
	{"PTV HOME"},
	{"PTV NEWS"},
	{"ATV"},
	{"ZING"},
	{"ZEE Smile"},
	{"Zee 36GARH"},
	{"Such TV"},
	{"AVT KHYBER"},
	{"KHYBER NEWS"},
	{"K2"},
	{"尼克动画频道"},
	{"ARY Digtal"},
	{"ARY QTV"},
	{"ARY Musik"},
	{"ARY Digtal"},
	{"ARY News"},
	{"PTV GLOBAL USA"},
	{"GEO News"},
	{ "K2" },
	{ "尼克动画频道" },
	{ "ARY Digtal" },
	{ "ARY QTV" },
	{ "ARY Musik" },
	{ "ARY Digtal" },
	{ "ARY News" },
	{ "PTV GLOBAL USA" },
	{ "GEO News" },
};

#else

	#ifdef DTMB
	#undef DTMB
	#endif
	#ifdef DVBC_B1
	#undef DVBC_B1
	#endif
	#ifdef DVBC_B2
	#undef DVBC_B2
	#endif
	#ifdef DVBC_C1
	#undef DVBC_C1
	#endif
	#ifdef DVBC_C2
	#undef DVBC_C2
	#endif
	
	#define DVBC_C1
	
	#ifdef DTMB
		/** @brief 定义预置TS个数 */
		#define DEFAULT_TS_NUM	sizeof(default_ts_list)/sizeof(default_ts_list[0])
		/** @brief 预置TS列表（元素依次为TS的列表序号、频率） */
		const static D_U32 default_ts_list[][2] = 
		{
			{1,474},
			{2,482},
			{3,490},
			{4,498},
			{5,506},
			{6,514},
			{7,522},
			{8,530},
			{9,538},
			{10,546},
			{11,554},
			{12,562},
			{13,570},
			{14,578},
			{15,586},
			{16,594},
			{17,602},
			{18,610},
			{19,618},
			{20,626},
			{21,634},
			{22,642},
			{23,650},
			{24,658},
			{25,666},
			{26,674},
			{27,682},
			{28,690},
			{29,698},
			{30,706},
			{31,714},
			{32,722},
			{33,730},
			{34,738},
			{35,746},
			{36,754},
			{37,762},
			{38,770},
			{39,778},
			{40,786},
			{41,794},
			{42,802},
			{43,810},
			{44,818},
			{45,826},
			{46,834},
			{47,842},
			{48,850},
			{49,858},
			{50,171},
			{51,179},
			{52,187},
			{53,195},
			{54,203},
			{55,211},
			{56,219},
		};
		/** @brief 定义预置服务数目 */
		#define DEFAULT_SRV_NUM	sizeof(default_srv_list)/sizeof(default_srv_list[0])
		/** @brief 预置服务列表（元素依次为服务所在的TS列表序号、服务类型、P_PID、V_PID、A1_PID、A2_PID） */
		const static D_U32 default_srv_list[][6] = 
		{
			{1,0,0x100,0x100,0x110,0x20},
			{2,0,0x100,0x100,0x110,0x20},
			{3,0,0x100,0x100,0x110,0x20},
			{4,0,0x100,0x100,0x110,0x20},
			{5,0,0x100,0x100,0x110,0x20},
			{6,0,0x100,0x100,0x110,0x20},
			{7,0,0x100,0x100,0x110,0x20},
			{8,0,0x100,0x100,0x110,0x20},
			{9,0,0x100,0x100,0x110,0x20},
			{10,0,0x100,0x100,0x110,0x20},
			{11,0,0x100,0x100,0x110,0x20},
			{12,0,0x100,0x100,0x110,0x20},
			{13,0,0x100,0x100,0x110,0x20},
			{14,0,0x100,0x100,0x110,0x20},
			{15,0,0x100,0x100,0x110,0x20},
			{16,0,0x100,0x100,0x110,0x20},
			{17,0,0x100,0x100,0x110,0x20},
			{18,0,0x100,0x100,0x110,0x20},
			{19,0,0x100,0x100,0x110,0x20},
			{20,0,0x100,0x100,0x110,0x20},
			{21,0,0x100,0x100,0x110,0x20},
			{22,0,0x100,0x100,0x110,0x20},
			{23,0,0x100,0x100,0x110,0x20},
			{24,0,0x100,0x100,0x110,0x20},
			{25,0,0x100,0x100,0x110,0x20},
			{26,0,0x100,0x100,0x110,0x20},
			{27,0,0x100,0x100,0x110,0x20},
			{28,0,0x100,0x100,0x110,0x20},
			{29,0,0x100,0x100,0x110,0x20},
			{30,0,0x100,0x100,0x110,0x20},
			{31,0,0x100,0x100,0x110,0x20},
			{32,0,0x100,0x100,0x110,0x20},
			{33,0,0x100,0x100,0x110,0x20},
			{34,0,0x100,0x100,0x110,0x20},
			{35,0,0x100,0x100,0x110,0x20},
			{36,0,0x100,0x100,0x110,0x20},
			{37,0,0x100,0x100,0x110,0x20},
			{38,0,0x100,0x100,0x110,0x20},
			{39,0,0x100,0x100,0x110,0x20},
			{40,0,0x100,0x100,0x110,0x20},
			{41,0,0x100,0x100,0x110,0x20},
			{42,0,0x100,0x100,0x110,0x20},
			{43,0,0x100,0x100,0x110,0x20},
			{44,0,0x100,0x100,0x110,0x20},
			{45,0,0x100,0x100,0x110,0x20},
			{46,0,0x100,0x100,0x110,0x20},
			{47,0,0x100,0x100,0x110,0x20},
			{48,0,0x100,0x100,0x110,0x20},
			{49,0,0x100,0x100,0x110,0x20},
			{50,0,0x100,0x100,0x110,0x20},
			{51,0,0x100,0x100,0x110,0x20},
			{52,0,0x100,0x100,0x110,0x20},
			{53,0,0x100,0x100,0x110,0x20},
			{54,0,0x100,0x100,0x110,0x20},
			{55,0,0x100,0x100,0x110,0x20},
			{56,0,0x100,0x100,0x110,0x20},
		};
		/** @brief 预置服务名称列表 */
		const static D_Char default_srv_name_list[][36] = 
		{
			{"474_Diver"},
			{"482_Diver "},
			{"490_Diver "},
			{"498_Diver"},
			{"506_Diver "},
			{"514_Diver "},
			{"522_Diver"},
			{"530_Diver "},
			{"538_Diver "},
			{"546_Diver"},
			{"554_Diver "},
			{"562_Diver "},
			{"570_Diver"},
			{"578_Diver "},
			{"586_Diver "},
			{"594_Diver"},
			{"602_Diver "},
			{"610_Diver "},
			{"618_Diver"},
			{"626_Diver "},
			{"634_Diver "},
			{"642_Diver"},
			{"650_Diver "},
			{"658_Diver "},
			{"666_Diver"},
			{"674_Diver "},
			{"682_Diver "},
			{"690_Diver"},
			{"698_Diver "},
			{"706_Diver "},
			{"714_Diver"},
			{"722_Diver "},
			{"730_Diver "},
			{"738_Diver"},
			{"746_Diver "},
			{"754_Diver "},
			{"762_Diver"},
			{"770_Diver "},
			{"778_Diver "},
			{"786_Diver"},
			{"794_Diver "},
			{"802_Diver "},
			{"810_Diver"},
			{"818_Diver "},
			{"826_Diver "},
			{"834_Diver"},
			{"842_Diver "},
			{"850_Diver "},
			{"858_Diver"},
			{"171_Diver "},
			{"179_Diver "},
			{"187_Diver"},
			{"195_Diver "},
			{"203_Diver "},
			{"211_Diver"},
			{"219_Diver "},
		};
	#endif
	
	#ifdef DVBC_B1
		/** @brief 定义预置TS个数 */
		#define DEFAULT_TS_NUM	sizeof(default_ts_list)/sizeof(default_ts_list[0])
		/** @brief 预置TS列表（元素依次为TS的列表序号、频率、符号率、调制方式） */
		const static D_U32 default_ts_list[][4] = 
		{
			{1,115,6875,2},
			{2,139,6875,2},
			{3,187,6875,2},
			{4,235,6875,2},
			{5,283,6875,2},
			{6,331,6875,2},
			{7,379,6875,2},
			{8,427,6875,2},
			{9,474,6875,2},
			{10,522,6875,2},
			{11,570,6875,2},
			{12,618,6875,2},
			{13,666,6875,2},
			{14,714,6875,2},
			{15,762,6875,2},
			{16,810,6875,2},
			{17,850,6875,2},
			{18,858,6875,2},
		};
		/** @brief 定义预置服务数目 */
		#define DEFAULT_SRV_NUM	sizeof(default_srv_list)/sizeof(default_srv_list[0])
		/** @brief 预置服务列表（元素依次为服务所在的TS列表序号、服务类型、P_PID、V_PID、A1_PID、A2_PID） */
		const static D_U32 default_srv_list[][6] = 
		{
			{1,0,0x100,0x100,0x110,0x20},
			{2,0,0x100,0x100,0x110,0x20},
			{3,0,0x100,0x100,0x110,0x20},
			{4,0,0x100,0x100,0x110,0x20},
			{5,0,0x100,0x100,0x110,0x20},
			{6,0,0x100,0x100,0x110,0x20},
			{7,0,0x100,0x100,0x110,0x20},
			{8,0,0x100,0x100,0x110,0x20},
			{9,0,0x100,0x100,0x110,0x20},
			{10,0,0x100,0x100,0x110,0x20},
			{11,0,0x100,0x100,0x110,0x20},
			{12,0,0x100,0x100,0x110,0x20},
			{13,0,0x100,0x100,0x110,0x20},
			{14,0,0x100,0x100,0x110,0x20},
			{15,0,0x100,0x100,0x110,0x20},
			{16,0,0x100,0x100,0x110,0x20},
			{17,0,0x100,0x100,0x110,0x20},
			{18,0,0x100,0x100,0x110,0x20},
		};
		/** @brief 预置服务名称列表 */
		const static D_Char default_srv_name_list[][36] = 
		{
			{"115_Diver"},
			{"139_Diver "},
			{"187_Diver "},
			{"235_Diver"},
			{"283_Diver "},
			{"331_Diver "},
			{"379_Diver"},
			{"427_Diver "},
			{"474_Diver "},
			{"522_Diver"},
			{"570_Diver "},
			{"618_Diver "},
			{"666_Diver"},
			{"714_Diver "},
			{"762_Diver "},
			{"810_Diver"},
			{"850_Diver "},
			{"858_Diver "},
		};
	#endif
	
	#ifdef DVBC_B2
		/** @brief 定义预置TS个数 */
		#define DEFAULT_TS_NUM	sizeof(default_ts_list)/sizeof(default_ts_list[0])
		/** @brief 预置TS列表（元素依次为TS的列表序号、频率、符号率、调制方式） */
		const static D_U32 default_ts_list[][4] = 
		{
			{1,115,6875,4},
			{2,139,6875,4},
			{3,187,6875,4},
			{4,235,6875,4},
			{5,283,6875,4},
			{6,331,6875,4},
			{7,379,6875,4},
			{8,427,6875,4},
			{9,474,6875,4},
			{10,522,6875,4},
			{11,570,6875,4},
			{12,618,6875,4},
			{13,666,6875,4},
			{14,714,6875,4},
			{15,762,6875,4},
			{16,810,6875,4},
			{17,850,6875,4},
			{18,858,6875,4},
		};
		/** @brief 定义预置服务数目 */
		#define DEFAULT_SRV_NUM	sizeof(default_srv_list)/sizeof(default_srv_list[0])
		/** @brief 预置服务列表（元素依次为服务所在的TS列表序号、服务类型、P_PID、V_PID、A1_PID、A2_PID） */
		const static D_U32 default_srv_list[][6] = 
		{
			{1,0,0x100,0x100,0x110,0x20},
			{2,0,0x100,0x100,0x110,0x20},
			{3,0,0x100,0x100,0x110,0x20},
			{4,0,0x100,0x100,0x110,0x20},
			{5,0,0x100,0x100,0x110,0x20},
			{6,0,0x100,0x100,0x110,0x20},
			{7,0,0x100,0x100,0x110,0x20},
			{8,0,0x100,0x100,0x110,0x20},
			{9,0,0x100,0x100,0x110,0x20},
			{10,0,0x100,0x100,0x110,0x20},
			{11,0,0x100,0x100,0x110,0x20},
			{12,0,0x100,0x100,0x110,0x20},
			{13,0,0x100,0x100,0x110,0x20},
			{14,0,0x100,0x100,0x110,0x20},
			{15,0,0x100,0x100,0x110,0x20},
			{16,0,0x100,0x100,0x110,0x20},
			{17,0,0x100,0x100,0x110,0x20},
			{18,0,0x100,0x100,0x110,0x20},
		};
		/** @brief 预置服务名称列表 */
		const static D_Char default_srv_name_list[][36] = 
		{
			{"115_Diver"},
			{"139_Diver "},
			{"187_Diver "},
			{"235_Diver"},
			{"283_Diver "},
			{"331_Diver "},
			{"379_Diver"},
			{"427_Diver "},
			{"474_Diver "},
			{"522_Diver"},
			{"570_Diver "},
			{"618_Diver "},
			{"666_Diver"},
			{"714_Diver "},
			{"762_Diver "},
			{"810_Diver"},
			{"850_Diver "},
			{"858_Diver "},
		};
	#endif
	
	#ifdef DVBC_C1
		/** @brief 定义预置TS个数 */
		#define DEFAULT_TS_NUM	sizeof(default_ts_list)/sizeof(default_ts_list[0])
		/** @brief 预置TS列表（元素依次为TS的列表序号、频率、符号率、调制方式） */
		const static D_U32 default_ts_list[][4] = 
		{
			{1,115,6875,2},
			{2,123,6875,2},
			{3,131,6875,2},
			{4,139,6875,2},
			{5,147,6875,2},
			{6,155,6875,2},
			{7,163,6875,2},
			{8,171,6875,2},
			{9,179,6875,2},
			{10,187,6875,2},
			{11,195,6875,2},
			{12,203,6875,2},
			{13,211,6875,2},
			{14,219,6875,2},
			{15,227,6875,2},
			{16,235,6875,2},
			{17,243,6875,2},
			{18,251,6875,2},
			{19,259,6875,2},
			{20,267,6875,2},
			{21,275,6875,2},
			{22,283,6875,2},
			{23,291,6875,2},
			{24,299,6875,2},
			{25,307,6875,2},
			{26,315,6875,2},
			{27,323,6875,2},
			{28,331,6875,2},
			{29,339,6875,2},
			{30,347,6875,2},
			{31,355,6875,2},
			{32,363,6875,2},
			{33,371,6875,2},
			{34,379,6875,2},
			{35,387,6875,2},
			{36,395,6875,2},
			{37,403,6875,2},
			{38,411,6875,2},
			{39,419,6875,2},
			{40,427,6875,2},
			{41,435,6875,2},
			{42,443,6875,2},
			{43,451,6875,2},
			{44,459,6875,2},
			{45,467,6875,2},
			{46,474,6875,2},
			{47,482,6875,2},
			{48,490,6875,2},
			{49,498,6875,2},
			{50,506,6875,2},
			{51,514,6875,2},
			{52,522,6875,2},
			{53,530,6875,2},
			{54,538,6875,2},
			{55,546,6875,2},
			{56,554,6875,2},
			{57,562,6875,2},
			{58,570,6875,2},
			{59,578,6875,2},
			{60,586,6875,2},
			{61,594,6875,2},
			{62,602,6875,2},
			{63,610,6875,2},
			{64,618,6875,2},
			{65,626,6875,2},
			{66,634,6875,2},
			{67,642,6875,2},
			{68,650,6875,2},
			{69,658,6875,2},
			{70,666,6875,2},
			{71,674,6875,2},
			{72,682,6875,2},
			{73,690,6875,2},
			{74,698,6875,2},
			{75,706,6875,2},
			{76,714,6875,2},
			{77,722,6875,2},
			{78,730,6875,2},
			{79,738,6875,2},
			{80,746,6875,2},
			{81,754,6875,2},
			{82,762,6875,2},
			{83,770,6875,2},
			{84,778,6875,2},
			{85,786,6875,2},
			{86,794,6875,2},
			{87,802,6875,2},
			{88,810,6875,2},
			{89,818,6875,2},
			{90,826,6875,2},
			{91,834,6875,2},
			{92,842,6875,2},
			{93,850,6875,2},
			{94,858,6875,2},
		};
		/** @brief 定义预置服务数目 */
		#define DEFAULT_SRV_NUM	sizeof(default_srv_list)/sizeof(default_srv_list[0])
		/** @brief 预置服务列表（元素依次为服务所在的TS列表序号、服务类型、P_PID、V_PID、A1_PID、A2_PID） */
		const static D_U32 default_srv_list[][6] = 
		{
			{1,0,0x100,0x100,0x110,0x20},
			{2,0,0x100,0x100,0x110,0x20},
			{3,0,0x100,0x100,0x110,0x20},
			{4,0,0x100,0x100,0x110,0x20},
			{5,0,0x100,0x100,0x110,0x20},
			{6,0,0x100,0x100,0x110,0x20},
			{7,0,0x100,0x100,0x110,0x20},
			{8,0,0x100,0x100,0x110,0x20},
			{9,0,0x100,0x100,0x110,0x20},
			{10,0,0x100,0x100,0x110,0x20},
			{11,0,0x100,0x100,0x110,0x20},
			{12,0,0x100,0x100,0x110,0x20},
			{13,0,0x100,0x100,0x110,0x20},
			{14,0,0x100,0x100,0x110,0x20},
			{15,0,0x100,0x100,0x110,0x20},
			{16,0,0x100,0x100,0x110,0x20},
			{17,0,0x100,0x100,0x110,0x20},
			{18,0,0x100,0x100,0x110,0x20},
			{19,0,0x100,0x100,0x110,0x20},
			{20,0,0x100,0x100,0x110,0x20},
			{21,0,0x100,0x100,0x110,0x20},
			{22,0,0x100,0x100,0x110,0x20},
			{23,0,0x100,0x100,0x110,0x20},
			{24,0,0x100,0x100,0x110,0x20},
			{25,0,0x100,0x100,0x110,0x20},
			{26,0,0x100,0x100,0x110,0x20},
			{27,0,0x100,0x100,0x110,0x20},
			{28,0,0x100,0x100,0x110,0x20},
			{29,0,0x100,0x100,0x110,0x20},
			{30,0,0x100,0x100,0x110,0x20},
			{31,0,0x100,0x100,0x110,0x20},
			{32,0,0x100,0x100,0x110,0x20},
			{33,0,0x100,0x100,0x110,0x20},
			{34,0,0x100,0x100,0x110,0x20},
			{35,0,0x100,0x100,0x110,0x20},
			{36,0,0x100,0x100,0x110,0x20},
			{37,0,0x100,0x100,0x110,0x20},
			{38,0,0x100,0x100,0x110,0x20},
			{39,0,0x100,0x100,0x110,0x20},
			{40,0,0x100,0x100,0x110,0x20},
			{41,0,0x100,0x100,0x110,0x20},
			{42,0,0x100,0x100,0x110,0x20},
			{43,0,0x100,0x100,0x110,0x20},
			{44,0,0x100,0x100,0x110,0x20},
			{45,0,0x100,0x100,0x110,0x20},
			{46,0,0x100,0x100,0x110,0x20},
			{47,0,0x100,0x100,0x110,0x20},
			{48,0,0x100,0x100,0x110,0x20},
			{49,0,0x100,0x100,0x110,0x20},
			{50,0,0x100,0x100,0x110,0x20},
			{51,0,0x100,0x100,0x110,0x20},
			{52,0,0x100,0x100,0x110,0x20},
			{53,0,0x100,0x100,0x110,0x20},
			{54,0,0x100,0x100,0x110,0x20},
			{55,0,0x100,0x100,0x110,0x20},
			{56,0,0x100,0x100,0x110,0x20},
			{57,0,0x100,0x100,0x110,0x20},
			{58,0,0x100,0x100,0x110,0x20},
			{59,0,0x100,0x100,0x110,0x20},
			{60,0,0x100,0x100,0x110,0x20},
			{61,0,0x100,0x100,0x110,0x20},
			{62,0,0x100,0x100,0x110,0x20},
			{63,0,0x100,0x100,0x110,0x20},
			{64,0,0x100,0x100,0x110,0x20},
			{65,0,0x100,0x100,0x110,0x20},
			{66,0,0x100,0x100,0x110,0x20},
			{67,0,0x100,0x100,0x110,0x20},
			{68,0,0x100,0x100,0x110,0x20},
			{69,0,0x100,0x100,0x110,0x20},
			{70,0,0x100,0x100,0x110,0x20},
			{71,0,0x100,0x100,0x110,0x20},
			{72,0,0x100,0x100,0x110,0x20},
			{73,0,0x100,0x100,0x110,0x20},
			{74,0,0x100,0x100,0x110,0x20},
			{75,0,0x100,0x100,0x110,0x20},
			{76,0,0x100,0x100,0x110,0x20},
			{77,0,0x100,0x100,0x110,0x20},
			{78,0,0x100,0x100,0x110,0x20},
			{79,0,0x100,0x100,0x110,0x20},
			{80,0,0x100,0x100,0x110,0x20},
			{81,0,0x100,0x100,0x110,0x20},
			{82,0,0x100,0x100,0x110,0x20},
			{83,0,0x100,0x100,0x110,0x20},
			{84,0,0x100,0x100,0x110,0x20},
			{85,0,0x100,0x100,0x110,0x20},
			{86,0,0x100,0x100,0x110,0x20},
			{87,0,0x100,0x100,0x110,0x20},
			{88,0,0x100,0x100,0x110,0x20},
			{89,0,0x100,0x100,0x110,0x20},
			{90,0,0x100,0x100,0x110,0x20},
			{91,0,0x100,0x100,0x110,0x20},
			{92,0,0x100,0x100,0x110,0x20},
			{93,0,0x100,0x100,0x110,0x20},
			{94,0,0x100,0x100,0x110,0x20},
		};
		/** @brief 预置服务名称列表 */
		const static D_Char default_srv_name_list[][36] = 
		{
			{"115_Diver"},
			{"123_Diver "},
			{"131_Diver "},
			{"139_Diver"},
			{"147_Diver "},
			{"155_Diver "},
			{"163_Diver"},
			{"171_Diver "},
			{"179_Diver "},
			{"187_Diver"},
			{"195_Diver "},
			{"203_Diver "},
			{"211_Diver"},
			{"219_Diver "},
			{"227_Diver "},
			{"235_Diver"},
			{"243_Diver "},
			{"251_Diver "},
			{"259_Diver"},
			{"267_Diver "},
			{"275_Diver "},
			{"283_Diver"},
			{"291_Diver "},
			{"299_Diver "},
			{"307_Diver"},
			{"315_Diver "},
			{"323_Diver "},
			{"331_Diver"},
			{"339_Diver "},
			{"347_Diver "},
			{"355_Diver"},
			{"363_Diver "},
			{"371_Diver "},
			{"379_Diver"},
			{"387_Diver "},
			{"395_Diver "},
			{"403_Diver"},
			{"411_Diver "},
			{"419_Diver "},
			{"427_Diver"},
			{"435_Diver "},
			{"443_Diver "},
			{"451_Diver"},
			{"459_Diver "},
			{"467_Diver "},
			{"474_Diver"},
			{"482_Diver "},
			{"490_Diver "},
			{"498_Diver"},
			{"506_Diver "},
			{"514_Diver "},
			{"522_Diver"},
			{"530_Diver "},
			{"538_Diver "},
			{"546_Diver"},
			{"554_Diver "},
			{"562_Diver"},
			{"570_Diver "},
			{"578_Diver "},
			{"586_Diver"},
			{"594_Diver "},
			{"602_Diver "},
			{"610_Diver"},
			{"618_Diver "},
			{"626_Diver "},
			{"634_Diver"},
			{"642_Diver "},
			{"650_Diver "},
			{"658_Diver"},
			{"666_Diver "},
			{"674_Diver "},
			{"682_Diver"},
			{"690_Diver "},
			{"698_Diver "},
			{"706_Diver"},
			{"714_Diver "},
			{"722_Diver "},
			{"730_Diver"},
			{"738_Diver "},
			{"746_Diver "},
			{"754_Diver"},
			{"762_Diver "},
			{"770_Diver "},
			{"778_Diver"},
			{"786_Diver "},
			{"794_Diver "},
			{"802_Diver"},
			{"810_Diver "},
			{"818_Diver "},
			{"826_Diver"},
			{"834_Diver "},
			{"842_Diver "},
			{"850_Diver"},
			{"858_Diver "},
		};
	#endif
	
	#ifdef DVBC_C2
		/** @brief 定义预置TS个数 */
		#define DEFAULT_TS_NUM	sizeof(default_ts_list)/sizeof(default_ts_list[0])
		/** @brief 预置TS列表（元素依次为TS的列表序号、频率、符号率、调制方式） */
		const static D_U32 default_ts_list[][4] = 
		{
			{1,115,6875,4},
			{2,123,6875,4},
			{3,131,6875,4},
			{4,139,6875,4},
			{5,147,6875,4},
			{6,155,6875,4},
			{7,163,6875,4},
			{8,171,6875,4},
			{9,179,6875,4},
			{10,187,6875,4},
			{11,195,6875,4},
			{12,203,6875,4},
			{13,211,6875,4},
			{14,219,6875,4},
			{15,227,6875,4},
			{16,235,6875,4},
			{17,243,6875,4},
			{18,251,6875,4},
			{19,259,6875,4},
			{20,267,6875,4},
			{21,275,6875,4},
			{22,283,6875,4},
			{23,291,6875,4},
			{24,299,6875,4},
			{25,307,6875,4},
			{26,315,6875,4},
			{27,323,6875,4},
			{28,331,6875,4},
			{29,339,6875,4},
			{30,347,6875,4},
			{31,355,6875,4},
			{32,363,6875,4},
			{33,371,6875,4},
			{34,379,6875,4},
			{35,387,6875,4},
			{36,395,6875,4},
			{37,403,6875,4},
			{38,411,6875,4},
			{39,419,6875,4},
			{40,427,6875,4},
			{41,435,6875,4},
			{42,443,6875,4},
			{43,451,6875,4},
			{44,459,6875,4},
			{45,467,6875,4},
			{46,474,6875,4},
			{47,482,6875,4},
			{48,490,6875,4},
			{49,498,6875,4},
			{50,506,6875,4},
			{51,514,6875,4},
			{52,522,6875,4},
			{53,530,6875,4},
			{54,538,6875,4},
			{55,546,6875,4},
			{56,554,6875,4},
			{57,562,6875,4},
			{58,570,6875,4},
			{59,578,6875,4},
			{60,586,6875,4},
			{61,594,6875,4},
			{62,602,6875,4},
			{63,610,6875,4},
			{64,618,6875,4},
			{65,626,6875,4},
			{66,634,6875,4},
			{67,642,6875,4},
			{68,650,6875,4},
			{69,658,6875,4},
			{70,666,6875,4},
			{71,674,6875,4},
			{72,682,6875,4},
			{73,690,6875,4},
			{74,698,6875,4},
			{75,706,6875,4},
			{76,714,6875,4},
			{77,722,6875,4},
			{78,730,6875,4},
			{79,738,6875,4},
			{80,746,6875,4},
			{81,754,6875,4},
			{82,762,6875,4},
			{83,770,6875,4},
			{84,778,6875,4},
			{85,786,6875,4},
			{86,794,6875,4},
			{87,802,6875,4},
			{88,810,6875,4},
			{89,818,6875,4},
			{90,826,6875,4},
			{91,834,6875,4},
			{92,842,6875,4},
			{93,850,6875,4},
			{94,858,6875,4},
		};
		/** @brief 定义预置服务数目 */
		#define DEFAULT_SRV_NUM	sizeof(default_srv_list)/sizeof(default_srv_list[0])
		/** @brief 预置服务列表（元素依次为服务所在的TS列表序号、服务类型、P_PID、V_PID、A1_PID、A2_PID） */
		const static D_U32 default_srv_list[][6] = 
		{
			{1,0,0x100,0x100,0x110,0x20},
			{2,0,0x100,0x100,0x110,0x20},
			{3,0,0x100,0x100,0x110,0x20},
			{4,0,0x100,0x100,0x110,0x20},
			{5,0,0x100,0x100,0x110,0x20},
			{6,0,0x100,0x100,0x110,0x20},
			{7,0,0x100,0x100,0x110,0x20},
			{8,0,0x100,0x100,0x110,0x20},
			{9,0,0x100,0x100,0x110,0x20},
			{10,0,0x100,0x100,0x110,0x20},
			{11,0,0x100,0x100,0x110,0x20},
			{12,0,0x100,0x100,0x110,0x20},
			{13,0,0x100,0x100,0x110,0x20},
			{14,0,0x100,0x100,0x110,0x20},
			{15,0,0x100,0x100,0x110,0x20},
			{16,0,0x100,0x100,0x110,0x20},
			{17,0,0x100,0x100,0x110,0x20},
			{18,0,0x100,0x100,0x110,0x20},
			{19,0,0x100,0x100,0x110,0x20},
			{20,0,0x100,0x100,0x110,0x20},
			{21,0,0x100,0x100,0x110,0x20},
			{22,0,0x100,0x100,0x110,0x20},
			{23,0,0x100,0x100,0x110,0x20},
			{24,0,0x100,0x100,0x110,0x20},
			{25,0,0x100,0x100,0x110,0x20},
			{26,0,0x100,0x100,0x110,0x20},
			{27,0,0x100,0x100,0x110,0x20},
			{28,0,0x100,0x100,0x110,0x20},
			{29,0,0x100,0x100,0x110,0x20},
			{30,0,0x100,0x100,0x110,0x20},
			{31,0,0x100,0x100,0x110,0x20},
			{32,0,0x100,0x100,0x110,0x20},
			{33,0,0x100,0x100,0x110,0x20},
			{34,0,0x100,0x100,0x110,0x20},
			{35,0,0x100,0x100,0x110,0x20},
			{36,0,0x100,0x100,0x110,0x20},
			{37,0,0x100,0x100,0x110,0x20},
			{38,0,0x100,0x100,0x110,0x20},
			{39,0,0x100,0x100,0x110,0x20},
			{40,0,0x100,0x100,0x110,0x20},
			{41,0,0x100,0x100,0x110,0x20},
			{42,0,0x100,0x100,0x110,0x20},
			{43,0,0x100,0x100,0x110,0x20},
			{44,0,0x100,0x100,0x110,0x20},
			{45,0,0x100,0x100,0x110,0x20},
			{46,0,0x100,0x100,0x110,0x20},
			{47,0,0x100,0x100,0x110,0x20},
			{48,0,0x100,0x100,0x110,0x20},
			{49,0,0x100,0x100,0x110,0x20},
			{50,0,0x100,0x100,0x110,0x20},
			{51,0,0x100,0x100,0x110,0x20},
			{52,0,0x100,0x100,0x110,0x20},
			{53,0,0x100,0x100,0x110,0x20},
			{54,0,0x100,0x100,0x110,0x20},
			{55,0,0x100,0x100,0x110,0x20},
			{56,0,0x100,0x100,0x110,0x20},
			{57,0,0x100,0x100,0x110,0x20},
			{58,0,0x100,0x100,0x110,0x20},
			{59,0,0x100,0x100,0x110,0x20},
			{60,0,0x100,0x100,0x110,0x20},
			{61,0,0x100,0x100,0x110,0x20},
			{62,0,0x100,0x100,0x110,0x20},
			{63,0,0x100,0x100,0x110,0x20},
			{64,0,0x100,0x100,0x110,0x20},
			{65,0,0x100,0x100,0x110,0x20},
			{66,0,0x100,0x100,0x110,0x20},
			{67,0,0x100,0x100,0x110,0x20},
			{68,0,0x100,0x100,0x110,0x20},
			{69,0,0x100,0x100,0x110,0x20},
			{70,0,0x100,0x100,0x110,0x20},
			{71,0,0x100,0x100,0x110,0x20},
			{72,0,0x100,0x100,0x110,0x20},
			{73,0,0x100,0x100,0x110,0x20},
			{74,0,0x100,0x100,0x110,0x20},
			{75,0,0x100,0x100,0x110,0x20},
			{76,0,0x100,0x100,0x110,0x20},
			{77,0,0x100,0x100,0x110,0x20},
			{78,0,0x100,0x100,0x110,0x20},
			{79,0,0x100,0x100,0x110,0x20},
			{80,0,0x100,0x100,0x110,0x20},
			{81,0,0x100,0x100,0x110,0x20},
			{82,0,0x100,0x100,0x110,0x20},
			{83,0,0x100,0x100,0x110,0x20},
			{84,0,0x100,0x100,0x110,0x20},
			{85,0,0x100,0x100,0x110,0x20},
			{86,0,0x100,0x100,0x110,0x20},
			{87,0,0x100,0x100,0x110,0x20},
			{88,0,0x100,0x100,0x110,0x20},
			{89,0,0x100,0x100,0x110,0x20},
			{90,0,0x100,0x100,0x110,0x20},
			{91,0,0x100,0x100,0x110,0x20},
			{92,0,0x100,0x100,0x110,0x20},
			{93,0,0x100,0x100,0x110,0x20},
			{94,0,0x100,0x100,0x110,0x20},
		};
		/** @brief 预置服务名称列表 */
		const static D_Char default_srv_name_list[][36] = 
		{
			{"115_Diver"},
			{"123_Diver "},
			{"131_Diver "},
			{"139_Diver"},
			{"147_Diver "},
			{"155_Diver "},
			{"163_Diver"},
			{"171_Diver "},
			{"179_Diver "},
			{"187_Diver"},
			{"195_Diver "},
			{"203_Diver "},
			{"211_Diver"},
			{"219_Diver "},
			{"227_Diver "},
			{"235_Diver"},
			{"243_Diver "},
			{"251_Diver "},
			{"259_Diver"},
			{"267_Diver "},
			{"275_Diver "},
			{"283_Diver"},
			{"291_Diver "},
			{"299_Diver "},
			{"307_Diver"},
			{"315_Diver "},
			{"323_Diver "},
			{"331_Diver"},
			{"339_Diver "},
			{"347_Diver "},
			{"355_Diver"},
			{"363_Diver "},
			{"371_Diver "},
			{"379_Diver"},
			{"387_Diver "},
			{"395_Diver "},
			{"403_Diver"},
			{"411_Diver "},
			{"419_Diver "},
			{"427_Diver"},
			{"435_Diver "},
			{"443_Diver "},
			{"451_Diver"},
			{"459_Diver "},
			{"467_Diver "},
			{"474_Diver"},
			{"482_Diver "},
			{"490_Diver "},
			{"498_Diver"},
			{"506_Diver "},
			{"514_Diver "},
			{"522_Diver"},
			{"530_Diver "},
			{"538_Diver "},
			{"546_Diver"},
			{"554_Diver "},
			{"562_Diver"},
			{"570_Diver "},
			{"578_Diver "},
			{"586_Diver"},
			{"594_Diver "},
			{"602_Diver "},
			{"610_Diver"},
			{"618_Diver "},
			{"626_Diver "},
			{"634_Diver"},
			{"642_Diver "},
			{"650_Diver "},
			{"658_Diver"},
			{"666_Diver "},
			{"674_Diver "},
			{"682_Diver"},
			{"690_Diver "},
			{"698_Diver "},
			{"706_Diver"},
			{"714_Diver "},
			{"722_Diver "},
			{"730_Diver"},
			{"738_Diver "},
			{"746_Diver "},
			{"754_Diver"},
			{"762_Diver "},
			{"770_Diver "},
			{"778_Diver"},
			{"786_Diver "},
			{"794_Diver "},
			{"802_Diver"},
			{"810_Diver "},
			{"818_Diver "},
			{"826_Diver"},
			{"834_Diver "},
			{"842_Diver "},
			{"850_Diver"},
			{"858_Diver "},
		};
	#endif
#endif


#ifdef P_DBASE_DVBS 
/** @brief 恢复出厂设置时添加预制数据
* @retval D_ERR_NO_SPACE 申请内存失败
* @retval D_OK	添加结束
*/
D_Result
d_dbase_add_default_data_dvbs(void) D_FUNCPOSTFIT
{
	D_U16 i = 0, ante_num = 0, sat_num = 0, dvbs_ts_num = 0, srv_num = 0;
	D_DBAnteInfo anteinfo;
	D_DBSateInfo satinfo;
	D_DBTSInfo	tsinfo;
	D_DBSrvInfo	srvinfo;
	D_ID * ante_id = NULL;
	D_ID * sat_id = NULL;
	D_ID * ts_id = NULL;
	D_ID did = 0;
	
	D_DB_LOCK ();
	/*添加预置天线*/
	if(DEFAULT_ANTE_NUM > P_DB_MAX_ANTE_CNT)
	{
		ante_num = P_DB_MAX_ANTE_CNT;
	}
	else
	{
		ante_num = DEFAULT_ANTE_NUM;
	}
	if(ante_num == 0)
	{
		D_DB_UNLOCK ();
		return D_OK;
	}
	ante_id = PROJECT_ALLOC(ante_num * sizeof(D_ID));
	if(ante_id == NULL)
	{
		D_DB_UNLOCK ();
		return D_ERR_NO_SPACE;
	}
	for(i = 0; i < ante_num; i++)	
	{
		D_DB_ANTE_INFO_INIT(&anteinfo);
		anteinfo.freq1 = default_ante_list[i][0];
		anteinfo.freq2 = default_ante_list[i][1];
		anteinfo.lnb_type = default_ante_list[i][2]; //LNBType;
		did = d_dbase_insert_ante(&anteinfo);
		ante_id[i] = did;
	}
	/*添加预置卫星*/
	if(DEFAULT_SAT_NUM > P_DB_MAX_SAT_CNT)
	{
		sat_num = P_DB_MAX_SAT_CNT;
	}
	else
	{
		sat_num = DEFAULT_SAT_NUM;
	}
	if(sat_num == 0)
	{
		D_DB_UNLOCK ();
		return D_OK;
	}
	sat_id = PROJECT_ALLOC(sat_num * sizeof(D_ID));
	if(sat_id == NULL)
	{
		D_DB_UNLOCK ();
		PROJECT_FREE(ante_id);
		return D_ERR_NO_SPACE;
	}
	for(i = 0; i < sat_num; i++)
	{
		if((default_sat_list[i][0] <= ante_num)&&(ante_id[default_sat_list[i][0] - 1] != -1))
		{
			D_DB_SAT_INFO_INIT(&satinfo);
			satinfo.antenna_slot = ante_id[default_sat_list[i][0] - 1];
			satinfo.longitude = default_sat_list[i][1];
			satinfo.sate_no = i;	//default_sat_list[i][2] - 1;
			satinfo.diseqc_pos = D_MIN(63, i);
			memcpy(&satinfo.sate_name, default_sat_name_list[i], (strlen(default_sat_name_list[i])+1));
                    if(i < 4)satinfo.selected = D_TRUE;
			did = d_dbase_insert_sat_ex(&satinfo, D_FALSE);
			sat_id[i] = did;
		}
		else
		{
			sat_id[i] = -1;
		}
	}
	/*添加预置TS*/
	if(DEFAULT_DVBS_TS_NUM > P_DB_MAX_TS_CNT)
	{
		dvbs_ts_num = P_DB_MAX_TS_CNT;
	}
	else
	{
		dvbs_ts_num = DEFAULT_DVBS_TS_NUM;
	}
	if(dvbs_ts_num == 0)
	{
		D_DB_UNLOCK ();
		return D_OK;
	}
	ts_id = PROJECT_ALLOC(dvbs_ts_num * sizeof(D_ID));
	if(ts_id == NULL)
	{
		D_DB_UNLOCK ();
		PROJECT_FREE(ante_id);
		PROJECT_FREE(sat_id);
		return D_ERR_NO_SPACE;
	}
	for(i = 0; i < dvbs_ts_num; i++)
	{
		if((default_dvbs_ts_list[i][0] <= sat_num)&&(sat_id[default_dvbs_ts_list[i][0] - 1] != -1))
		{
			D_DBTSID	id = -1;
			
			D_DB_TS_INFO_INIT(&tsinfo);
 			tsinfo.db_net_id = D_DB_DEF_NET_ID;           
			tsinfo.db_sat_id = sat_id[default_dvbs_ts_list[i][0] - 1];
			tsinfo.param.dvbs.freq = default_dvbs_ts_list[i][1];
			tsinfo.param.dvbs.baud = default_dvbs_ts_list[i][2];
			tsinfo.param.dvbs.pol = default_dvbs_ts_list[i][3];//POL;
			//tsinfo.ts_id = i;	//default_dvbs_ts_list[i][4] - 1;
			tsinfo.tuner_type = D_FEND_DVBS;
			
			id = d_dbase_get_ts_by_param(0, D_FEND_DVBS, &tsinfo. param);
			if(id == -1)
			{
				did = d_dbase_insert_ts (&tsinfo);
				ts_id[i] = did;
			}
			else
			{
				ts_id[i] = id;
			}
		}
		else
		{
			ts_id[i] = -1;
		}
	}
    
	/*添加预置服务*/
	if(DEFAULT_SRV_NUM > P_DB_MAX_SRV_CNT)
	{
		srv_num = P_DB_MAX_SRV_CNT;
	}
	else
	{
		srv_num = DEFAULT_SRV_NUM;
	}
	for(i = 0; i < srv_num; i++)
	{
		if((default_srv_list[i][0] <= dvbs_ts_num)&&(ts_id[default_srv_list[i][0] - 1] != -1))
		{
			D_DB_SRV_INFO_INIT(&srvinfo);
			srvinfo.db_ts_id = ts_id[default_srv_list[i][0] - 1];
			srvinfo.srv_type = default_srv_list[i][1];
			srvinfo.pcr_pid = default_srv_list[i][2];
			srvinfo.vid_pid = default_srv_list[i][3];
			srvinfo.aud1_pid = default_srv_list[i][4];
			srvinfo.aud2_pid = default_srv_list[i][5];
			srvinfo.chan_num = d_dbase_get_free_chan_num(srvinfo.srv_type);
			memcpy(&srvinfo.name, &default_srv_name_list[i], (strlen(default_srv_name_list[i])+1));
			d_dbase_insert_srv_ex(&srvinfo, D_FALSE);
		}
	}
	D_DB_UNLOCK ();
	
	PROJECT_FREE(ante_id);
	PROJECT_FREE(sat_id);
	PROJECT_FREE(ts_id);
	
	
	return D_OK;
}

#else

/** @brief 恢复出厂设置时添加预制数据
* @retval D_ERR_NO_SPACE 申请内存失败
* @retval D_OK	添加结束
*/
D_Result
d_dbase_add_default_data(void) D_FUNCPOSTFIT
{
	D_U16 i, ts_num = 0, srv_num = 0;
	D_DBTSInfo	tsinfo;
	D_DBSrvInfo	srvinfo;
	D_ID * ts_id = NULL;
	D_ID did = 0;
	
	D_DB_LOCK ();
	
	if(DEFAULT_TS_NUM > P_DB_MAX_TS_CNT)
	{
		ts_num = P_DB_MAX_TS_CNT;
	}
	else
	{
		ts_num = DEFAULT_TS_NUM;
	}
	if(ts_num == 0)
	{
		D_DB_UNLOCK ();
		return D_OK;
	}
	ts_id = PROJECT_ALLOC(ts_num * sizeof(D_ID));
	if(ts_id == NULL)
	{
		D_DB_UNLOCK ();
		return D_ERR_NO_SPACE;
	}
	for(i = 0; i < ts_num; i++)
	{
		D_DBTSID	id = -1;
		
		D_DB_TS_INFO_INIT(&tsinfo);
              tsinfo.db_net_id = D_DB_DEF_NET_ID;
	#ifdef DTMB
		tsinfo.ts_id = i;	//default_ts_list[i][0] - 1;
		tsinfo.param.dtmb.freq = default_ts_list[i][1];
		tsinfo.tuner_type = D_FEND_DTMB;
		
		id = d_dbase_get_ts_by_param(0, D_FEND_DTMB, &tsinfo. param);
	#else
		tsinfo.ts_id = i;	//default_ts_list[i][0] - 1;
		tsinfo.param.dvbc.freq = default_ts_list[i][1];
		tsinfo.param.dvbc.baud = default_ts_list[i][2];
		tsinfo.param.dvbc.mod = default_ts_list[i][3];//MOD;
		tsinfo.tuner_type = D_FEND_DVBC;
		
		id = d_dbase_get_ts_by_param(0, D_FEND_DVBC, &tsinfo. param);
	#endif
		
		if(id == -1)
		{
			did = d_dbase_insert_ts (&tsinfo);
			ts_id[i] = did;
		}
		else
		{
			ts_id[i] = id;
		}
	}
	/*添加预置服务*/
	if(DEFAULT_SRV_NUM > P_DB_MAX_SRV_CNT)
	{
		srv_num = P_DB_MAX_SRV_CNT;
	}
	else
	{
		srv_num = DEFAULT_SRV_NUM;
	}
	for(i = 0; i < srv_num; i++)
	{
		if((default_srv_list[i][0] <= ts_num)&&(ts_id[default_srv_list[i][0] - 1] != -1))
		{
			D_DB_SRV_INFO_INIT(&srvinfo);
			srvinfo.db_ts_id = ts_id[default_srv_list[i][0] - 1];
			srvinfo.srv_type = default_srv_list[i][1];
			srvinfo.pcr_pid = default_srv_list[i][2];
			srvinfo.vid_pid = default_srv_list[i][3];
			srvinfo.aud1_pid = default_srv_list[i][4];
			srvinfo.aud2_pid = default_srv_list[i][5];
			srvinfo.chan_num = d_dbase_get_free_chan_num(srvinfo.srv_type);
			memcpy(&srvinfo.name, &default_srv_name_list[i], (strlen(default_srv_name_list[i])+1));
			d_dbase_insert_srv_ex(&srvinfo, D_FALSE);
		}
	}
	D_DB_UNLOCK ();
	
	PROJECT_FREE(ts_id);
	
	return D_OK;
}

#endif

/** @brief 数据库恢复出厂设置
* @retval D_OK
*/
D_Result
d_dbase_factory_set(void) D_FUNCPOSTFIT
{
	d_dbase_set_rset_en(0);
#ifdef P_DBASE_DVBS 
        d_dbase_clear_sat();
	d_dbase_clear_ante ();	//清空天线表里面包含了清空卫星表，清空卫星表包含了清空TS表，清空TS表包含了清空服务表，所以只需调用清空天线表即可。
#else	
	d_dbase_clear_ts ();	//清空TS表里面包含了清空服务表，所以只需调用清空TS表即可。 
#endif

#ifdef P_DBASE_DVBS
	d_dbase_add_default_data_dvbs();
#else
	d_dbase_add_default_data();
#endif
	d_dbase_flush();
	
	return D_OK;
}
#include "dAV.h"
#include "ptvConfig.h"
#include "pCustomConfig.h"
#include "pStb.h"
typedef struct
{
    D_FEndFreq freq;
    D_U8    videoMode;
    D_U8    audioMode;
    D_Char  *name;
    D_VidCodecType vid_codec;
    D_AudCodecType aud1_codec;
} DEF_Atv_Data;

typedef struct
{
    D_Char      *name;
    D_U16       srv_id;
    D_U16       pmt_pid;
    D_U16       pcr_pid;
    D_U16       vid_pid;
    D_U16       aud1_pid;
    D_VidCodecType vid_codec;
    D_AudCodecType aud1_codec;
    D_U8    srv_type;
} DEF_Dtv_srv;

typedef struct
{
    D_FEndType ftype;
    D_FEndFreq freq;
    D_FEndBaud baud;
    D_FEndMod  mode;
    D_U16      ts_id;
    D_U16      org_net;
    D_U32      srv_cnt;
    DEF_Dtv_srv *srv;
} DEF_Dtv_Data;

typedef struct
{
    DEF_Atv_Data *atv;
    D_U32 atv_cnt;
    DEF_Dtv_Data *dtv;
    D_U32 dtv_cnt;
} DEF_DBIfo;

//// ================ ctv厂家
static DEF_Atv_Data Atv_srv_ctv[] =
{
    {60000, D_VideoP, D_AudioI, "P0", D_VID_CODEC_PAL, D_AUD_CODEC_I},
};

static DEF_Dtv_srv Dtv_srv_ctv[] =
{
    {"75%% colour bar", 1, 0x64, 0x6e, 0x6e, 0x78, D_VID_CODEC_MPEG2, D_AUD_CODEC_MPEG2, D_DB_SRV_TV},
};

static DEF_Dtv_Data Dtv_ts_ctv[] = {{D_FEND_DTMB, 171, 0, 0, 1, 0xabcd, sizeof(Dtv_srv_ctv) / sizeof(Dtv_srv_ctv[0]), Dtv_srv_ctv}};

//// ================ boe厂家
static DEF_Atv_Data Atv_srv_boe[] =
{
#if 1
	{64250, D_VideoP, D_AudioI, "P0", D_VID_CODEC_PAL, D_AUD_CODEC_I},
	{440250, D_VideoP, D_AudioI, "P3", D_VID_CODEC_PAL, D_AUD_CODEC_DK},
	{471250, D_VideoP, D_AudioI, "P4", D_VID_CODEC_PAL, D_AUD_CODEC_I},
	{567250, D_VideoP, D_AudioI, "P5", D_VID_CODEC_PAL, D_AUD_CODEC_I},
	{855250, D_VideoP, D_AudioBG, "P6", D_VID_CODEC_PAL, D_AUD_CODEC_BG},
	{863250, D_VideoP, D_AudioDK, "P7", D_VID_CODEC_PAL, D_AUD_CODEC_DK},
#else
	{49750, D_VideoP, D_AudioDK,  "P00  ", D_VID_CODEC_PAL, D_AudioDK},
	{57750, D_VideoP, D_AudioDK,  "P01  ", D_VID_CODEC_PAL, D_AudioDK},
	{65750, D_VideoP, D_AudioDK,  "P02  ", D_VID_CODEC_PAL, D_AudioDK},
	{77750, D_VideoP, D_AudioDK,  "P03  ", D_VID_CODEC_PAL, D_AudioDK},
	{85250, D_VideoP, D_AudioDK,  "P04  ", D_VID_CODEC_PAL, D_AudioDK},
	{112250, D_VideoP, D_AudioDK, "P05  ", D_VID_CODEC_PAL, D_AudioDK},
	{120250, D_VideoP, D_AudioDK, "P06  ", D_VID_CODEC_PAL, D_AudioDK},
	{128250, D_VideoP, D_AudioDK, "P07  ", D_VID_CODEC_PAL, D_AudioDK},
	{136250, D_VideoP, D_AudioDK, "P08  ", D_VID_CODEC_PAL, D_AudioDK},
	{144250, D_VideoP, D_AudioDK, "P09  ", D_VID_CODEC_PAL, D_AudioDK},
	{152250, D_VideoP, D_AudioDK, "P010 ", D_VID_CODEC_PAL, D_AudioDK},
	{160250, D_VideoP, D_AudioDK, "P011 ", D_VID_CODEC_PAL, D_AudioDK},
	{168250, D_VideoP, D_AudioDK, "P012 ", D_VID_CODEC_PAL, D_AudioDK},
	{176250, D_VideoP, D_AudioDK, "P013 ", D_VID_CODEC_PAL, D_AudioDK},
	{184250, D_VideoP, D_AudioDK, "P014 ", D_VID_CODEC_PAL, D_AudioDK},
	{192250, D_VideoP, D_AudioDK, "P015 ", D_VID_CODEC_PAL, D_AudioDK},
	{200250, D_VideoP, D_AudioDK, "P016 ", D_VID_CODEC_PAL, D_AudioDK},
	{208250, D_VideoP, D_AudioDK, "P017 ", D_VID_CODEC_PAL, D_AudioDK},
	{216250, D_VideoP, D_AudioDK, "P018 ", D_VID_CODEC_PAL, D_AudioDK},
	{224250, D_VideoP, D_AudioDK, "P019 ", D_VID_CODEC_PAL, D_AudioDK},
	{232250, D_VideoP, D_AudioDK, "P020 ", D_VID_CODEC_PAL, D_AudioDK},
	{240250, D_VideoP, D_AudioDK, "P021 ", D_VID_CODEC_PAL, D_AudioDK},
	{248250, D_VideoP, D_AudioDK, "P022 ", D_VID_CODEC_PAL, D_AudioDK},
	{256250, D_VideoP, D_AudioDK, "P023 ", D_VID_CODEC_PAL, D_AudioDK},
	{264250, D_VideoP, D_AudioDK, "P024 ", D_VID_CODEC_PAL, D_AudioDK},
	{272250, D_VideoP, D_AudioDK, "P025 ", D_VID_CODEC_PAL, D_AudioDK},
	{280250, D_VideoP, D_AudioDK, "P026 ", D_VID_CODEC_PAL, D_AudioDK},
	{288250, D_VideoP, D_AudioDK, "P027 ", D_VID_CODEC_PAL, D_AudioDK},
	{296250, D_VideoP, D_AudioDK, "P028 ", D_VID_CODEC_PAL, D_AudioDK},
	{304250, D_VideoP, D_AudioDK, "P029 ", D_VID_CODEC_PAL, D_AudioDK},
	{312250, D_VideoP, D_AudioDK, "P030 ", D_VID_CODEC_PAL, D_AudioDK},
	{320250, D_VideoP, D_AudioDK, "P031 ", D_VID_CODEC_PAL, D_AudioDK},
	{328250, D_VideoP, D_AudioDK, "P032 ", D_VID_CODEC_PAL, D_AudioDK},
	{336250, D_VideoP, D_AudioDK, "P033 ", D_VID_CODEC_PAL, D_AudioDK},
	{344250, D_VideoP, D_AudioDK, "P034 ", D_VID_CODEC_PAL, D_AudioDK},
	{352250, D_VideoP, D_AudioDK, "P035 ", D_VID_CODEC_PAL, D_AudioDK},
	{360250, D_VideoP, D_AudioDK, "P036 ", D_VID_CODEC_PAL, D_AudioDK},
	{368250, D_VideoP, D_AudioDK, "P037 ", D_VID_CODEC_PAL, D_AudioDK},
	{376250, D_VideoP, D_AudioDK, "P038 ", D_VID_CODEC_PAL, D_AudioDK},
	{384250, D_VideoP, D_AudioDK, "P039 ", D_VID_CODEC_PAL, D_AudioDK},
	{392250, D_VideoP, D_AudioDK, "P040 ", D_VID_CODEC_PAL, D_AudioDK},
	{400250, D_VideoP, D_AudioDK, "P041 ", D_VID_CODEC_PAL, D_AudioDK},
	{408250, D_VideoP, D_AudioDK, "P042 ", D_VID_CODEC_PAL, D_AudioDK},
	{416250, D_VideoP, D_AudioDK, "P043 ", D_VID_CODEC_PAL, D_AudioDK},
	{424250, D_VideoP, D_AudioDK, "P044 ", D_VID_CODEC_PAL, D_AudioDK},
	{440250, D_VideoP, D_AudioDK, "P045 ", D_VID_CODEC_PAL, D_AudioDK},
	{448250, D_VideoP, D_AudioDK, "P046 ", D_VID_CODEC_PAL, D_AudioDK},
	{456250, D_VideoP, D_AudioDK, "P047 ", D_VID_CODEC_PAL, D_AudioDK},
	{464250, D_VideoP, D_AudioDK, "P048 ", D_VID_CODEC_PAL, D_AudioDK},
	{471250, D_VideoP, D_AudioDK, "P049 ", D_VID_CODEC_PAL, D_AudioDK},
	{479250, D_VideoP, D_AudioDK, "P050 ", D_VID_CODEC_PAL, D_AudioDK},
	{487250, D_VideoP, D_AudioDK, "P051 ", D_VID_CODEC_PAL, D_AudioDK},
	{495250, D_VideoP, D_AudioDK, "P052 ", D_VID_CODEC_PAL, D_AudioDK},
	{503250, D_VideoP, D_AudioDK, "P053 ", D_VID_CODEC_PAL, D_AudioDK},
	{511250, D_VideoP, D_AudioDK, "P054 ", D_VID_CODEC_PAL, D_AudioDK},
	{519250, D_VideoP, D_AudioDK, "P055 ", D_VID_CODEC_PAL, D_AudioDK},
	{527250, D_VideoP, D_AudioDK, "P056 ", D_VID_CODEC_PAL, D_AudioDK},
	{535250, D_VideoP, D_AudioDK, "P057 ", D_VID_CODEC_PAL, D_AudioDK},
	{543250, D_VideoP, D_AudioDK, "P058 ", D_VID_CODEC_PAL, D_AudioDK},
	{551250, D_VideoP, D_AudioDK, "P059 ", D_VID_CODEC_PAL, D_AudioDK},
	{559250, D_VideoP, D_AudioDK, "P060 ", D_VID_CODEC_PAL, D_AudioDK},
	{607250, D_VideoP, D_AudioDK, "P061 ", D_VID_CODEC_PAL, D_AudioDK},
	{615250, D_VideoP, D_AudioDK, "P062 ", D_VID_CODEC_PAL, D_AudioDK},
	{623250, D_VideoP, D_AudioDK, "P063 ", D_VID_CODEC_PAL, D_AudioDK},
	{631250, D_VideoP, D_AudioDK, "P064 ", D_VID_CODEC_PAL, D_AudioDK},
	{639250, D_VideoP, D_AudioDK, "P065 ", D_VID_CODEC_PAL, D_AudioDK},
	{647250, D_VideoP, D_AudioDK, "P066 ", D_VID_CODEC_PAL, D_AudioDK},
	{655250, D_VideoP, D_AudioDK, "P067 ", D_VID_CODEC_PAL, D_AudioDK},
	{663250, D_VideoP, D_AudioDK, "P068 ", D_VID_CODEC_PAL, D_AudioDK},
	{671250, D_VideoP, D_AudioDK, "P069 ", D_VID_CODEC_PAL, D_AudioDK},
	{679250, D_VideoP, D_AudioDK, "P070 ", D_VID_CODEC_PAL, D_AudioDK},
	{687250, D_VideoP, D_AudioDK, "P071 ", D_VID_CODEC_PAL, D_AudioDK},
	{695250, D_VideoP, D_AudioDK, "P072 ", D_VID_CODEC_PAL, D_AudioDK},
	{703250, D_VideoP, D_AudioDK, "P073 ", D_VID_CODEC_PAL, D_AudioDK},
	{711250, D_VideoP, D_AudioDK, "P074 ", D_VID_CODEC_PAL, D_AudioDK},
	{719250, D_VideoP, D_AudioDK, "P075 ", D_VID_CODEC_PAL, D_AudioDK},
	{727250, D_VideoP, D_AudioDK, "P076 ", D_VID_CODEC_PAL, D_AudioDK},
	{735250, D_VideoP, D_AudioDK, "P077 ", D_VID_CODEC_PAL, D_AudioDK},
	{743250, D_VideoP, D_AudioDK, "P078 ", D_VID_CODEC_PAL, D_AudioDK},
	{751250, D_VideoP, D_AudioDK, "P079 ", D_VID_CODEC_PAL, D_AudioDK},
	{759250, D_VideoP, D_AudioDK, "P080 ", D_VID_CODEC_PAL, D_AudioDK},
	{767250, D_VideoP, D_AudioDK, "P081 ", D_VID_CODEC_PAL, D_AudioDK},
	{775250, D_VideoP, D_AudioDK, "P082 ", D_VID_CODEC_PAL, D_AudioDK},
	{783250, D_VideoP, D_AudioDK, "P083 ", D_VID_CODEC_PAL, D_AudioDK},
	{791250, D_VideoP, D_AudioDK, "P084 ", D_VID_CODEC_PAL, D_AudioDK},
	{799250, D_VideoP, D_AudioDK, "P085 ", D_VID_CODEC_PAL, D_AudioDK},
	{807250, D_VideoP, D_AudioDK, "P086 ", D_VID_CODEC_PAL, D_AudioDK},
	{815250, D_VideoP, D_AudioDK, "P087 ", D_VID_CODEC_PAL, D_AudioDK},
	{823250, D_VideoP, D_AudioDK, "P088 ", D_VID_CODEC_PAL, D_AudioDK},
	{831250, D_VideoP, D_AudioDK, "P089 ", D_VID_CODEC_PAL, D_AudioDK},
	{839250, D_VideoP, D_AudioDK, "P090 ", D_VID_CODEC_PAL, D_AudioDK},
	{847250, D_VideoP, D_AudioDK, "P091 ", D_VID_CODEC_PAL, D_AudioDK},
	{855250, D_VideoP, D_AudioDK, "P092 ", D_VID_CODEC_PAL, D_AudioDK},
	{863250, D_VideoP, D_AudioDK, "P093 ", D_VID_CODEC_PAL, D_AudioDK},
#endif	                         
};

static DEF_Dtv_srv Dtv_srv_boe[] =
{
	{"SZTV-2", 11, 0x20, 0x65, 0x65, 0x3e9, D_VID_CODEC_H264, D_AUD_CODEC_MPEG2, D_DB_SRV_TV},
	{"SZTV-7", 12, 0x21, 0x66, 0x66, 0x3ea, D_VID_CODEC_H264, D_AUD_CODEC_MPEG2, D_DB_SRV_TV},
};

static DEF_Dtv_Data Dtv_ts_boe[] = {{D_FEND_DTMB, 586, 0, 0, 1, 1, sizeof(Dtv_srv_boe) / sizeof(Dtv_srv_boe[0]), Dtv_srv_boe}};

//// ================atv全频点
static DEF_Atv_Data Atv_srv_test[] =
{
#if 0
	{64250, D_VideoP, D_AudioI, "P0", D_VID_CODEC_PAL, D_AUD_CODEC_I},
	{440250, D_VideoP, D_AudioI, "P3", D_VID_CODEC_PAL, D_AUD_CODEC_DK},
	{471250, D_VideoP, D_AudioI, "P4", D_VID_CODEC_PAL, D_AUD_CODEC_I},
	{567250, D_VideoP, D_AudioI, "P5", D_VID_CODEC_PAL, D_AUD_CODEC_I},
	{855250, D_VideoP, D_AudioBG, "P6", D_VID_CODEC_PAL, D_AUD_CODEC_BG},
	{863250, D_VideoP, D_AudioDK, "P7", D_VID_CODEC_PAL, D_AUD_CODEC_DK},
#else
	{49750, D_VideoP, D_AudioDK,  "P00  ", D_VID_CODEC_PAL, D_AudioDK},
	{57750, D_VideoP, D_AudioDK,  "P01  ", D_VID_CODEC_PAL, D_AudioDK},
	{65750, D_VideoP, D_AudioDK,  "P02  ", D_VID_CODEC_PAL, D_AudioDK},
	{77750, D_VideoP, D_AudioDK,  "P03  ", D_VID_CODEC_PAL, D_AudioDK},
	{85250, D_VideoP, D_AudioDK,  "P04  ", D_VID_CODEC_PAL, D_AudioDK},
	{112250, D_VideoP, D_AudioDK, "P05  ", D_VID_CODEC_PAL, D_AudioDK},
	{120250, D_VideoP, D_AudioDK, "P06  ", D_VID_CODEC_PAL, D_AudioDK},
	{128250, D_VideoP, D_AudioDK, "P07  ", D_VID_CODEC_PAL, D_AudioDK},
	{136250, D_VideoP, D_AudioDK, "P08  ", D_VID_CODEC_PAL, D_AudioDK},
	{144250, D_VideoP, D_AudioDK, "P09  ", D_VID_CODEC_PAL, D_AudioDK},
	{152250, D_VideoP, D_AudioDK, "P010 ", D_VID_CODEC_PAL, D_AudioDK},
	{160250, D_VideoP, D_AudioDK, "P011 ", D_VID_CODEC_PAL, D_AudioDK},
	{168250, D_VideoP, D_AudioDK, "P012 ", D_VID_CODEC_PAL, D_AudioDK},
	{176250, D_VideoP, D_AudioDK, "P013 ", D_VID_CODEC_PAL, D_AudioDK},
	{184250, D_VideoP, D_AudioDK, "P014 ", D_VID_CODEC_PAL, D_AudioDK},
	{192250, D_VideoP, D_AudioDK, "P015 ", D_VID_CODEC_PAL, D_AudioDK},
	{200250, D_VideoP, D_AudioDK, "P016 ", D_VID_CODEC_PAL, D_AudioDK},
	{208250, D_VideoP, D_AudioDK, "P017 ", D_VID_CODEC_PAL, D_AudioDK},
	{216250, D_VideoP, D_AudioDK, "P018 ", D_VID_CODEC_PAL, D_AudioDK},
	{224250, D_VideoP, D_AudioDK, "P019 ", D_VID_CODEC_PAL, D_AudioDK},
	{232250, D_VideoP, D_AudioDK, "P020 ", D_VID_CODEC_PAL, D_AudioDK},
	{240250, D_VideoP, D_AudioDK, "P021 ", D_VID_CODEC_PAL, D_AudioDK},
	{248250, D_VideoP, D_AudioDK, "P022 ", D_VID_CODEC_PAL, D_AudioDK},
	{256250, D_VideoP, D_AudioDK, "P023 ", D_VID_CODEC_PAL, D_AudioDK},
	{264250, D_VideoP, D_AudioDK, "P024 ", D_VID_CODEC_PAL, D_AudioDK},
	{272250, D_VideoP, D_AudioDK, "P025 ", D_VID_CODEC_PAL, D_AudioDK},
	{280250, D_VideoP, D_AudioDK, "P026 ", D_VID_CODEC_PAL, D_AudioDK},
	{288250, D_VideoP, D_AudioDK, "P027 ", D_VID_CODEC_PAL, D_AudioDK},
	{296250, D_VideoP, D_AudioDK, "P028 ", D_VID_CODEC_PAL, D_AudioDK},
	{304250, D_VideoP, D_AudioDK, "P029 ", D_VID_CODEC_PAL, D_AudioDK},
	{312250, D_VideoP, D_AudioDK, "P030 ", D_VID_CODEC_PAL, D_AudioDK},
	{320250, D_VideoP, D_AudioDK, "P031 ", D_VID_CODEC_PAL, D_AudioDK},
	{328250, D_VideoP, D_AudioDK, "P032 ", D_VID_CODEC_PAL, D_AudioDK},
	{336250, D_VideoP, D_AudioDK, "P033 ", D_VID_CODEC_PAL, D_AudioDK},
	{344250, D_VideoP, D_AudioDK, "P034 ", D_VID_CODEC_PAL, D_AudioDK},
	{352250, D_VideoP, D_AudioDK, "P035 ", D_VID_CODEC_PAL, D_AudioDK},
	{360250, D_VideoP, D_AudioDK, "P036 ", D_VID_CODEC_PAL, D_AudioDK},
	{368250, D_VideoP, D_AudioDK, "P037 ", D_VID_CODEC_PAL, D_AudioDK},
	{376250, D_VideoP, D_AudioDK, "P038 ", D_VID_CODEC_PAL, D_AudioDK},
	{384250, D_VideoP, D_AudioDK, "P039 ", D_VID_CODEC_PAL, D_AudioDK},
	{392250, D_VideoP, D_AudioDK, "P040 ", D_VID_CODEC_PAL, D_AudioDK},
	{400250, D_VideoP, D_AudioDK, "P041 ", D_VID_CODEC_PAL, D_AudioDK},
	{408250, D_VideoP, D_AudioDK, "P042 ", D_VID_CODEC_PAL, D_AudioDK},
	{416250, D_VideoP, D_AudioDK, "P043 ", D_VID_CODEC_PAL, D_AudioDK},
	{424250, D_VideoP, D_AudioDK, "P044 ", D_VID_CODEC_PAL, D_AudioDK},
	{440250, D_VideoP, D_AudioDK, "P045 ", D_VID_CODEC_PAL, D_AudioDK},
	{448250, D_VideoP, D_AudioDK, "P046 ", D_VID_CODEC_PAL, D_AudioDK},
	{456250, D_VideoP, D_AudioDK, "P047 ", D_VID_CODEC_PAL, D_AudioDK},
	{464250, D_VideoP, D_AudioDK, "P048 ", D_VID_CODEC_PAL, D_AudioDK},
	{471250, D_VideoP, D_AudioDK, "P049 ", D_VID_CODEC_PAL, D_AudioDK},
	{479250, D_VideoP, D_AudioDK, "P050 ", D_VID_CODEC_PAL, D_AudioDK},
	{487250, D_VideoP, D_AudioDK, "P051 ", D_VID_CODEC_PAL, D_AudioDK},
	{495250, D_VideoP, D_AudioDK, "P052 ", D_VID_CODEC_PAL, D_AudioDK},
	{503250, D_VideoP, D_AudioDK, "P053 ", D_VID_CODEC_PAL, D_AudioDK},
	{511250, D_VideoP, D_AudioDK, "P054 ", D_VID_CODEC_PAL, D_AudioDK},
	{519250, D_VideoP, D_AudioDK, "P055 ", D_VID_CODEC_PAL, D_AudioDK},
	{527250, D_VideoP, D_AudioDK, "P056 ", D_VID_CODEC_PAL, D_AudioDK},
	{535250, D_VideoP, D_AudioDK, "P057 ", D_VID_CODEC_PAL, D_AudioDK},
	{543250, D_VideoP, D_AudioDK, "P058 ", D_VID_CODEC_PAL, D_AudioDK},
	{551250, D_VideoP, D_AudioDK, "P059 ", D_VID_CODEC_PAL, D_AudioDK},
	{559250, D_VideoP, D_AudioDK, "P060 ", D_VID_CODEC_PAL, D_AudioDK},
	{607250, D_VideoP, D_AudioDK, "P061 ", D_VID_CODEC_PAL, D_AudioDK},
	{615250, D_VideoP, D_AudioDK, "P062 ", D_VID_CODEC_PAL, D_AudioDK},
	{623250, D_VideoP, D_AudioDK, "P063 ", D_VID_CODEC_PAL, D_AudioDK},
	{631250, D_VideoP, D_AudioDK, "P064 ", D_VID_CODEC_PAL, D_AudioDK},
	{639250, D_VideoP, D_AudioDK, "P065 ", D_VID_CODEC_PAL, D_AudioDK},
	{647250, D_VideoP, D_AudioDK, "P066 ", D_VID_CODEC_PAL, D_AudioDK},
	{655250, D_VideoP, D_AudioDK, "P067 ", D_VID_CODEC_PAL, D_AudioDK},
	{663250, D_VideoP, D_AudioDK, "P068 ", D_VID_CODEC_PAL, D_AudioDK},
	{671250, D_VideoP, D_AudioDK, "P069 ", D_VID_CODEC_PAL, D_AudioDK},
	{679250, D_VideoP, D_AudioDK, "P070 ", D_VID_CODEC_PAL, D_AudioDK},
	{687250, D_VideoP, D_AudioDK, "P071 ", D_VID_CODEC_PAL, D_AudioDK},
	{695250, D_VideoP, D_AudioDK, "P072 ", D_VID_CODEC_PAL, D_AudioDK},
	{703250, D_VideoP, D_AudioDK, "P073 ", D_VID_CODEC_PAL, D_AudioDK},
	{711250, D_VideoP, D_AudioDK, "P074 ", D_VID_CODEC_PAL, D_AudioDK},
	{719250, D_VideoP, D_AudioDK, "P075 ", D_VID_CODEC_PAL, D_AudioDK},
	{727250, D_VideoP, D_AudioDK, "P076 ", D_VID_CODEC_PAL, D_AudioDK},
	{735250, D_VideoP, D_AudioDK, "P077 ", D_VID_CODEC_PAL, D_AudioDK},
	{743250, D_VideoP, D_AudioDK, "P078 ", D_VID_CODEC_PAL, D_AudioDK},
	{751250, D_VideoP, D_AudioDK, "P079 ", D_VID_CODEC_PAL, D_AudioDK},
	{759250, D_VideoP, D_AudioDK, "P080 ", D_VID_CODEC_PAL, D_AudioDK},
	{767250, D_VideoP, D_AudioDK, "P081 ", D_VID_CODEC_PAL, D_AudioDK},
	{775250, D_VideoP, D_AudioDK, "P082 ", D_VID_CODEC_PAL, D_AudioDK},
	{783250, D_VideoP, D_AudioDK, "P083 ", D_VID_CODEC_PAL, D_AudioDK},
	{791250, D_VideoP, D_AudioDK, "P084 ", D_VID_CODEC_PAL, D_AudioDK},
	{799250, D_VideoP, D_AudioDK, "P085 ", D_VID_CODEC_PAL, D_AudioDK},
	{807250, D_VideoP, D_AudioDK, "P086 ", D_VID_CODEC_PAL, D_AudioDK},
	{815250, D_VideoP, D_AudioDK, "P087 ", D_VID_CODEC_PAL, D_AudioDK},
	{823250, D_VideoP, D_AudioDK, "P088 ", D_VID_CODEC_PAL, D_AudioDK},
	{831250, D_VideoP, D_AudioDK, "P089 ", D_VID_CODEC_PAL, D_AudioDK},
	{839250, D_VideoP, D_AudioDK, "P090 ", D_VID_CODEC_PAL, D_AudioDK},
	{847250, D_VideoP, D_AudioDK, "P091 ", D_VID_CODEC_PAL, D_AudioDK},
	{855250, D_VideoP, D_AudioDK, "P092 ", D_VID_CODEC_PAL, D_AudioDK},
	{863250, D_VideoP, D_AudioDK, "P093 ", D_VID_CODEC_PAL, D_AudioDK},
#endif	                         
};

static DEF_Dtv_srv Dtv_srv_test[] =
{
	{"Diver", 1, 0x20, 0x100, 0x100, 0x110, D_VID_CODEC_MPEG, D_AUD_CODEC_MPEG2, D_DB_SRV_TV},
};

static DEF_Dtv_Data Dtv_ts_test[] = 
{
	{D_FEND_DTMB, 52, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 60, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 68, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 80, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 88, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 171, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 179, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 187, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 195, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 203, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 211, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 219, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 474, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 482, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 490, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 498, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 506, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 514, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 522, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 530, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 538, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 546, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 554, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 562, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 570, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 578, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 586, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 594, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 602, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 610, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 618, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 626, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 634, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 642, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 650, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 658, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 666, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 674, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 682, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 690, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 698, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 706, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 714, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 722, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 730, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 738, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 746, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 754, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 762, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 770, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 778, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 786, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 794, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 802, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 810, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 818, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 826, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 834, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 842, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 850, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 858, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
	{D_FEND_DTMB, 866, 0, 0, 1, 1, sizeof(Dtv_srv_test) / sizeof(Dtv_srv_test[0]), Dtv_srv_test},
};

static DEF_DBIfo def_db2610d[] =
{
    {Atv_srv_boe, sizeof(Atv_srv_boe) / sizeof(Atv_srv_boe[0]), Dtv_ts_boe, sizeof(Dtv_ts_boe) / sizeof(Dtv_ts_boe[0])},
    {Atv_srv_ctv, sizeof(Atv_srv_ctv) / sizeof(Atv_srv_ctv[0]), Dtv_ts_ctv, sizeof(Dtv_ts_ctv) / sizeof(Dtv_ts_ctv[0])},
    {Atv_srv_test, sizeof(Atv_srv_test) / sizeof(Atv_srv_test[0]), Dtv_ts_test, sizeof(Dtv_ts_test) / sizeof(Dtv_ts_test[0])},
};


D_Result p_precast_program(D_U32 param)
{
    D_ATVSCAN_SET scan_set;
    D_ScanTsInfoNode *scants;
    D_DBTSInfo ts_info;
    D_DBSrvInfo srvinfo;
    D_U8    i, j, idx;
    D_DBID  dbtsid, dbsrvid;

    idx = D_MIN(param, 2);

    d_dbase_set_rset_en(0);
#if 0
    d_dbase_clear_srv_by_type(D_DB_SRV_ACTION_ATV);
    d_dbase_delete_ts_by_type(D_FEND_ANALOG);
#else
    d_dbase_clear_srv();
    d_dbase_clear_ts();
    d_dbase_clear_sat();
    d_dbase_clear_ante();
#endif

#ifdef HI_SOFT_TYPE_DVBS
    d_dbase_add_default_data_dvbs();
#else
    p_tvconf_get_cur_atvscan(&scan_set);

    for(i = 0; i < def_db2610d[idx].atv_cnt; i++)
    {
        D_DB_TS_INFO_INIT(&ts_info);
        ts_info.tuner_type = D_FEND_ANALOG;
        ts_info.param.atv.fltCenterAdj = scan_set.fltCenterAdj;
        ts_info.param.atv.fltBwAdj = scan_set.fltBwAdj;
        ts_info.param.atv.freq = def_db2610d[idx].atv[i].freq;
        ts_info.param.atv.videoMode = def_db2610d[idx].atv[i].videoMode;
        ts_info.param.atv.audioMode = def_db2610d[idx].atv[i].audioMode;
        ts_info.param.atv.SoundSys = SoundSys_FmMono;

        dbtsid = d_dbase_insert_ts(&ts_info);
        if(dbtsid != -1)
        {
            D_DB_SRV_INFO_INIT(&srvinfo);
            srvinfo.srv_type = D_DB_SRV_ATV;
            srvinfo.db_ts_id = dbtsid;

            if(!g_custom_config.sys_setup.vol_compensate)
            {
                if(g_custom_config.scan.volume > D_STB_VOLUME_MAX)
                {
                    g_custom_config.scan.volume = 0;
                }
                srvinfo.volume = g_custom_config.scan.volume;
            }

            if(srvinfo.chan_num == -1)
            {
                srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
            }

            sprintf(srvinfo.name, def_db2610d[idx].atv[i].name);
            srvinfo.vid_codec = def_db2610d[idx].atv[i].vid_codec;
            srvinfo.aud1_codec = def_db2610d[idx].atv[i].aud1_codec;

            dbsrvid = d_dbase_insert_srv (&srvinfo);
            if (-1 == dbsrvid)
            {
                D_ERROR ("Cannot add new ATV service !!!\n");
            }
            else
            {
                D_DUMP("Add ATV dbtsid: %03d dbsrvid:%03d -> num:%03d \n", srvinfo.db_ts_id, dbsrvid, srvinfo.chan_num);
            }
        }
    }

    for(i = 0; i < def_db2610d[idx].dtv_cnt; i++)
    {
        D_DB_TS_INFO_INIT(&ts_info);
        ts_info.db_net_id = D_DB_DEF_NET_ID;
        ts_info.db_sat_id = (D_U8) - 1;       
        ts_info.tuner_type = def_db2610d[idx].dtv[i].ftype;
        ts_info.param.freq = def_db2610d[idx].dtv[i].freq;
        if(i < 3)
        	ts_info.param.dtmb.freq_k = 5;
        ts_info.param.dvbc.baud = def_db2610d[idx].dtv[i].baud;
        ts_info.param.dvbc.mod = def_db2610d[idx].dtv[i].mode;
        ts_info.ts_id = def_db2610d[idx].dtv[i].ts_id;
        ts_info.org_net_id = def_db2610d[idx].dtv[i].org_net;
        
        dbtsid = p_dbase_insert_ts (&ts_info);
        if(dbtsid != -1)
        {
            for(j = 0; j < def_db2610d[idx].dtv[i].srv_cnt; j++)
            {
                D_DB_SRV_INFO_INIT(&srvinfo);

                srvinfo.db_ts_id = dbtsid;

                if(!g_custom_config.sys_setup.vol_compensate)
                {
                    if(g_custom_config.scan.volume > D_STB_VOLUME_MAX)
                    {
                        g_custom_config.scan.volume = 0;
                    }
                    srvinfo.volume = g_custom_config.scan.volume;
                }

                if(g_custom_config.scan.track <= 3 )
                {
                    srvinfo.aud_track = g_custom_config.scan.track;
                }

                if(srvinfo.chan_num == -1)
                {
                    srvinfo.chan_num = d_dbase_get_free_chan_num((D_DBSrvType)srvinfo.srv_type);
                }

                sprintf(srvinfo.name, def_db2610d[idx].dtv[i].srv[j].name);
                srvinfo.srv_id = def_db2610d[idx].dtv[i].srv[j].srv_id;
                srvinfo.pmt_pid = def_db2610d[idx].dtv[i].srv[j].pmt_pid;
                srvinfo.pcr_pid = def_db2610d[idx].dtv[i].srv[j].pcr_pid;
                srvinfo.vid_pid = def_db2610d[idx].dtv[i].srv[j].vid_pid;
                srvinfo.aud1_pid = def_db2610d[idx].dtv[i].srv[j].aud1_pid;
                srvinfo.vid_codec = def_db2610d[idx].dtv[i].srv[j].vid_codec;
                srvinfo.aud1_codec = def_db2610d[idx].dtv[i].srv[j].aud1_codec;
                srvinfo.srv_type = def_db2610d[idx].dtv[i].srv[j].srv_type;

                dbsrvid = d_dbase_insert_srv (&srvinfo);
                if (-1 == dbsrvid)
                {
                    D_ERROR ("Cannot add new DTV service !!!\n");
                }
                else
                {
                    D_DUMP("Add DTV dbtsid: %03d dbsrvid:%03d -> num:%03d \n", srvinfo.db_ts_id, dbsrvid, srvinfo.chan_num);
                }
            }
        }
    }
#endif
    d_dbase_flush();
    return D_OK;
}

/**@}*/
