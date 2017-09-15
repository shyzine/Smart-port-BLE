/*
 *
 * */
#include "system_file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version.h"

#include "main.h"

#include "task_system.h"
#include "task_telemetry.h"

void setDefaultTransmitterFile(void)
{
    int i;
    //char sTmp[10] = {0};
    
    TransmitterFile &transmitterFile = *getTransmitterFile();

	
    
    memset(&transmitterFile, 0, sizeof(transmitterFile));
			/// stick mode
#if defined(STKMODE1)
			transmitterFile.stickMode = 0;
#endif
#if defined(STKMODE2)
			transmitterFile.stickMode = 1;
#endif
#if defined(STKMODE3)
			transmitterFile.stickMode = 2;
#endif
#if defined(STKMODE4)
			transmitterFile.stickMode = 3;
#endif

	
    /// version
    memcpy(transmitterFile.HardwareVersion, HARDWARE_VERSION, sizeof(HARDWARE_VERSION));
    if(myglob.version)
    {
       strcat((char*)transmitterFile.HardwareVersion,(char*)"14");
    }
    else
    {
        strcat((char*)transmitterFile.HardwareVersion,(char*)"12");
    }
//    memcpy(transmitterFile.SoftwareVersion, SOFTWARE_VERSION, strlen(SOFTWARE_VERSION));
	sprintf((char *)transmitterFile.SoftwareVersion,"%d.%d",MAJOR_VERSION,MINOR_VERSION);
    
    //Add cur mode
    strcpy((char*)transmitterFile.currModelName, DEFAULT_MODEL_NAME);

    /// ownername
    memcpy(transmitterFile.ownerName,"HORUS",6);
    
    /// password
    memset(transmitterFile.ownerPwd , ' ', sizeof(transmitterFile.ownerPwd));
    transmitterFile.ownerPwd[LEN_USER_NAME-1] = 0;
    
    /// time
    transmitterFile.dateShowType = 0;
    transmitterFile.timezone = 0;
    transmitterFile.TotSeconds = 0;
    
    //sound
    transmitterFile.beepMode = 3;

	transmitterFile.silentAll= 0;
    transmitterFile.alarmVolume = 1;
    transmitterFile.keyVolume= 1;
	transmitterFile.trimVolume = 1;
//	transmitterFile.mp3Volume = 1;
    transmitterFile.AllVolume = 50;
    transmitterFile.alarmVolumePot = 0xff;
    transmitterFile.keyVolumnPot = 0xff;
    transmitterFile.trimVolumnPot = 0xff;
    transmitterFile.mp3VolumnPot = 0xff;
	transmitterFile.keyVibsEnable=1;
    transmitterFile.alarmVibsEnable=1;	
	transmitterFile.trimVibsEnable=1;
    transmitterFile.hapticStrength = 3;
    transmitterFile.mp3Volume = 60;
    
    //backlight
    transmitterFile.backlightModeChanged = 0;
    transmitterFile.backlightMode = 0;
    transmitterFile.backlightValueChanged = 0;
    transmitterFile.backlightValue = 100;
    transmitterFile.backlightDurationChanged = 0;
    transmitterFile.backlightDuration = 0;
    transmitterFile.backlightPot = 0xff;

    //locked
    transmitterFile.locked = 0;

    //battery
    transmitterFile.vBatWarnChanged = 0;
    transmitterFile.vBatWarn = 92;
    transmitterFile.vBatCalib = 0;
    transmitterFile.vBatMin = 88;
    transmitterFile.vBatMax = 112;
    transmitterFile.vBatRatio = 100;
    
    /// cali
    for(i=0; i<NUM_POT; i++)
    {
        transmitterFile.caliData[i].maxValue=4095;
        transmitterFile.caliData[i].minValue=0;
        transmitterFile.caliData[i].midValue=2048;
    }
    


#if 0
    /// virtual source
    for(i=0; i<NUM_VSW; i++)
    {
        set_vsw_const(i,0);
    }
    
    set_vsw_sw(0, 0, BOOLEAN_NOT, 1,0); /// !sw[0]
    set_vsw_sw(1, 0, BOOLEAN_OR, 1,3); /// sw[0] || sw[3]
    set_vsw_sw(2, 0, BOOLEAN_AND, 1,3); /// sw[0] && sw[3]
    set_vsw_vsw(3, 0, BOOLEAN_AND, 1,3); /// vsw[0] && sw[3]
    set_vsw_pot(4, 0, 0); /// pot[0]: only gate from pot to vsw
    set_vsw_vpot(5, 6, 0); /// vpot[6]: only gate from vpot to vsw
    
    for(i=0; i<NUM_VPOT; i++)
    {
        set_vpot_const(i, 0);
    }
    
    set_vpot_sw(0, 0, 1024, SRC_TYPE_POT, 0); /// sw[0]: 1024; pot[0]
    set_vpot_vsw(1,0,1024, SRC_TYPE_POT,1); /// vsw[0]: 1024, pot[1]
    set_vpot_pot(2, 0, CURVE_TYPE_LINE,1); /// pot[0], line, 'V'
    set_vpot_pot(3, 0, CURVE_TYPE_SMOOTH,1);
    
    /// create a VPot to output sw0 - sw8
    set_vpot_sw(4, 0, -2048, SRC_TYPE_VPOT, 5);
    set_vpot_sw(5, 1, -1536, SRC_TYPE_VPOT, 6);
    set_vpot_sw(6, 3, -1024, SRC_TYPE_VPOT, 7);
    set_vpot_sw(7, 4, -512, SRC_TYPE_VPOT, 8);
    set_vpot_sw(8, 6, 0, SRC_TYPE_VPOT, 9);
    set_vpot_sw(9, 7, 512, SRC_TYPE_VPOT, 10);
    set_vpot_sw(10, 9, 1024, SRC_TYPE_VPOT, 11);
    set_vpot_sw(11, 10, 1536, SRC_TYPE_VPOT, 12);
    set_vpot_const(12, 2047);
#endif
}

void setDefaultModelFile(ModelFile *pStTmpModelFile)
{
    ///> it will be replaced
    pStTmpModelFile->mapCh[0].channelEnable = 1;
    pStTmpModelFile->mapCh[1].channelEnable = 1;
    pStTmpModelFile->mapCh[2].channelEnable = 1;
    pStTmpModelFile->mapCh[3].channelEnable = 1;
    pStTmpModelFile->mapCh[4].channelEnable = 1;
    pStTmpModelFile->mapCh[5].channelEnable = 1;

    Mixer tmp;
    tmp.valid = 1;
    tmp.src.type =SRC_TYPE_POT;
    tmp.src.id =0;
    tmp.mltplxMode =MULTIPLEX_MODE_ADD;
    tmp.sw.type = SRC_TYPE_SW_CONST;    //test
    tmp.sw.id = 1;                        //sw is alwayls true
    tmp.activePhaseMap =FLIGHT_PHASE_ALL;
    tmp.isCarryTrim = 1;

    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_activeMap = FLIGHT_PHASE_ALL;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 50;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 50;

    tmp.curveDt[NUM_CURVES_WEIGHT-1].curve_activeMap = FLIGHT_PHASE_ALL;
    tmp.curveDt[NUM_CURVES_WEIGHT-1].curveNumber = 0;

    tmp.offsetDt[NUM_CURVES_WEIGHT-1].offset_activeMap = FLIGHT_PHASE_ALL;
    tmp.offsetDt[NUM_CURVES_WEIGHT-1].offset1 = 0;

    //Ail
    tmp.src.id = 0;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 100;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 100;
    set_mixer_slot(pStTmpModelFile, 0, 1, &tmp);

    //Ele
    tmp.src.id = 1;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 100;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 100;
    set_mixer_slot(pStTmpModelFile, 1, 2, &tmp);

    //thr
    tmp.src.id = 2;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 100;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 100;
    set_mixer_slot(pStTmpModelFile, 2, 3, &tmp);

    //rud
    tmp.src.id = 3;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 100;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 100;
    set_mixer_slot(pStTmpModelFile, 3, 4, &tmp);

    //FLP1
    tmp.src.id = 11;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 100;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 100;
    set_mixer_slot(pStTmpModelFile, 4, 8, &tmp);

    //FLP2
    tmp.src.id = 12;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_left = 100;
    tmp.weight_Dt[NUM_CURVES_WEIGHT-1].weight_right = 100;
    set_mixer_slot(pStTmpModelFile, 5, 9, &tmp);
}

/* Init Slot */
static void InitSlotState(Slot_State *pSlotStateList)
{
    pSlotStateList->cur_index = 4;
    pSlotStateList->UsedNum = 4;

    pSlotStateList->slotState[0] = 1;
    pSlotStateList->slotState[1] = 1;
    pSlotStateList->slotState[2] = 1;
    pSlotStateList->slotState[3] = 1;
}

void ResetModelFile(ModelFile *pStTmpModelFile, char* model_file_name, unsigned int nLen)
{
    unsigned int i;
	TransmitterFile &transmitterFile = *getTransmitterFile();

    memset(pStTmpModelFile, 0,sizeof(*pStTmpModelFile));

    //create new model file version
    pStTmpModelFile->ModelVersion = (MAJOR_VERSION<<16 | MINOR_VERSION<<8 | REVISION_NUMBER);//MODEL_VERSION;

    //model name
    memcpy(pStTmpModelFile->name, model_file_name, nLen);

    /*----------------------------------TRAINER INIT-------------------------------------*/
    pStTmpModelFile->trainerMode = 0;    //master
//ashang 2015.12.16
    pStTmpModelFile->trainerType = 0;    //cable
    //ch1
    pStTmpModelFile->trainerMasterCh[0].mode = 1;
    pStTmpModelFile->trainerMasterCh[0].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[0].function_channel = 0;
    //ch2
    pStTmpModelFile->trainerMasterCh[1].mode = 1;
    pStTmpModelFile->trainerMasterCh[1].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[1].function_channel = 1;
    //ch3
    pStTmpModelFile->trainerMasterCh[2].mode = 1;
    pStTmpModelFile->trainerMasterCh[2].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[2].function_channel = 2;
    //ch4
    pStTmpModelFile->trainerMasterCh[3].mode = 1;
    pStTmpModelFile->trainerMasterCh[3].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[3].function_channel = 3;
    //ch5
    pStTmpModelFile->trainerMasterCh[4].mode = 1;
    pStTmpModelFile->trainerMasterCh[4].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[4].function_channel = 4;
    //ch6
    pStTmpModelFile->trainerMasterCh[5].mode = 1;
    pStTmpModelFile->trainerMasterCh[5].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[5].function_channel = 5;
    //ch7
    pStTmpModelFile->trainerMasterCh[6].mode = 1;
    pStTmpModelFile->trainerMasterCh[6].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[6].function_channel = 6;
    //ch8
    pStTmpModelFile->trainerMasterCh[7].mode = 1;
    pStTmpModelFile->trainerMasterCh[7].stu_weight = 50;
    pStTmpModelFile->trainerMasterCh[7].function_channel = 7;

    pStTmpModelFile->sw_trainer.type = SRC_TYPE_SW;
    pStTmpModelFile->sw_trainer.id = SWH_D;
    /*----------------------------------end TRAINER INIT-------------------------------------*/


    //set thr default safe pos
    pStTmpModelFile->nThrSafePos = -1600;
    //set sw default safe pos
    memcpy(pStTmpModelFile->nSwitchSafePos, sw_default_pos, sizeof(sw_default_pos));

    /*----------------------------------rf system INIT-------------------------------------*/

    pStTmpModelFile->moduleData[1].state = 0;
    pStTmpModelFile->moduleData[1].rfprotocol = 0;///< D16
    pStTmpModelFile->moduleData[1].channelsStart = 16;//start from 0
    pStTmpModelFile->moduleData[1].channelsEnd = 31;//start from 0
    if(transmitterFile.rxNumber >= 64)transmitterFile.rxNumber = 0;
        pStTmpModelFile->moduleData[1].rxNumber = ++transmitterFile.rxNumber;//1;

    //default status is closed; RF protocol is pxx:D16
    pStTmpModelFile->moduleData[0].state = 0;///< off
    pStTmpModelFile->moduleData[0].rfprotocol = 0;///< D16
    pStTmpModelFile->moduleData[0].channelsStart = 0;//start from 0
    pStTmpModelFile->moduleData[0].channelsEnd = 15;//start from 0
    pStTmpModelFile->moduleData[0].rxNumber = transmitterFile.rxNumber;//2;///< rx no
	
    /*----------------------------------end rf system INIT-------------------------------------*/


    /*----------------------------------TRIM STEP INIT-------------------------------------*/
    pStTmpModelFile->trimSet.SteptrimArray[0] = 2;
    pStTmpModelFile->trimSet.SteptrimArray[1] = 2;
    pStTmpModelFile->trimSet.SteptrimArray[2] = 2;
    pStTmpModelFile->trimSet.SteptrimArray[3] = 2;
    pStTmpModelFile->trimSet.SteptrimArray[4] = 2;
    pStTmpModelFile->trimSet.SteptrimArray[5] = 2;
    pStTmpModelFile->trimSet.InctrimMode = 0;
    /*----------------------------------end TRIM STEP INIT-------------------------------------*/

    pStTmpModelFile->phaseData[0].fadeIn = 0;
    pStTmpModelFile->phaseData[1].fadeIn = 0;
    pStTmpModelFile->phaseData[2].fadeIn = 0;
    pStTmpModelFile->phaseData[3].fadeIn = 0;
    pStTmpModelFile->phaseData[4].fadeIn = 0;
    pStTmpModelFile->phaseData[5].fadeIn = 0;
    pStTmpModelFile->phaseData[6].fadeIn = 0;
    pStTmpModelFile->phaseData[7].fadeIn = 0;
    pStTmpModelFile->phaseData[8].fadeIn = 0;       //it is time, 50:50/10(s),

    pStTmpModelFile->DefaultCurveData.type = CURVE_TYPE_EXPO;
    pStTmpModelFile->DefaultCurveData.points[0]=-99;
    pStTmpModelFile->DefaultCurveData.points[1]=-66;
    pStTmpModelFile->DefaultCurveData.points[2]=-33;
    pStTmpModelFile->DefaultCurveData.points[3]=0;
    pStTmpModelFile->DefaultCurveData.points[4]= 33;
    pStTmpModelFile->DefaultCurveData.points[5]= 66;
    pStTmpModelFile->DefaultCurveData.points[6]= 99;
	pStTmpModelFile->DefaultCurveData.k=0;
	pStTmpModelFile->DefaultCurveData.e_weigth=100;
    pStTmpModelFile->DefaultCurveData.e_offset=0;

    for (i=0; i<NUM_ALL_CURVES; ++i)
    {
        pStTmpModelFile->AllcurveData[i].type = CURVE_TYPE_EXPO;
        memset(pStTmpModelFile->AllcurveData[i].name, 0, 10);
        sprintf(pStTmpModelFile->AllcurveData[i].name, "Curve %d", i);
        pStTmpModelFile->AllcurveData[i].points[0]=-99;
        pStTmpModelFile->AllcurveData[i].points[1]=-66;
        pStTmpModelFile->AllcurveData[i].points[2]=-33;
        pStTmpModelFile->AllcurveData[i].points[3]=0;
        pStTmpModelFile->AllcurveData[i].points[4]= 33;
        pStTmpModelFile->AllcurveData[i].points[5]= 66;
        pStTmpModelFile->AllcurveData[i].points[6]= 99;
		pStTmpModelFile->AllcurveData[i].k = 0;
		pStTmpModelFile->AllcurveData[i].e_weigth=100;
		pStTmpModelFile->AllcurveData[i].e_offset = 0;
    }

    for (i=0; i<EXTRA_NUM_CURVES; ++i)
    {
        pStTmpModelFile->ExtraAllcurveData[i].type = CURVE_TYPE_EXPO;
        memset(pStTmpModelFile->ExtraAllcurveData[i].name, 0, 10);
        sprintf(pStTmpModelFile->ExtraAllcurveData[i].name, "Curve %d", i);
        pStTmpModelFile->ExtraAllcurveData[i].points[0]=-99;
        pStTmpModelFile->ExtraAllcurveData[i].points[1]=-66;
        pStTmpModelFile->ExtraAllcurveData[i].points[2]=-33;
        pStTmpModelFile->ExtraAllcurveData[i].points[3]=0;
        pStTmpModelFile->ExtraAllcurveData[i].points[4]= 33;
        pStTmpModelFile->ExtraAllcurveData[i].points[5]= 66;
        pStTmpModelFile->ExtraAllcurveData[i].points[6]= 99;
		pStTmpModelFile->ExtraAllcurveData[i].k = 0;
		pStTmpModelFile->ExtraAllcurveData[i].e_weigth=100;
		pStTmpModelFile->ExtraAllcurveData[i].e_offset = 0;
    }


    ///servo calibration
    for(i=0; i<NUM_VIRTUAL_CHANNEL; ++i)
    {
        ServoData &servo = pStTmpModelFile->servoData[i];

        servo.endPoint_max = 100;
        servo.endPoint_min = -100;
		servo.endPoint_lmtmax=110;
		servo.endPoint_lmtmin=-110;
        servo.reverseFlag = 0;
        servo.subTrim = 0;
        //servo.fadeSpeedTim = 50;    //it is time, 50:50/10(s),
        servo.fadeSpeedTim = 0;    //it is time, 50:50/10(s),
    }


    /*--------------------------PHYSICAL MAP(INPUT MAP) INIT-----------------------*/
    pStTmpModelFile->stPhyMap.stPortMap[0].nPortFunctionID = 0;
    pStTmpModelFile->stPhyMap.stPortMap[0].nPortPhysisID = 0;
    pStTmpModelFile->stPhyMap.stPortMap[1].nPortFunctionID = 1;
    pStTmpModelFile->stPhyMap.stPortMap[1].nPortPhysisID = 1;
    pStTmpModelFile->stPhyMap.stPortMap[2].nPortFunctionID = 2;
    pStTmpModelFile->stPhyMap.stPortMap[2].nPortPhysisID = 2;
    pStTmpModelFile->stPhyMap.stPortMap[3].nPortFunctionID = 3;
    pStTmpModelFile->stPhyMap.stPortMap[3].nPortPhysisID = 3;
    pStTmpModelFile->stPhyMap.stPortMap[4].nPortFunctionID = 7;
    pStTmpModelFile->stPhyMap.stPortMap[4].nPortPhysisID = 11;
    pStTmpModelFile->stPhyMap.stPortMap[5].nPortFunctionID = 11;
    pStTmpModelFile->stPhyMap.stPortMap[5].nPortPhysisID = 12;
    pStTmpModelFile->stPhyMap.stPortMap[6].nPortFunctionID = 13;
    pStTmpModelFile->stPhyMap.stPortMap[6].nPortPhysisID = 2;
    pStTmpModelFile->stPhyMap.stPortMap[7].nPortFunctionID = 14;
    pStTmpModelFile->stPhyMap.stPortMap[7].nPortPhysisID = 10;
    pStTmpModelFile->stPhyMap.stPortMap[8].nPortFunctionID = 15;
    pStTmpModelFile->stPhyMap.stPortMap[8].nPortPhysisID = 100;

    for (i = 9; i < 25; ++i)
    {
        pStTmpModelFile->stPhyMap.stPortMap[i].nPortFunctionID = i;
        pStTmpModelFile->stPhyMap.stPortMap[i].nPortPhysisID = 0;
    }

    for (i = 25; i < NUM_PORT_MAP; ++i)
    {
        pStTmpModelFile->stPhyMap.stPortMap[i].nPortFunctionID = 0;
        pStTmpModelFile->stPhyMap.stPortMap[i].nPortPhysisID = 0;
    }
    /*--------------------------END PHYSICAL MAP(INPUT MAP) INIT-----------------------*/



    for(i=0; i<NUM_CHANNEL_MAP; ++i)
    {
        pStTmpModelFile->stChannelToFunction[i].nChannelID = i;
        //need modify
        pStTmpModelFile->stChannelToFunction[i].nActualFunctionID = i;
    }

    //init slot for  custom
    InitSlotState(&(pStTmpModelFile->slotStateList));

    //init telemetry
    pStTmpModelFile->teleUserData.loginterval = 1;
    for(i = 0;i<NumOfDisplayParam;i++)
        pStTmpModelFile->teleUserData.disOrder[i] = i+1;

    for(i=0; i<sizeof(pStTmpModelFile->teleUserData.SensorParam)/sizeof(pStTmpModelFile->teleUserData.SensorParam[0]); i++)
    {
    	strcpy(pStTmpModelFile->teleUserData.SensorParam[i].name, teleDataName[i]);
    }

    pStTmpModelFile->teleUserData.SensorParam[RPM].blade = 1;
    pStTmpModelFile->teleUserData.SensorParam[D8R_A1].ratio = 10;
    pStTmpModelFile->teleUserData.SensorParam[D8R_A2].ratio = 10;
    pStTmpModelFile->teleUserData.SensorParam[SP2UART_AD1].ratio = 10;
    pStTmpModelFile->teleUserData.SensorParam[SP2UART_AD2].ratio = 10;
    pStTmpModelFile->teleUserData.SensorParam[RX_BATTERY].ratio = 40;
	

	pStTmpModelFile->teleUserData.SensorParam[RECEIVER_SWR].maxAlarm =  51;
    pStTmpModelFile->teleUserData.SensorParam[RECEIVER_SWR].enableMaxAlarm=1;
	pStTmpModelFile->teleUserData.SensorParam[RECEIVER_RSSI].minAlarm = 43;
	pStTmpModelFile->teleUserData.SensorParam[RECEIVER_RSSI].enableMinAlarm= 1;

    //init sound
    //TODO:sound
    pStTmpModelFile->stTeleSoundData[0].cEnable = 0;
    pStTmpModelFile->stTeleSoundData[0].nCalculateType = 3;
    pStTmpModelFile->stTeleSoundData[0].cHapticEnable = 1;

    pStTmpModelFile->stSpecialFuncDat[0].cEnable = 0;
    pStTmpModelFile->stSpecialFuncDat[0].swSpecialFunction.type = SRC_TYPE_SW_CONST;
    pStTmpModelFile->stSpecialFuncDat[0].swSpecialFunction.id = 1;
    pStTmpModelFile->stSpecialFuncDat[0].cRunShellType = 0;

    //extra mixer init
    memset(pStTmpModelFile->ExtraMixerSlot, 0, sizeof(pStTmpModelFile->ExtraMixerSlot));
    for (int i = 0; i < NUM_CHANNEL; ++i)
    {
        pStTmpModelFile->ExtraMixerHead[i] = 0;
    }
    for (int i = 0; i < NUM_EXTRA_MIXER; ++i)
    {
        Mixer* tmpMixerSlot;
        tmpMixerSlot = &pStTmpModelFile->ExtraMixerSlot[i];

        tmpMixerSlot->valid = 0;
        tmpMixerSlot->src.id = 0;
        tmpMixerSlot->src.type = SRC_TYPE_POT;
        tmpMixerSlot->sw.id = 1;
        tmpMixerSlot->sw.type = SRC_TYPE_SW_CONST;
        tmpMixerSlot->mltplxMode = 0;
        tmpMixerSlot->activePhaseMap = 1;
        tmpMixerSlot->next = 0;

        tmpMixerSlot->weight_Dt[0].weight_left = 100;
        tmpMixerSlot->weight_Dt[0].weight_right = 100;
        tmpMixerSlot->weight_Dt[0].weight_activeMap = 1;
        tmpMixerSlot->weight_Dt[0].sw_weight.id = 0;
        tmpMixerSlot->weight_Dt[0].sw_weight.type = SRC_TYPE_SW_CONST;

        tmpMixerSlot->offsetDt[0].offset1 = 0;
        tmpMixerSlot->offsetDt[0].offset_activeMap = 1;
        tmpMixerSlot->offsetDt[0].sw_offset.id = 0;
        tmpMixerSlot->offsetDt[0].sw_offset.type = SRC_TYPE_SW_CONST;

        tmpMixerSlot->curveDt[0].curveNumber = 0;
        tmpMixerSlot->curveDt[0].curve_activeMap = 1;
        tmpMixerSlot->curveDt[0].sw_curve.id = 0;
        tmpMixerSlot->curveDt[0].sw_curve.type = SRC_TYPE_SW_CONST;

        for (int i = 1; i < NUM_CURVES_WEIGHT; ++i)
        {
            tmpMixerSlot->weight_Dt[i].weight_left = 0;
            tmpMixerSlot->weight_Dt[i].weight_right = 0;
            tmpMixerSlot->weight_Dt[i].weight_activeMap = 0;
            tmpMixerSlot->weight_Dt[i].sw_weight.id = 0;
            tmpMixerSlot->weight_Dt[i].sw_weight.type = SRC_TYPE_SW_CONST;

            tmpMixerSlot->offsetDt[i].offset1 = 0;
            tmpMixerSlot->offsetDt[i].offset_activeMap = 0;
            tmpMixerSlot->offsetDt[i].sw_offset.id = 0;
            tmpMixerSlot->offsetDt[i].sw_offset.type = SRC_TYPE_SW_CONST;

            tmpMixerSlot->curveDt[i].curveNumber = 0;
            tmpMixerSlot->curveDt[i].curve_activeMap = 0;
            tmpMixerSlot->curveDt[i].sw_curve.id = 0;
            tmpMixerSlot->curveDt[i].sw_curve.type = SRC_TYPE_SW_CONST;
        }
    }

}

void SelectConfigFile(char* model_file_name, unsigned short model_num)
{
    switch (model_num)
    {
    case MODEL_AIRPLANE_NORMAL:
        strcat(model_file_name, "Airplane");
        break;
    case MODEL_AIRPLANE_FLYING_WING:
        strcat(model_file_name, "flying-wing");
        break;
    case MODEL_AIRPLANE_V_TAIL:
        strcat(model_file_name, "Airplane-V-tail");
        break;
    case MODEL_HELICOPTER_H_1:
        strcat(model_file_name, "H-1");
        break;
    case MODEL_HELICOPTER_H_4:
        strcat(model_file_name, "H-4");
        break;
    case MODEL_HELICOPTER_HE3:
        strcat(model_file_name, "HE3");
        break;
    case MODEL_HELICOPTER_H_3:
        strcat(model_file_name, "H-3");
        break;
    case MODEL_HELICOPTER_HR3:
        strcat(model_file_name, "HR3");
        break;
    case MODEL_HELICOPTER_H_4X:
        strcat(model_file_name, "H-4X");
        break;
    case MODEL_GLIDER_NORMAL:
        strcat(model_file_name, "Glider");
        break;
    case MODEL_GLIDER_V_TAIL:
        strcat(model_file_name, "Glider-V-tail");
        break;
    case MODEL_MULTICOPTER:
        strcat(model_file_name, "multicopter");
        break;
    case MODEL_CUSTOM:
        strcat(model_file_name, "custom");
        break;
    default:
        strcat(model_file_name, "Airplane");
        break;
    }
}

void SetPhaseName(ModelFile *pStTmpModelFile)
{
    char buff[3] =
    { 0 };
    unsigned char i = 0;
    /// set all flight phase to valid
    switch (pStTmpModelFile->stModelType.model_type / 10)
    {
    case 0:          //airplane
        for (i = 0; i < NUM_PHASE; i++)
        {
            if (i == 0)
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 1);
                strcpy(pStTmpModelFile->phaseData[i].name, "NORMAL");
            }
            else
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strncpy(pStTmpModelFile->phaseData[i].name, "F.MODE", 6);
                sprintf(buff, "%d", (i + 1));
                strncat(pStTmpModelFile->phaseData[i].name, buff, 1);
            }
        }
        break;
    case 1:          //helicoptor
        for (i = 0; i < NUM_PHASE; i++)
        {
            if (i == 0)
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 1);
                strcpy(pStTmpModelFile->phaseData[i].name, "NORMAL");
            }
            else if (i < 4)
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strncpy(pStTmpModelFile->phaseData[i].name, "IDLE", 4);
                sprintf(buff, "%d", i);
                strncat(pStTmpModelFile->phaseData[i].name, buff, 1);
            }
            else if (i == 4)
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strcpy(pStTmpModelFile->phaseData[i].name, "HOLD");
            }
            else
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strncpy(pStTmpModelFile->phaseData[i].name, "F.MODE", 6);
                sprintf(buff, "%d", (i + 1));
                strncat(pStTmpModelFile->phaseData[i].name, buff, 1);
            }
        }
        break;
    case 2:          //glider
        for (i = 0; i < NUM_PHASE; i++)
        {
            switch (i)
            {
            case 0:
                //default start
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 1);
                strcpy(pStTmpModelFile->phaseData[i].name, "LAUNCH");
                break;
            case 1:
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strcpy(pStTmpModelFile->phaseData[i].name, "SPEED");
                break;
            case 2:
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strcpy(pStTmpModelFile->phaseData[i].name, "CRUISE");
                break;
            case 3:
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strcpy(pStTmpModelFile->phaseData[i].name, "THERMAL");
                break;
            case 4:
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strcpy(pStTmpModelFile->phaseData[i].name, "LANDING");
                break;
            default:
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strncpy(pStTmpModelFile->phaseData[i].name, "F.MODE", 6);
                sprintf(buff, "%d", (i + 1));
                strncat(pStTmpModelFile->phaseData[i].name, buff, 1);
                break;

            }
        }
        break;
    case 3:          //muticopter
        for (i = 0; i < NUM_PHASE; i++)
        {
            if (i == 0)
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 1);
                strcpy(pStTmpModelFile->phaseData[i].name, "NORMAL");
            }
            else
            {
                set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
                strncpy(pStTmpModelFile->phaseData[i].name, "F.MODE", 6);
                sprintf(buff, "%d", (i + 1));
                strncat(pStTmpModelFile->phaseData[i].name, buff, 1);
            }
        }
        break;
    case 4:          //custom
        for (i = 0; i < NUM_PHASE; i++)
        {
            set_phase(pStTmpModelFile, i, SRC_TYPE_SW_CONST, 0);
            if (0 == i)
            {
                strcpy(pStTmpModelFile->phaseData[i].name, "NORMAL");
            }
            else
            {
                strncpy(pStTmpModelFile->phaseData[i].name, "F.MODE", 6);
                sprintf(buff, "%d", (i + 1));
                strncat(pStTmpModelFile->phaseData[i].name, buff, 1);
            }
        }
        break;
    default:
        break;
    }
}

void SelectModelStorePath(char *filename, unsigned char nModelType)
{
    switch( nModelType )
    {
    case 0:
        strcat(filename, MODEL_AIRPLANE_PATH);
        break;
    case 1:
        strcat(filename, MODEL_HELICOPTER_PATH);
        break;
    case 2:
        strcat(filename, MODEL_GLIDER_PATH);
        break;
    case 3:
        strcat(filename, MODEL_MULTICOPTER_PATH);
        break;
    case 4:
        strcat(filename, MODEL_CUSTOM_PATH);
        break;
    default:
        strcat(filename, MODEL_AIRPLANE_PATH);
        break;
    }
}
