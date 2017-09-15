#ifndef __GUI_EXTERN_INTERFACE
#define __GUI_EXTERN_INTERFACE

// it use c interface

#ifdef __cplusplus
extern "C" {
#endif
    
	#include "platform.h"
    #include "model_file.h"
    #include "transmitter_file.h"
    #include "telemetry_file.h"
    #include "task_telemetry.h"
    #include "ff.h"
	#include "task_gps.h"
	#include "task_system.h"
	#include "task_mix.h"

    extern TransmitterFile *tempTransmitterFile;
    extern ModelFile    *tempModelFile;

    //message
    // it is for trim
    #define MSG_DRIVER_TRIM_CHANGED (WM_USER + 0xff)
	#define MSG_DRIVER_PORT_CHANGED (WM_USER + 0xfe)
	#define MSG_DRIVER_SWITCH_CHANGED (WM_USER + 0xfd)
    // it is for encoder
	#define MSG_DRIVER_ENCODER_LEFT (WM_USER + 0xfc)
	#define MSG_DRIVER_ENCODER_RIGHT (WM_USER + 0xfb)
    // it is for pageUp & pageDown
	#define MSG_PG_UP 				(WM_USER + 0xfa)
	#define MSG_PG_DOWN 			(WM_USER + 0xf9)

	#define	PlayHapticDefault()	playhaptic(tempTransmitterFile.hapticStrength,50,30)
	#define playHapticRed()	playhaptic(tempTransmitterFile.hapticStrength,80,20)
	#define	playHapticOrange()	palyhaptic(tempTransmitterFile.hapticStrength,60,20)

    typedef struct t_ModelOthers
    {
        char modelImageName[50];
        char modeMusic[BITMAP_PATH_LEN];
    }ModelOthers;

    typedef struct _t_CREATE_MODEL
    {
        char create_name[LEN_MODEL_NAME - 14];
        ModelType stModelType;
        ModelOthers    stModelPam;
    }CREATE_MODEL;

    typedef struct _t_COPY_MODEL
    {
        char copy_src[LEN_MODEL_NAME];
        char copy_dst[LEN_MODEL_NAME];
    }COPY_MODEL;

    //进入临界区
    void EnterSystemfileCritical(void);
    //退出临界区
    void ExitSystemfileCritical(void);

    //写系统文件加CRC校验
    void AddFileSystemCheck(void *pSysFile, unsigned short nFileLen);
    //读出文件进行CRC校验
    char CheckFileSystem(void *pSysFile, unsigned short nFileLen);

    //获取电压值
    short BatteryVoltageGet(void);
    
    //电位器状态获取(输入analog_raw_len的地址，获取的是模拟量的长度;输出的short*的指针,指向电位器值的数组)
   /*Order:STICK_J1,_J2,_J3,_J4,_MOUSE_X ,MOUSE_Y,_FLP1,_FLP2,_FLP3,_SLIDER_LEFT,_SLIDER_RIGHT,_SP_RIGHT,_SP_LEFT,*/
    short* potentiometerGetValue(unsigned short *analog_raw_len);
//ashnag 2015.11.3
    short* potentiometerGetValueCali(unsigned short *analog_raw_len);

    //获取油门摇杆在ADC数组中的index
    unsigned short GetThrIndex(void);

    //输出当前的飞行模式，以便于获得当前trim的值
    char CurrentFlightModeGetValue(void);
    
    //Switch值的获取(输入switch_array_len的地址，获取的是Switch的长度;输出的char*的指针,指向Switch值的数组)
    char* SwitchGetValue(unsigned short *switch_array_len);
    
    //获取SD卡状态的函数
    SD_File_STATUS diskStatusGet(void);
    
    //ModelFile的新建(返回值:1，表示船舰的模型是默认的模型(错误的新建模型结果)！要提示用户！)
    //返回值2:代表船舰的模型版本号有问题，提示用户更换最新的config文件
    //返回0:正常
    int modelfileCreateFile(ModelFile *pStTmpModelFile, unsigned short nLen, CREATE_MODEL* cModelInfo);
    
    //ModelFile指针的获取，可以针对指针修改相应的信息
    ModelFile* modelfileCurrentGet(void);
    
	//modelFile的文件获取
    ModelFile* modelfileRename(char modelfile_Id);
    
    //ModelFile修改之后的保存到SD卡
    int modelfileModify(ModelFile* cur_model_file);
    
    //ModelFile Select Change
    int modelfileChangeSelect(char cModelType, char *cur_model_file_name, unsigned short nLen);
    //保存当前的模型文件
    void saveCurModelFiles(void);
    //重新选择模型后，模式是否正确(返回0，表示真确； 返回1， 表示模型校验错误；返回2：表示模型版本不一致,返回0xFF:表示模型没有切换)
    unsigned char IsModelSwitchCorrect(void);

    //如果上面函数的模型返回正确，显示判断油门和开关的界面，就打开mixer的功能；
	void SwitchOnMixer(void);

    //TransmitterFile的获取
    TransmitterFile* transmitterfileCurrentGet(void);
    
    //TransmitterFile修改之后的保存到SD卡
    int transmitterfileModify(TransmitterFile* cur_transmitter_file);
    
    //输出抹一个文件目录下的所有文件名
    pFilePointer getPathFileNames(char* path);

    //system time set function
    typedef struct __SYSTEM_TIME
    {
        unsigned char tm_sec;   /*Seconds. [0-60] (1 leap second)*/
        unsigned char tm_min;   /*Minutes. [0-59]*/
        unsigned char tm_hour;  /*Hours.   [0-23]*/
        unsigned char tm_mday;  /*Day.     [1-31]*/
        unsigned char tm_mon;   /*Month.   [0-11]*/
        unsigned char tm_year;  /* Year - 1900. Limited to the year 2115. Oh no! :P */
        unsigned char tm_wday;  /* Day of week. [0-6] */
        unsigned char tm_yday;  /* Day of year. [0-365] Needed internally for calculations */
    }SYSTEM_TIME;
    
    //获取系统时间
    SYSTEM_TIME systemTimeGet(void);
    
    //设置系统时间
    void systemTimeSet(const SYSTEM_TIME* pTime);
    
    //获取输出通道的值
    short* getOutChannelValue(unsigned short *channelNum);

    //遥感数据的获取
    sensorData* sensorDataGet(void);

    //播放声音文件的接口
    void PlayWavFiles(int type, char *filename, int volume);

    //----------------------------------------------
    //定时器的获取//tim:0 or 1
    TimerState *getTimerState(int tim);

    //获取trim的接口
    TrimIncData* getTrimValue(void);

    //获取ModelFile的存储路径(参数1：文件名，参数2：模型类型；)
    void GetModelStorePath(char *filename, unsigned char modelFirstCate);

    //获取关机事件
    unsigned char GetShutdownEvent(void);

    //获取USB Plug事件
    unsigned char GetPlugUSBEvent(void);

    //获取TRAINER插入事件
    unsigned char GetPlugTrainerEvent(void);

    //发送关机命令
    unsigned char GetShutdownCmd(void);

    //get mixStatu
    unsigned char GetMixStopEvent(void);
	GPSData* GetGpsData();

	
	void setTrainMode(int d);
	
	int getTrainMode();
	
	short*	potentiometerGetMinMax(short unsigned int* len);
	
	void GetGyroValue(short* pbuf);
	
	short* imuGetValue(unsigned short *len);

    void clrXPortChangeFlg();
	
	int getXPortChange();//0--no change    others--x-1 pot num

	
	void setServoTestFlag(int flag);   //0--no test other --test 
	int getServoTestFlag();

	
	uint8_t getThrCutFlag();
	uint8_t getThrHoleFlag();	
	void timers_reset(unsigned char timerId);
	
	unsigned char GetLogicSwitch(unsigned char num);
#ifdef __cplusplus
}
#endif

#endif
