#ifndef __MIXER_CONFIG_H_
#define __MIXER_CONFIG_H_

#define BITMAP_PATH_LEN	 		50			///< bitmap Path
#define NUM_MODEL        		64          ///< number of model

#define LEN_USER_NAME 			10    		///< use name length
#define LEN_FP_NAME 			10        	///< flight phase name
#define LEN_CURVE_NAME          10          ///< flight phase name
#define LEN_MODEL_NAME 			30 			///< model name length
#define LEN_VCH_NAME    		10    		///< virtual channel name
#define LEN_MLTPLX_MODE 		5           ///< MLTPLX MODE

//define the RESX
#define RESX    2048
//define MAX_TRIM_VALUE
#define MAX_TRIM_VALUE    512
//define Step Kx
#define TRIM_VALUE_KX    RESX/MAX_TRIM_VALUE

#define SWA_U    0
#define SWA_M    1
#define SWA_D    2
#define SWB_U    3
#define SWB_M    4
#define SWB_D    5
#define SWC_U    6
#define SWC_M    7
#define SWC_D    8
#define SWD_U    9
#define SWD_M    10
#define SWD_D    11
#define SWE_U    12
#define SWE_M    13
#define SWE_D    14
#define SWF_U    15
#define SWF_D    16
#define SWG_U    17
#define SWG_M    18
#define SWG_D    19
#define SWH_U    20
#define SWH_D    21
//ashang add 2015.10.29 flp3 as switch
#define SWFLP_1  22
#define SWFLP_2  23
#define SWFLP_3  24
#define SWFLP_4  25
#define SWFLP_5  26
#define SWFLP_6  27
#define TOTAL_SW_POSITION 28

#define TRIM_POT_MASK   50
#define TRIM_POT_1   50
#define TRIM_POT_2   51
#define TRIM_POT_3   52
#define TRIM_POT_4   53
#define TRIM_POT_5   54
#define TRIM_POT_6   55

#define TIMER_POT_MASK   60
#define TIMER_POT_1   60
#define TIMER_POT_2   61



#define SWX_SW_MASK             100
#define SWA_SW                  100
#define SWB_SW                  101
#define SWC_SW                  102
#define SWD_SW                  103
#define SWE_SW                  104
#define SWF_SW                  105
#define SWG_SW                  106
#define SWH_SW                  107
#define SWFLP_SW                108

#define TELEMETRY_MASK       120

#define LOGIC_SW_MASK   200
#define LOGIC_SW_1          200
#define LOGIC_SW_2          201
#define LOGIC_SW_3          202
#define LOGIC_SW_4          203
#define LOGIC_SW_5          204
#define LOGIC_SW_6          205
#define LOGIC_SW_7          206
#define LOGIC_SW_8          207
#define LOGIC_SW_9          208
#define LOGIC_SW_10          209
#define LOGIC_SW_11          210
#define LOGIC_SW_12          211
#define LOGIC_SW_13          212
#define LOGIC_SW_14          213
#define LOGIC_SW_15          214
#define LOGIC_SW_16          215
#define LOGIC_SW_17          216
#define LOGIC_SW_18          217
#define LOGIC_SW_19          218
#define LOGIC_SW_20          219
#define LOGIC_SW_21          220
#define LOGIC_SW_22          221
#define LOGIC_SW_23          222
#define LOGIC_SW_24          223

//define for Sticks
#define STICK_J1            	0
#define STICK_J2            	1
#define STICK_J3            	2
#define STICK_J4            	3
#define STICK_MOUSE_X        	4
#define STICK_MOUSE_Y        	5
#define STICK_FLP1            	6
#define STICK_M_POS             7 //ashang 2015.10.29 8
#define STICK_FLP2            	8 //ashang 2015.10.29 7  
#define STICK_SLIDER_LEFT    	9
#define STICK_SLIDER_RIGHT    	10
#define STICK_SP_RIGHT          11
#define STICK_SP_LEFT        	12

#define STICK_GYRO_MASK        	30
#define STICK_GYRO_END        	40

#define STICK_GYRO_ROLL			30
#define STICK_GYRO_PITCH		31

/*****************mixer config************************/
#define NUM_POT 				14         	///< number of potentiometers:14
#define NUM_ACTUALLY_POT 		13         	///< number of actually potentiometers:13
#define NUM_EXT_POT 			2
#define NUM_TOTAL_POT           (NUM_ACTUALLY_POT + NUM_EXT_POT)

#define NUM_SWS            		8+1    //ashang 2015.10.29    	///<SWA.....SWH number   flp3
#define NUM_SW_POSITION   		TOTAL_SW_POSITION //ashang add 2015.10.29     22    		///< total positions for sw, for hours: 6*3 +2*2
#define NUM_LOGIC_SW        	16    		///< number of the logic switch
#define NUM_EXTRA_LOGIC_SW      8          ///< number of extra logic switch
#define NUM_TOTLE_LOGIC_SW      (NUM_LOGIC_SW+NUM_EXTRA_LOGIC_SW)
#define NUM_PHY_TRIMS    		6        	///< Number of phy trims
#define NUM_TRIMS         		12         	///< number of trims bool

#define FUNC_NAME_LEN      		10        	///<funtion name length
#define MAX_TIMERS         		2           ///< Max Timer Number

#define NUM_PHASE         		9           ///< number of light phase per model
#define FLIGHT_PHASE_ALL 		(0x1FF)  	///< ALL flight phase(B0-B9)
#define NUM_MIXER 				121 //120         ///< number of mixers per model
#define NUM_EXTRA_MIXER         11

#define NUM_ALL_CURVES			100  //ashang 2015.11.4 47          /// all curves number in model(default is zero)
#define EXTRA_NUM_CURVES        16
#define NUM_CURVES_WEIGHT  		9        	///<curve & weight numbers

#define NUM_VSW          		16          ///< number of virtual switches
#define NUM_VPOT         		16          ///< number of virtual potentiometers

#define NUM_CHANNEL     		32          ///< number of channels produced
#define NUM_VIRTUAL_CHANNEL     32    		///< actual channels

#define NUM_PORT_MAP    		32
#define NUM_CHANNEL_MAP    		32

#endif




