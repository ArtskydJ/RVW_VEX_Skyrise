#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S2,     COMPASS,        sensorVirtualCompass)
#pragma config(Sensor, S3,     LIGHT,          sensorLightActive)
#pragma config(Sensor, S4,     ULTRA,          sensorSONAR)
#pragma config(Motor,  mtr_S1_C1_1,     DRIVE_FR,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     DRIVE_FL,      tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     DRIVE_BR,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     DRIVE_BL,      tmotorTetrix, openLoop, reversed, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     LIFT_R,        tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     LIFT_L,        tmotorTetrix, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "FTC_Definitions.c"
#define   PRACTICE // If not defined, then competition mode
#include "FTC_Declarations.c"
#include "FTC_OtherFunctions.c"
#include "FTC_Initialize.c"
#include "FTC_InputAndOutput.c"
#include "FTC_Autonomous.c"

/*
By Joseph Dykstra
For the CS2N FTC Ring It Up! Challenge
2013-06-27 - 2013-08-??

Instructions:
Robot:	Gyro ScissorBot
Mode:	CS2N Mode
Start:	Start Point 1

HKEY_CLASSES_ROOT\vdsp

Do not move the robot at all from it's starting position.
*/

task main()
	{
	initialize(N_EAST); //Which way does the robot start pointing?
	autoReset(START);

	//	TYPE,	Left,	Right,	Other,	End Type,	Delay
	auto(CMP_2,	350,	FULL,	LOW_SH,	DRIV_READY,	PID);	//Turn toward S dispenser
	auto(STR,	1700,	11600,	LOW_SH,	DRIV_READY,	NEXT);	//Forward
	auto(CMP_2,	-800,	FULL,	LOW_SH,	DRIV_READY,	PID);	//Turn to SE hooks
	auto(STR,	NORTH,	7200,	HIG_SH,	DRIV_READY,	NEXT);	//Forward - High
	auto(STR,	NORTH,	-7500,	MED_OP,	DRIV_READY,	NEXT);	//Backward
	auto(STR,	NORTH,	6800,	MED_SH,	DRIV_READY,	NEXT);	//Forward - Med
	auto(STR,	NORTH,	-7000,	LOW_OP,	DRIV_READY,	NEXT);	//Backward
	auto(STR,	NORTH,	6700,	LOW_SH,	DRIV_READY,	NEXT);	//Forward - Low
	auto(STR,	NORTH,	-8000,	LOW_OP,	DRIV_READY,	NEXT);	//Backward

	auto(CMP_2,	RHT_90,	FULL,	CRN_SH,	DRIV_READY,	PID);	//Turn toward corner hook
	auto(STR,	EAST,	8500,	CRN_SH,	DRIV_READY,	NEXT);	//Forward into corner hook
	auto(CMP_2,	LFT_90,	FULL,	DRP_OP,	DRIV_READY,	PID);	//Turn toward E dispenser

	auto(STR,	NORTH,	11600,	DRP_SH,	DRIV_READY,	NEXT);	//Forward - E dispenser to 4 tiles
	auto(CMP_2,	-100,	FULL,	DRP_OP,	DRIV_READY,	PID);	//Turn
	auto(STR,	800,	7000,	DRP_SH,	DRIV_READY,	NEXT);	//Forward -	1 Tile
	auto(STR,	800,	-9500,	DRP_OP,	DRIV_READY,	NEXT);	//Backward
	auto(CMP_2,	-175,	FULL,	DRP_SH,	DRIV_READY,	PID);	//Turn then drop
	auto(CMP_2,	-175,	FULL,	DRP_OP,	DRIV_READY,	PID);	//Keep turning ~45
	auto(STR,	N_WEST,	5000,	DRP_SH,	DRIV_READY,	NEXT);	//Forward -	3 Tile

	auto(CMP_2,	1800,	FULL,	DRP_SH,	DRIV_READY,	PID);	//Turn 180
	auto(STR,	S_EAST,	-9000,	DRP_SH,	DRIV_READY,	NEXT);	//Backward then drop
	auto(STR,	S_EAST,	-1350,	DRP_OP,	DRIV_READY,	NEXT);	//Backward
	auto(CMP_2,	RHT_45,	FULL,	DRP_SH,	DRIV_READY,	PID);	//Turn - Align

	auto(STR,	SOUTH,	-2000,	LOW_LV,	DRIV_READY,	NEXT);	//Backward - N dispenser to NW hooks
	auto(STR,	SOUTH,	8250,	HIG_SH,	DRIV_READY,	NEXT);	//Forward - High
	auto(STR,	SOUTH,	-7450,	HIG_OP,	DRIV_READY,	NEXT);	//Backward
	auto(STR,	SOUTH,	7200,	MED_SH,	DRIV_READY,	NEXT);	//Forward - Med
	auto(STR,	SOUTH,	-7200,	MED_OP,	DRIV_READY,	NEXT);	//Backward
	auto(STR,	SOUTH,	7000,	LOW_SH,	DRIV_READY,	NEXT);	//Forward - Low
	auto(STR,	SOUTH,	-8800,	LOW_OP,	DRIV_READY,	NEXT);	//Backward

	auto(CMP_2,	RHT_90,	FULL,	CRN_SH,	DRIV_READY,	PID);	//Turn toward corner hook
	auto(STR,	3600,	8750,	CRN_SH,	DRIV_READY,	NEXT);	//Forward into corner hook
	auto(CMP_2,	LFT_90,	FULL,	CRN_OP,	DRIV_READY,	NEXT);	//Turn toward W dispenser

	auto(STR,	SOUTH,	11600,	DRP_SH,	DRIV_READY,	NEXT);	//Forward - W dispenser to 4 tiles
	auto(CMP_2,	-100,	FULL,	DRP_OP,	DRIV_READY,	NEXT);	//Turn
	auto(STR,	2600,	6800,	DRP_SH,	DRIV_READY,	NEXT);	//Forward -	1 Tile
	auto(STR,	2600,	-6800,	DRP_OP,	DRIV_READY,	NEXT);	//Backward
	auto(CMP_2,	-300,	FULL,	DRP_SH,	DRIV_READY,	PID);	//Turn
	auto(CMP_2,	-150,	FULL,	DRP_OP,	DRIV_READY,	PID);	//Turn
	auto(STR,	2150,	4800,	DRP_SH,	DRIV_READY,	NEXT);	//Forward -	3 Tile
	auto(SPD,	1,		1,		DRP_OP,	TIME_LIMIT,	100);	//Backward

	autoReset(FINISH);

	while(1==1) {}
	}

/* BUGS...
LIFT_READY was not working correctly, triggered too soon; maybe working now.


still too far right 2nd pole

DO...
[test...]


DONE...

*/



/* --LINE 38--

	auto(CMP_2,	450,	FULL,	NEW_SH,	DRIV_READY,	PID);	//Turn to align with field
	auto(STR,	EAST,	9000,	NEW_SH,	DRIV_READY,	NEXT);	//Forward + Grab
	auto(STR,	EAST,	200,	NEW_OP,	DRIV_READY,	NEXT);	//Forward + Drop
	auto(STR,	EAST,	8000,	NEW_SH,	DRIV_READY,	NEXT);	//Forward + Grab
	auto(SPD,	0,		0,		NEW_SH,	TIME_LIMIT,	500);	//Stop
	auto(STR,	EAST,	-3000,	NEW_SH,	DRIV_READY,	NEXT);	//Reverse
*/