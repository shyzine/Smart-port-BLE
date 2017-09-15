/** @file 
* @brief 控设置的数据结构
* @author Robert Zhang <armner@gmail.com>
* @version 1.0.0
* @date 2013/10/03
*/
#ifndef _TRANSMITTER_FILE_H_
#define _TRANSMITTER_FILE_H_

#include <stdint.h>
#include "MixerConfig.h"

/// Virtual source types
#define SRC_TYPE_POT			(0)
#define SRC_TYPE_VPOT			(1)
#define SRC_TYPE_POT_CONST  	(2)

#define SRC_TYPE_SW         	(3)
#define SRC_TYPE_SW_TO_POT    	(4)
#define SRC_TYPE_VSW         	(5)
#define SRC_TYPE_LOGIC_SW     	(6)
#define SRC_TYPE_SW_CONST    	(7)

#define SRC_TYPE_CHANNEL    	(8)

#define SRC_VPOT_POT_TYPE    	(10)
#define SRC_VPOT_SW_TYPE    	(11)
#define SRC_VSW_POT_TYPE    	(12)
#define SRC_VSW_SW_TYPE        	(13)

#define SRC_TYPE_TELEMETRY    	(14)

#define SRC_TYPE_CONST_VALUE    (15)

#define SRC_TYPE_PHYPOT			(16)
#define SRC_TYPE_TRIM			(17)


/// virtual pot
#define CURVE_TYPE_EXPO 		(0)
#define CURVE_TYPE_LINE         (1)
#define CURVE_TYPE_SMOOTH 		(2)
#define CURVE_TYPE_MULTI 		(3)
#define CURVE_TYPE_MULTISMOOTH 		(4)



//define beep typde
typedef enum _e_BEEP_MSG
{
	e_audio_button_down,
    e_audio_battery_low,
    e_audio_phase_on,
    e_audio_timer_00,   //ashang timer stop
    e_audio_timer_over,
    e_audio_timer_minute,
    e_audio_trim_normal,
    e_audio_trim_middle,
    e_audio_trim_end,
    e_audio_timer_number,   //ashang  number
    e_audio_sound_set,
    e_audio_button_alarm,
    e_audio_button_down1,
    e_audio_mode_name,
    e_audio_alarm_nooperation
}BEEP_MSG;

//status of the SD card
typedef enum __SD_File_STATUS
{
	
    SD_STATUS_WORKING = 0x00,
    SD_STATUS_NO_DISK = 0x03,
    SD_STATUS_NO_INIT_FILE = 0x01,
    SD_STATUS_PROTECTED = 0x02,
    SD_STATUS_TRANS_FILE_FAILED = 0x04,
    SD_STATUS_MODEL_FILE_FAILED = 0x05,
    SD_STATUS_TRANS_VERSION_ERROR = 0x06,    
    SD_STATUS_MODEL_VERSION_ERROR=0x7,
    SD_STATUS_MOUNT_FAILED = 0x08,
    SD_STATUS_MODEL_VERSION=0x8,
    SD_STATUS_CREATE_ERROR=0x9,
	SD_STATUS_MKDIR_ERROR=0xA,
	SD_STATUS_NO_CONFIG=0xb,
	SD_STATUS_NO_MODELFILE=0xc
	
    
}SD_File_STATUS;

#pragma pack(1)
typedef struct{
    unsigned char type:4;        ///<source type
    short id;      ///< source number
    char name[LEN_VCH_NAME];
}Source;


typedef struct t_CH_VPOTS
{
    unsigned char type:4;        ///<source type()
    short id;                      ///< source number

    short min_value;
    short mid_value;
    short max_value;

    signed char point[7];   ///< 7-points curve, if source is pot; -99~+99
    int k;
    unsigned char curve_type;        ///< 0: curve_type_line; 1: curve_type_smooth
}CH_VPOTS;

#define STICK_DIFF_VALUE 20
typedef struct t_CH_VSW
{
    unsigned char type:4;        ///<source type()
    short id;      ///< source number

    short mid_value;    //judge value

    unsigned char reverseFlag;    //reverse flag
}CH_VSW;

typedef struct t_STICK_CALI
{
	short minValue;
	short maxValue;
	short midValue;
}STICK_CALI;

//GYRO CONFIG
typedef struct _t_GYRO_CONFIG
{
	unsigned char cUsedFlag;		//0:close   1:open
}GYRO_CONFIG;

#define TOUCH_X_CALI_RANGE	20
#define TOUCH_Y_CALI_RANGE	15

//touch cali struct
typedef struct _t_TOUCH_CALI_PAM
{
	unsigned short left_x;
	unsigned short right_x;
	unsigned short top_y;
	unsigned short bottom_y;
}TOUCH_CALI_PAM;

typedef struct _t_TOUCH_CONFIG
{
	unsigned short bNeedCaliFlag;
	TOUCH_CALI_PAM stCaliPam;
}TOUCH_CONFIG;

/// transmitter file
typedef struct t_TransmitterFile {
    unsigned short    chkSum;           ///< Summed up should be 0

    uint8_t		HardwareVersion[10];          ///< hd version
    uint8_t		SoftwareVersion[15];          ///< sf version

    uint16_t   variant;          ///<
    char      ownerName[LEN_USER_NAME];        ///< owner name
    char      ownerPwd[LEN_USER_NAME];  ///< password

    /*time about */
    int32_t   TotSeconds;      ///< since user use
    int8_t    timezone;         ///< country code  (-11)~(+12)
    int8_t    dateShowType;     ///< Date display format

    /*locked about*/
    int8_t    locked; ///< before locked  :0 :never locked ;  10: 10s; 30: 30s; 60: 60s; 120: 2m; 600: 10m

    STICK_CALI  caliData[NUM_POT];   ///< calibration
    short       imuMiddleAngle[2];

    uint8_t		curModelType;		///< model type
    int8_t		currModelName[LEN_MODEL_NAME];        ///< current model name

    int8_t    vBatCalib;        ///< battery calibration value, should be calculated to vBat
    int8_t    vBatMin;          ///< battery min
    int8_t    vBatMax;          ///< battery max
    
    CH_VSW    virtual_SW[NUM_VSW];         ///< virtual SW
    CH_VPOTS  virtual_Pot[NUM_VPOT];   ///< virtual pots

    //int8_t    buzzerMode:2;     ///< -2=quiet, -1=only alarms, 0=no keys, 1=all
    uint8_t   disableMemoryWarning:1;    ///< no warning for low memory
    uint8_t   disableAlarmWarning:1;     ///< no warning for alarm
    uint8_t   stickMode:2;      ///< RETA mode
    uint8_t   inactivityTimer;  ///< inactivity timer value, in seconds
    uint8_t   lightAutoOff;     ///< time last for back light off
    uint8_t   templateSetup;    ///< channel outputs map
    uint8_t   unexpectedShutdown:1;     ///< check for power failure
    

    
    /*display about*/
    uint8_t    backlightModeChanged:1;
    uint8_t    backlightMode;    ///< back light mode: 0:off;1:backlight for key; 2: backlight for stick;
    uint8_t    backlightValueChanged:1;
    uint8_t    backlightValue;   ///< back light pwm value: 1-100;
    uint8_t    backlightDurationChanged:1;
    uint16_t   backlightDuration;     ///< back light time :0 :always ;  10: 10s; 30: 30s; 60: 60s; 120: 2m; 600: 10m

    uint8_t    vBatWarnChanged:1;
    uint8_t   vBatWarn;         ///< battery warning value

    /*haptic about*/
    uint8_t   hapticState:1;//0 enabled;1 disabled
    uint8_t   hapticStrength;//0-4
    uint8_t   hapticHoldTimes;//0~4

    /*GYRO CONFIG*/
    GYRO_CONFIG		stGyroCfg;



    /* touch screen Cali Data */
    TOUCH_CONFIG	stTouchParam;

    /*sound about*/

    
    uint8_t    beepMode:2;       ///< 0=quiet, 1=only alarms, 2=only keys, 3=all

    uint8_t    silentAll;
	uint8_t    alarmVolume;		 /// 0=quiet,  >=1 && <=4
    uint8_t    keyVolume;		 /// 0=quiet,  >=1 && <=4
    uint8_t	   AllVolume;		 /// 0~100
    uint8_t    mp3Volume;//wismy 20160408,
    uint8_t    trimVolume;


	uint8_t  alarmVolumePot;//ashang 2016.2.3    6-7-8  s1-mpos-s2
	uint8_t  keyVolumnPot;
	uint8_t  trimVolumnPot;
	uint8_t  mp3VolumnPot;
	uint8_t  backlightPot;

	uint8_t  alarmVibsEnable:1;
	uint8_t  keyVibsEnable:1;
	uint8_t  trimVibsEnable:1;


	uint8_t beepLength:3;

	uint8_t gpsFormat:1;
	uint8_t  switchesDelay;
    uint8_t hapticLength;


	uint8_t rsv8_1;
	//battery ratio
	uint8_t vBatRatio;
	uint8_t rxNumber;
	uint16_t rsv16_1;
	uint16_t rsv16_2;
	uint16_t rsv16_3;

    /*end of TransmitterFile*/
}TransmitterFile;
#pragma pack()

/**********************************************************/
//define the File System
//physical path
#define LOGIC_PATH          		"0:"
#define LOGIC_SPI_PATH              "1:"                   

//System Files Path
#define SYSTEM_FILE_PATH    		"/SYSTEM"
//Transmitter File Name
#define DEFAULT_TRANSMITTER_NAME    "/transmitterFile.bin"
//Model File Name
#define DEFAULT_MODEL_NAME    		"AirPlane_0"

//AirPlane
#define MODEL_AIRPLANE_PATH			"/AirPlane"
//HeliCopter
#define MODEL_HELICOPTER_PATH		"/HeliCopter"
//Glider
#define MODEL_GLIDER_PATH			"/Glider"
//MultiCopter
#define MODEL_MULTICOPTER_PATH		"/MultiCopter"
//Custom
#define MODEL_CUSTOM_PATH			"/Custom"

//Logs Path
#define TELEMETRY_LOGS_FILE_PATH    "0:/LOGS"
//System Config Path
#define MODEL_CONFIG_PATH   		"/CONFIG"
#define FIRMWARE_PATH   		    "0:/FIRMWARE"


//music path
#define MUSIC_PATH     				"0:/MUSIC"

//sound path
#define SOUND_ORIGIN_PATH			"/SOUNDS"
#define SOUND_LAN_PATH				"/en"
#define SOUND_ALL_PATH				"/SOUNDS/en"
#define SOUND_TEL_PATH				"/TeleData"
#define SOUND_FX_PATH				"/Fixed"
#define SOUND_TK_PATH				"/Track"
#define SOUND_VE_PATH				"/Value"

#endif
