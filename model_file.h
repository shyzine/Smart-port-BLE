#ifndef _MODEL_FILE_H_
#define _MODEL_FILE_H_

#include <stdint.h>
#include "MixerConfig.h"
#include "telemetry_file.h"

#if defined ( __CC_ARM   )
	#define __PACK__
#elif defined ( __ICCARM__ )
	#define __PACK__
#elif defined   (  __GNUC__  )
	#define __PACK__  __attribute__((packed))
#endif

//define the macro value
#define TELEMETRY_SOUND_NUM		50
#define SPECIAL_FUNC_NUM		32

//define TIMER MODE
typedef enum _e_TimerModes
{
    TMRMODE_NONE,
    TMRMODE_ABS,
    TMRMODE_THR,
    TMRMODE_THR_REL,
    TMRMODE_THR_TRG,
    TMRMODE_FIRST_SWITCH
}TimerModes;

#pragma pack(1)
// define TimerStates
typedef struct _t_TimerState
{
    uint16_t cnt;
    uint16_t sum;
    uint8_t  state;
    int16_t  val;
    uint16_t  val_1000ms;
}__PACK__ TimerState;

typedef struct t_ChannelMap
{
    char    channelEnable;    //channel have exports
    char    vChannelName[FUNC_NAME_LEN];
}__PACK__ ChannelMap;

typedef struct t_TrimConfig {
	uint8_t SteptrimArray[NUM_PHY_TRIMS];  ///< steps of the trim
	uint8_t	TrimReverseFlag[NUM_PHY_TRIMS];	///< reverse flag(no used)
	uint8_t InctrimMode:2;	///< 0: separate; 1:combine
	uint8_t trimDisplayMode:2;	///< 0:value  1:x%(no used)
} __PACK__ TrimConfig;

/// trainer port setting for 4 trainer channel
typedef struct t_TrainerMasterData {
    uint8_t mode:2;                ///< off/+=/:= 0:off 1:add; 2:replace
    uint8_t stu_weight;            ///< student weight
    uint8_t function_channel;      ///< function channel
}__PACK__ TrainerMasterData;


typedef struct t_RF_SYSTEM_v13 {
    uint8_t         state:1;            ///<1:on  0:off
    uint8_t        rfprotocol:3;       ///< communication protocols(0:D16;1:D8;2:LR12;3:CPPM)

    uint8_t        channelsStart;       ///< first is 0
    uint8_t        channelsEnd;        ///<  0~31 channels

    uint8_t     rxNumber;         ///< receiver number
    uint8_t     ppmPolarity:1;

    uint8_t     extAnt:1; ///< antenna 1 :ext; 0: int
    uint8_t     notelemetry:1;///< set tele  1 :no; 0: with
    uint8_t     channel_after:1;///< set ch range  1 :9-16; 0: 1-8
//    uint8_t     powerLevel:2;//0-10mw 1-100mw 2-500mw 3-1000mw
//    uint8_t     noSport:1;

}__PACK__ RF_SYSTEM_v13;

typedef struct t_RF_SYSTEM_11 {
	uint8_t 		state:1;			///<1:on  0:off
    uint8_t        rfprotocol:3;       ///< communication protocols(0:D16;1:D8;2:LR12;3:CPPM)
    
    uint8_t        channelsStart;		///< first is 0
    uint8_t        channelsEnd;        ///<  0~31 channels
    
    uint8_t   	rxNumber;         ///< receiver number
    uint8_t     ppmPolarity:1;

}__PACK__ RF_SYSTEM_11;

typedef struct t_RF_SYSTEM {
	uint8_t 		state:1;			///<1:on  0:off
    uint8_t        rfprotocol:3;       ///< communication protocols(0:D16;1:D8;2:LR12;3:CPPM)
    
    uint8_t        channelsStart;		///< first is 0
    uint8_t        channelsEnd;        ///<  0~31 channels
    
    uint8_t   	rxNumber;         ///< receiver number
    uint8_t     ppmPolarity:1;

    uint8_t     extAnt:1; ///< antenna 1 :ext; 0: int
    uint8_t     notelemetry:1;///< set tele  1 :no; 0: with
	uint8_t     channel_after:1;///< set ch range  1 :9-16; 0: 1-8
	uint8_t     powerLevel:2;//0-10mw 1-100mw 2-500mw 3-1000mw
	uint8_t     noSport:1;

}__PACK__ RF_SYSTEM;


typedef struct t_FAILSAFE {
    uint8_t  	failsafeMode[NUM_VIRTUAL_CHANNEL]; 		///< fail-safe mode 0-2:Hold/Custom/No pulse
    int16_t    failsafeValue[NUM_VIRTUAL_CHANNEL];		///< -100~+100 for servo monitor
}__PACK__ FAILSAFE;

typedef struct t_TimerData {
    uint8_t  mode:1;             ///< timer count up:0 or count down:1;
    uint8_t  sound:2;  		///< mute:0 or beep:1 speech:2 when last 10 seconds
    uint8_t  vibes:1;     		///< vibes :1 or not : 0 when last 10 seconds
    uint8_t  persistent:1;     ///< timer value be saved when power down:1
    uint8_t  spare;          ///< spare for other
    uint16_t start;		    ///< timer start from value
    uint16_t  source;        ///trigger source:sw,throttle,off
    uint16_t  reset_src;        ///reset source:sw or off
    uint16_t  value;            ///< seconds left
} __PACK__ TimerData;

///< different flight trim value
typedef struct t_TrimIncData
{
    int16_t trimArray[NUM_PHY_TRIMS];
    // add trim set
}__PACK__ TrimIncData;

typedef  struct{
    char    name[LEN_CURVE_NAME];
    int8_t   type;              ///< 0, exp; 1, line, 2 :curve; 3,multiLine; 4, multiCurve
    signed char  points[22];      ///< 7-point values for -99, 99
    int k;
	int8_t e_weigth;
	int16_t e_offset;
	int8_t count;
}__PACK__ CurveData;

typedef struct _t_SourceMixer
{
    unsigned char type;        ///<source type
    short id;                    ///< source number
}__PACK__ SourceMixer;

/// phase is on by trim
typedef struct t_PhaseData {
    char name[LEN_FP_NAME];     ///< flight phase name
    SourceMixer src_condition;    ///< src
    uint16_t fadeIn;        ///< fade in out time
}__PACK__ PhaseData;

#define MULTIPLEX_MODE_ADD 0
#define MULTIPLEX_MODE_MULTIPLY 1
#define MULTIPLEX_MODE_SUBST 2

typedef struct t_Weight_Data{
    int8_t  weight_left;           ///< weight is, -100~100
    int8_t  weight_right;
    uint16_t weight_activeMap;    ///< it is or with the sw
    SourceMixer sw_weight;
}__PACK__ Weight_Data;

typedef struct t_offset_Data {
    int16_t  offset1;       ///< offset add to src channel value
    uint16_t offset_activeMap;    ///< it is or with the sw
    SourceMixer sw_offset;
}__PACK__ offset_Data;

typedef struct t_Curve_Data {
    uint8_t curveNumber;          ///< curve number
    uint16_t curve_activeMap;    ///< it is or with the sw
    SourceMixer sw_curve;
}__PACK__ Curve_Data;

#define MIXER_SLOT_NON_AVAILABLE (0)

typedef struct t_MixToData_V13 {
    SourceMixer src;                 ///< source channel, pot or switch
    SourceMixer sw;                  ///< active if sw is TRUE, sw could be SW or VSW

    uint16_t activePhaseMap;   ///< phase active bitmap: B0 ==1? active in flight_phase_0; B1==1? active in flight phase_1;
    uint8_t isCarryTrim;    ///< if source carry trim

    Weight_Data  weight_Dt[5];
    offset_Data  offsetDt[5];        ///<offset
    Curve_Data   curveDt[5];        ///<curve

    uint8_t mltplxMode;            ///< multiplex method: 0 means +=, 1 means *=, 2 means :=
    uint8_t next;           ///< next mixer for this channel, 0 for end of mixer train
    uint8_t valid;        ///< mixer in operation
}__PACK__ Mixer_v13;

typedef struct t_MixToData {
    SourceMixer src;                 ///< source channel, pot or switch
    SourceMixer sw;                  ///< active if sw is TRUE, sw could be SW or VSW

    uint16_t activePhaseMap;   ///< phase active bitmap: B0 ==1? active in flight_phase_0; B1==1? active in flight phase_1;
    uint8_t isCarryTrim;    ///< if source carry trim

    Weight_Data	 weight_Dt[NUM_CURVES_WEIGHT];
    offset_Data  offsetDt[NUM_CURVES_WEIGHT];        ///<offset
    Curve_Data   curveDt[NUM_CURVES_WEIGHT];        ///<curve

    uint8_t next;           ///< next mixer for this channel, 0 for end of mixer train
    uint8_t valid;        ///< mixer in operation
}__PACK__ Mixer;



typedef struct t_LogicSwitchToMix {
	uint8_t  LogicSw_Type;	//1:< ;2:=; 3> ;4:&& ;5: || ;6:^; 7: !;

    SourceMixer src_Left;            ///< source channel, pot or vPot
    SourceMixer src_Right;          ///< source channel, pot or vPot
}__PACK__ LogicSwitchToMix;

typedef struct t_ServoData {
	uint8_t		reverseFlag:1;	//reverse flag
    int16_t		endPoint_min;	//calibrate the min&max (it is the end point)
    int16_t		endPoint_max;
    int16_t 	subTrim;		//sub-trim
    uint16_t	fadeSpeedTim;	//channel fade speed time when out up
    uint16_t    nfadeSpeedTim;//channel fade speed time when out down
    int16_t		endPoint_lmtmin;	//calibrate the min&max (it is the end point)
    int16_t		endPoint_lmtmax;
    
}__PACK__ ServoData;

//map for set
typedef struct t_PORT_MAP {
    uint8_t        nPortFunctionID;
    uint8_t        nPortPhysisID;
}__PACK__ PORT_MAP;

typedef struct t_PHYSIS_MAP {
    PORT_MAP    stPortMap[NUM_PORT_MAP];
}__PACK__ PHYSIS_MAP;

typedef struct t_CHANNEL_TO_FUNCTION {
    uint8_t        nChannelID;
    uint8_t        nActualFunctionID;
}__PACK__ CHANNEL_TO_FUNCTION;

/* telemetry sound data */
typedef struct t_TELEMETRY_SOUND {
	uint8_t		cEnable;		//open flag; 0->disable   1->enable
	uint8_t		nTelemetryNum;	//telemetry number 0 -> SWR
	uint8_t		nCalculateType;	//calculate type  0:none   1->greater 2->less 3->equal
	int16_t		nCompareValue;	//compare value	-32738~32768
	uint8_t		cHapticEnable;	//open haptic; 0->disable   1->enable
	uint8_t		nCurTicks;		//play sample ticks	0:start
}__PACK__ TELEMETRY_SOUND;

/* special function data */
typedef enum {
    PLAY_TRACK = 1,
    PLAY_VALUE,
    HAPTIC,
    CENTER_TRIM,
    CLEAR_CONSP,
    TELE_LOG,
    MUSIC_NEXT,
    MUSIC_PREV,
    PLAY_PAUSE,
    PRINTSCREEN,
    READTIMER,
    READBATTERY,
    PLAYVARIO,
} specFunctions;

typedef struct t_SPECIAL_FUNCTION {
	uint8_t		cEnable:1;			//open flag; 0->disable   1->enable
	uint8_t     delay:7;    //0:once 1:5s 2:10s 3:15s....120s
	SourceMixer	swSpecialFunction;	//sw for special function
	uint8_t		cRunShellType;		//run shell type	0:no 1:play sound 2:play track 3:play value 4: haptic
	uint8_t		cReserved[10];		//reserved region
	uint8_t		nCurTicks;		    //play sample ticks	0:start
}__PACK__ SPECIAL_FUNCTION;

/* slot define*/
typedef struct t_Slot_State {
    unsigned char cur_index;
    unsigned char slotState[NUM_MIXER];
    unsigned char UsedNum;
}__PACK__ Slot_State;

/**************************************************/
//different plane type
//airplane
#define MODEL_AIRPLANE_NORMAL			0
#define MODEL_AIRPLANE_FLYING_WING      1
#define MODEL_AIRPLANE_V_TAIL			2
//heli
#define MODEL_HELICOPTER_H_1            10
#define MODEL_HELICOPTER_H_4            11
#define MODEL_HELICOPTER_HE3            12
#define MODEL_HELICOPTER_H_3            13
#define MODEL_HELICOPTER_HR3            14
#define MODEL_HELICOPTER_H_4X           15
//glider
#define MODEL_GLIDER_NORMAL         	20
#define MODEL_GLIDER_V_TAIL             21

#define MODEL_MULTICOPTER 	30
#define MODEL_CUSTOM 	40
//model type
typedef struct t_ModelType
{
    unsigned short model_type;
    unsigned char stickMode;
}ModelType;

///< model file
typedef struct t_ModelFile {
    unsigned short      checkSum;           ///< crc value

    uint32_t            ModelVersion;          ///< current Model version

    char                name[LEN_MODEL_NAME]; ///< Name
    char                modelBmpPath[BITMAP_PATH_LEN];   ///< bitmap
    char                modeMusic[BITMAP_PATH_LEN];
    ModelType           stModelType;        ///< Model type Number

    //model start in judge
    int16_t             nThrSafeOperater;    ///< thr safe pos  : 0 : thr <= safePos, poss; 1: thr >= safePos, poss
    int16_t             nThrSafePos;    ///< thr safe pos
    uint8_t             nSwitchSafePos[NUM_SW_POSITION];    /// switch safe pos

    //first:Thr;second:Rud*2,third:Ele*2;fourth:(Ail|FLP)*6
    ChannelMap          mapCh[NUM_CHANNEL];    ///< model type -> channel_map

    //TrainerSlaveData trainerSlaveData;
    uint8_t             trainerMode:1;          //0:Master,1:Slave
    uint8_t             trainerType:1;          //0:cable   1:wireless   //ashang 2015.12.16
    TrainerMasterData   trainerMasterCh[8];      ///< trainer port
    SourceMixer         sw_trainer;                ///<sw for trainer

    //stick direction but is used in systemFile
    uint8_t             StickDir[NUM_ACTUALLY_POT+NUM_SWS]; ///< 0:normal ; 1:reverse

    ///< RF system
    RF_SYSTEM           moduleData[2];//internal + external RF system
    ///< Two Timers
    TimerData           timers[MAX_TIMERS];        ///< timers for mix
    ///< Trim Setup
    TrimConfig          trimSet;

    ///< flight phase
    PhaseData           phaseData[NUM_PHASE];         ///< flight phase
    TrimIncData         trimInc[NUM_PHASE];        ///< Trim Increments

    ///< mixer set
    Mixer               mixerSlot[NUM_MIXER];          ///< mixer slot for a model, mixerSlot[0] should never be used,
    int8_t              mixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    Mixer               ExtraMixerSlot[NUM_EXTRA_MIXER]; // 0 unused
    int8_t              ExtraMixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    //HeliData              heli;                       ///< heli ccpm and swash-ring
    LogicSwitchToMix    mixerLogicSwitchs[NUM_LOGIC_SW+NUM_EXTRA_LOGIC_SW];     ///<Logic switch for mixer
    int8_t              logicSwShowOrder[8];        ///<Logic switch for mixer

    CurveData           DefaultCurveData;                   ///< default curve
    CurveData           AllcurveData[NUM_ALL_CURVES];         ///< all curve lines for mixer

    CurveData           ExtraAllcurveData[EXTRA_NUM_CURVES];         ///< all curve lines for mixer

    ///< limit output
    ServoData           servoData[NUM_VIRTUAL_CHANNEL];
    ///< failsafe mode & values
    FAILSAFE            failsafeData;

    //PhysicalMap
    PHYSIS_MAP          stPhyMap;

    //ChannelMap
    CHANNEL_TO_FUNCTION stChannelToFunction[NUM_CHANNEL_MAP];

    //Slot Map
    Slot_State          slotStateList;                      ///< globle Slot

    //tele User Data
    TeleUserData        teleUserData;

    //tele sound
    TELEMETRY_SOUND     stTeleSoundData[TELEMETRY_SOUND_NUM];

    //special function
    SPECIAL_FUNCTION    stSpecialFuncDat[SPECIAL_FUNC_NUM];

    uint16_t  imuAngleFull;

    //ashang 2016.2.23
    uint16_t  thrCutSlot;
    uint16_t  thrHoldSlot;
    uint32_t  usedSeconds;
    uint8_t   thrTrim:1;   //throttle trim enable
    uint8_t   disableThrottleWarning:1;
    uint16_t  beepANACenter;
    uint16_t switchWarningState;
    uint16_t potsWarnMode;
    uint16_t potsWarnEnabled;
    int      potsWarnPosition[32];
    uint8_t      generalSkip; //bit0:1--no open sound
    union
    {
        int rsv2;
        struct
        {
            char swashAILRate;
            char swashELERate;
        };
    };
    union
    {
        int rsv3;
        struct
        {
            char swashRate;
            char rsv6;
        };
    };
    int      swWarningPerState;
    int      rsv5;

    //tele input calibaration
    TeleInputCal    teleInputCalData;
}__PACK__ ModelFile;

typedef struct t_ModelFile_v13 {
    unsigned short      checkSum;           ///< crc value

    uint32_t            ModelVersion;          ///< current Model version

    char                name[LEN_MODEL_NAME]; ///< Name
    char                modelBmpPath[BITMAP_PATH_LEN];   ///< bitmap
    char                modeMusic[BITMAP_PATH_LEN];
    ModelType           stModelType;        ///< Model type Number

    //model start in judge
    int16_t             nThrSafeOperater;    ///< thr safe pos  : 0 : thr <= safePos, poss; 1: thr >= safePos, poss
    int16_t             nThrSafePos;    ///< thr safe pos
    uint8_t             nSwitchSafePos[NUM_SW_POSITION];    /// switch safe pos

    //first:Thr;second:Rud*2,third:Ele*2;fourth:(Ail|FLP)*6
    ChannelMap          mapCh[NUM_CHANNEL];    ///< model type -> channel_map

    //TrainerSlaveData trainerSlaveData;
    uint8_t             trainerMode:1;          //0:Master,1:Slave
    uint8_t             trainerType:1;          //0:cable   1:wireless   //ashang 2015.12.16
    TrainerMasterData   trainerMasterCh[8];      ///< trainer port
    SourceMixer         sw_trainer;                ///<sw for trainer

    //stick direction but is used in systemFile
    uint8_t             StickDir[NUM_ACTUALLY_POT+NUM_SWS]; ///< 0:normal ; 1:reverse

    ///< RF system
    RF_SYSTEM_v13           moduleData[2];//internal + external RF system
    ///< Two Timers
    TimerData           timers[MAX_TIMERS];        ///< timers for mix
    ///< Trim Setup
    TrimConfig          trimSet;

    ///< flight phase
    PhaseData           phaseData[NUM_PHASE];         ///< flight phase
    TrimIncData         trimInc[NUM_PHASE];        ///< Trim Increments

    ///< mixer set
    Mixer_v13               mixerSlot[NUM_MIXER];          ///< mixer slot for a model, mixerSlot[0] should never be used,
    int8_t              mixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    Mixer_v13               ExtraMixerSlot[NUM_EXTRA_MIXER]; // 0 unused
    int8_t              ExtraMixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    //HeliData              heli;                       ///< heli ccpm and swash-ring
    LogicSwitchToMix    mixerLogicSwitchs[NUM_LOGIC_SW+NUM_EXTRA_LOGIC_SW];     ///<Logic switch for mixer
    int8_t              logicSwShowOrder[8];        ///<Logic switch for mixer

    CurveData           DefaultCurveData;                   ///< default curve
    CurveData           AllcurveData[NUM_ALL_CURVES];         ///< all curve lines for mixer

    CurveData           ExtraAllcurveData[EXTRA_NUM_CURVES];         ///< all curve lines for mixer

    ///< limit output
    ServoData           servoData[NUM_VIRTUAL_CHANNEL];
    ///< failsafe mode & values
    FAILSAFE            failsafeData;

    //PhysicalMap
    PHYSIS_MAP          stPhyMap;

    //ChannelMap
    CHANNEL_TO_FUNCTION stChannelToFunction[NUM_CHANNEL_MAP];

    //Slot Map
    Slot_State          slotStateList;                      ///< globle Slot

    //tele User Data
    TeleUserData        teleUserData;

    //tele sound
    TELEMETRY_SOUND     stTeleSoundData[TELEMETRY_SOUND_NUM];

    //special function
    SPECIAL_FUNCTION    stSpecialFuncDat[SPECIAL_FUNC_NUM];

    uint16_t  imuAngleFull;

    //ashang 2016.2.23
    uint16_t  thrCutSlot;
    uint16_t  thrHoldSlot;
    uint32_t  usedSeconds;
    uint8_t   thrTrim:1;   //throttle trim enable
    uint8_t   disableThrottleWarning:1;
    uint16_t  beepANACenter;
    uint16_t switchWarningState;
    uint16_t potsWarnMode;
    uint16_t potsWarnEnabled;
    int      potsWarnPosition[32];
    uint8_t      generalSkip; //bit0:1--no open sound
    union
    {
        int rsv2;
        struct
        {
            char swashAILRate;
            char swashELERate;
        };
    };
    union
    {
        int rsv3;
        struct
        {
            char swashRate;
            char rsv6;
        };
    };
    int      swWarningPerState;
    int      rsv5;

    //tele input calibaration
    TeleInputCal    teleInputCalData;
}__PACK__ ModelFile_v13;

typedef struct t_ModelFile_v12 {
    unsigned short 		checkSum;			///< crc value

    uint32_t   			ModelVersion;          ///< current Model version

    char      			name[LEN_MODEL_NAME]; ///< Name    
    char   				modelBmpPath[BITMAP_PATH_LEN];   ///< bitmap
    char                modeMusic[BITMAP_PATH_LEN];
    ModelType			stModelType;		///< Model type Number
    
    //model start in judge
    int16_t             nThrSafeOperater;    ///< thr safe pos  : 0 : thr <= safePos, poss; 1: thr >= safePos, poss
    int16_t			    nThrSafePos;	///< thr safe pos
    uint8_t				nSwitchSafePos[NUM_SW_POSITION];	/// switch safe pos

    //first:Thr;second:Rud*2,third:Ele*2;fourth:(Ail|FLP)*6
    ChannelMap			mapCh[NUM_CHANNEL];    ///< model type -> channel_map
    
    //TrainerSlaveData trainerSlaveData;
    uint8_t				trainerMode:1;			//0:Master,1:Slave
    uint8_t             trainerType:1;          //0:cable   1:wireless   //ashang 2015.12.16
    TrainerMasterData	trainerMasterCh[8];      ///< trainer port
    SourceMixer			sw_trainer;                ///<sw for trainer
    
    //stick direction but is used in systemFile
    uint8_t				StickDir[NUM_ACTUALLY_POT+NUM_SWS];	///< 0:normal ; 1:reverse

    ///< RF system
    RF_SYSTEM_v13           moduleData[2];//internal + external RF system
    ///< Two Timers
    TimerData           timers[MAX_TIMERS];        ///< timers for mix
    ///< Trim Setup
    TrimConfig			trimSet;
    
    ///< flight phase
    PhaseData           phaseData[NUM_PHASE];         ///< flight phase
    TrimIncData			trimInc[NUM_PHASE];        ///< Trim Increments
    
    ///< mixer set
    Mixer_v13   			mixerSlot[NUM_MIXER];          ///< mixer slot for a model, mixerSlot[0] should never be used,
    int8_t 				mixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    Mixer_v13               ExtraMixerSlot[NUM_EXTRA_MIXER]; // 0 unused
    int8_t              ExtraMixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    //HeliData  			heli;                		///< heli ccpm and swash-ring
    LogicSwitchToMix	mixerLogicSwitchs[NUM_LOGIC_SW+NUM_EXTRA_LOGIC_SW];		///<Logic switch for mixer
    int8_t              logicSwShowOrder[8];        ///<Logic switch for mixer

    CurveData			DefaultCurveData;					///< default curve
    CurveData  			AllcurveData[NUM_ALL_CURVES];         ///< all curve lines for mixer
    
    CurveData  			ExtraAllcurveData[EXTRA_NUM_CURVES];         ///< all curve lines for mixer

    ///< limit output
    ServoData           servoData[NUM_VIRTUAL_CHANNEL];
    ///< failsafe mode & values
    FAILSAFE			failsafeData;
    
    //PhysicalMap
    PHYSIS_MAP			stPhyMap;

    //ChannelMap
    CHANNEL_TO_FUNCTION	stChannelToFunction[NUM_CHANNEL_MAP];

    //Slot Map
    Slot_State			slotStateList;						///< globle Slot

    //tele User Data
    TeleUserData 		teleUserData;

    //tele sound
    TELEMETRY_SOUND		stTeleSoundData[TELEMETRY_SOUND_NUM];

    //special function
    SPECIAL_FUNCTION	stSpecialFuncDat[SPECIAL_FUNC_NUM];

	uint16_t  imuAngleFull;

	//ashang 2016.2.23 
	uint16_t  thrCutSlot;
	uint16_t  thrHoldSlot;
	uint32_t  usedSeconds;
    uint8_t   thrTrim:1;   //throttle trim enable
    uint8_t   disableThrottleWarning:1;
    uint16_t  beepANACenter;
    uint16_t switchWarningState;
    uint16_t potsWarnMode;
    uint16_t potsWarnEnabled;
    int      potsWarnPosition[32];
    uint8_t      generalSkip; //bit0:1--no open sound
    union
    {
        int rsv2;
        struct
        {
            char swashAILRate;
            char swashELERate;
        };
    };
    union
    {
        int rsv3;
        struct
        {
            char swashRate;
            char rsv6;
        };
    };
	int      rsv4;
	int      rsv5;

}__PACK__ ModelFile_v12;

typedef struct t_ModelFile_v11
{
    unsigned short 		checkSum;			///< crc value

    uint32_t   			ModelVersion;          ///< current Model version

    char      			name[LEN_MODEL_NAME]; ///< Name    
    char   				modelBmpPath[BITMAP_PATH_LEN];   ///< bitmap
    char                modeMusic[BITMAP_PATH_LEN];
    ModelType			stModelType;		///< Model type Number
    
    //model start in judge
    int16_t             nThrSafeOperater;    ///< thr safe pos  : 0 : thr <= safePos, poss; 1: thr >= safePos, poss
    int16_t			    nThrSafePos;	///< thr safe pos
    uint8_t				nSwitchSafePos[NUM_SW_POSITION];	/// switch safe pos

    //first:Thr;second:Rud*2,third:Ele*2;fourth:(Ail|FLP)*6
    ChannelMap			mapCh[NUM_CHANNEL];    ///< model type -> channel_map
    
    //TrainerSlaveData trainerSlaveData;
    uint8_t				trainerMode:1;			//0:Master,1:Slave
    uint8_t             trainerType:1;          //0:cable   1:wireless   //ashang 2015.12.16
    TrainerMasterData	trainerMasterCh[8];      ///< trainer port
    SourceMixer			sw_trainer;                ///<sw for trainer
    
    //stick direction but is used in systemFile
    uint8_t				StickDir[NUM_ACTUALLY_POT+NUM_SWS];	///< 0:normal ; 1:reverse

    ///< RF system
    RF_SYSTEM_11           moduleData[2];//internal + external RF system
    ///< Two Timers
    TimerData           timers[MAX_TIMERS];        ///< timers for mix
    ///< Trim Setup
    TrimConfig			trimSet;
    
    ///< flight phase
    PhaseData           phaseData[NUM_PHASE];         ///< flight phase
    TrimIncData			trimInc[NUM_PHASE];        ///< Trim Increments
    
    ///< mixer set
    Mixer_v13   			mixerSlot[NUM_MIXER];          ///< mixer slot for a model, mixerSlot[0] should never be used,
    int8_t 				mixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    Mixer_v13               ExtraMixerSlot[NUM_EXTRA_MIXER]; // 0 unused
    int8_t              ExtraMixerHead[NUM_CHANNEL];    ///<  first mixer slot for this channel
    //HeliData  			heli;                		///< heli ccpm and swash-ring
    LogicSwitchToMix	mixerLogicSwitchs[NUM_LOGIC_SW+NUM_EXTRA_LOGIC_SW];		///<Logic switch for mixer
    int8_t              logicSwShowOrder[8];        ///<Logic switch for mixer

    CurveData			DefaultCurveData;					///< default curve
    CurveData  			AllcurveData[NUM_ALL_CURVES];         ///< all curve lines for mixer
    
    CurveData  			ExtraAllcurveData[EXTRA_NUM_CURVES];         ///< all curve lines for mixer

    ///< limit output
    ServoData           servoData[NUM_VIRTUAL_CHANNEL];
    ///< failsafe mode & values
    FAILSAFE			failsafeData;
    
    //PhysicalMap
    PHYSIS_MAP			stPhyMap;

    //ChannelMap
    CHANNEL_TO_FUNCTION	stChannelToFunction[NUM_CHANNEL_MAP];

    //Slot Map
    Slot_State			slotStateList;						///< globle Slot

    //tele User Data
    TeleUserData_v11 		teleUserData;

    //tele sound
    TELEMETRY_SOUND		stTeleSoundData[TELEMETRY_SOUND_NUM];

    //special function
    SPECIAL_FUNCTION	stSpecialFuncDat[SPECIAL_FUNC_NUM];

	uint16_t  imuAngleFull;

	//ashang 2016.2.23 
	uint16_t  thrCutSlot;
	uint16_t  thrHoldSlot;
	uint32_t  usedSeconds;
    uint8_t   thrTrim:1;   //throttle trim enable
    uint8_t   disableThrottleWarning:1;
    uint16_t  beepANACenter;
    uint16_t switchWarningState;
    uint16_t potsWarnMode;
    uint16_t potsWarnEnabled;
    int      potsWarnPosition[32];
    uint8_t      generalSkip; //bit0:1--no open sound
    union
    {
        int rsv2;
        struct
        {
            char swashAILRate;
            char swashELERate;
        };
    };
    union
    {
        int rsv3;
        struct
        {
            char swashRate;
            char rsv6;
        };
    };
	int      swWarningPerState;//rsv4;
	int      rsv5;

}__PACK__ ModelFile_v11;


///< it is the origin config file header
typedef struct _t_CONFIG_HEADER
{
	unsigned char		nMixerNumber[NUM_CHANNEL];	//mixer number
	unsigned char		nAllMixerNumber;		//all mixer number

	unsigned char		nHeaderSize;			//size of header
	unsigned short		nChannelMapSize;		//size of channel map
	unsigned short		nLogicSwSize;			//logic sw number
	unsigned short		nmixerSlotSize;			//mixer slot number
	unsigned char		nPhyMapSize;			//phy size

	unsigned long		lConfigVersion;			//config version
	unsigned long		fileSize;				//file size
}__PACK__ CONFIG_HEADER;
#pragma pack()

#endif
