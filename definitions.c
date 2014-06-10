//Definitions.c
//2013-05-06

/*MOTORS
 Change motor names to memorable names.
*/
#define CLAW	motorA
#define WRIST	motorB

/*FLAGS
 These flags are meant to be overall system
toggles that are easily turned off and on.
*/
//#define SLEW
//#undef _TARGET				//This statement and the next go together. Uncomment both
//#define _TARGET "VirtWorld"	//If you want the emulator to act like a virtual worlds robot.

/*FUNCTIONS
 These function-like defines are for shortening
and simplifying the code.
 The ones that have INLC as an input are for
last/curr structs (declared below).
 There are some for autonomous values so that
different sensors can be used.
 There are also constants for these functions.
*/
#define checkTarget(cndtn,value)	(cndtn)?((value)>=INtarget):((value)<=INtarget)
#define capValue(Min,Value,Max)		Value = (Value<Min)? (Min):(Value); Value = (Value>Max)? (Max):(Value)
#define changed(INLC)				(INLC.last != INLC.curr)
#define pressed(INLC)				(!INLC.last && INLC.curr)
#define diffLast(INLC)				(INLC.curr - INLC.last)
#define diffStep(INLC)				(INLC.curr - INLC.stepStart)
#define setLast(INLC)				INLC.last = INLC.curr
#define setStep(INLC)				INLC.stepStart = INLC.curr
#define setToZero(INLC)				INLC.last=0; INLC.curr=0; INLC.stepStart=0
#define fixIrregularity(INLC,n)		slew(INLC.curr,INLC.last,n)
#define K_STRAFE					10000
#define enc(n)						((K_STRAFE*0)+n)
#define L_US(n)						((K_STRAFE*1)+n)
#define R_US(n)						((K_STRAFE*2)+n)

/*VALUES
 These values are stored here for easy modifica-
tion of system constants.
 NO means Number-Of.
*/
#define NO_AUTO_COLUMNS		6
#define NO_TIME_RECORDS		100

/*Time
 Minimum Loop time; scrolling text next
character; PID delay (for autonomous); LCD blink
time, slow and fast; LCD timeout (untouched).
*/
#define MIN_LOOP_MS			4
#define PID_WAIT_MS			0 //350
#define SHUT_CLAW_MS		1000

/*Preset Values
 Heights for lift, gyro, etc.
*/
#define START	0
#define FINISH	1

#define LOW_LV	1
#define LOW_OP	2
#define LOW_SH	3
#define MED_OP	4
#define MED_SH	5
#define HIG_OP	6
#define HIG_SH	7
#define CRN_OP	8
#define CRN_SH	9
#define DRP_OP	10
#define DRP_SH	11
#define NEW_OP	12
#define NEW_SH	13

#define L_HIGH	3000 //2940	100	3040
#define L_MED	2150 //2086	314	2400
#define L_LOW	1000 //867	493	1360
#define L_CRNR	1100 //1055	330	1485


#define C_SH	10
#define C_OP	-70

#define W_NEW	200
#define W_HI	150 //180
#define W_HI2	160
#define W_MED	130
#define W_LEV	90
#define W_DRP	55
#define W_LOW	0


#define LFT_90	-900	//Relative-v-
#define LFT_45	-450	//Relative |
#define RHT_45	450		//Relative |
#define RHT_90	900		//Relative-^-
#define WEST	0		//Absolute-v-
#define N_WEST	450		//Absolute |
#define NORTH	900		//Absolute |
#define N_EAST	1350	//Absolute |
#define EAST	1800	//Absolute |
#define S_EAST	2250	//Absolute |
#define SOUTH	2700	//Absolute |
#define S_WEST	3150	//Absolute-^-


/*Motor Speed Constants
 Shortcuts for autonomous writing.
*/
#define UP		 100
#define DOWN	-100
#define FWD		 100
#define REV		-100
#define LEFT	-100
#define RIGHT	 100
#define BOTH	 0
#define IN		 100
#define OUT		-100
#define FULL	 100
#define HALF	 50
#define FOLLOW	 100
#define TURN	 100
#define BRAKE	 5	//can also be used in -Action- column

/*Motor Slew Constants
 Values for how much to add to each motor value
each loop iteration.
*/
#define AUTO_DRV_SLEW	3
#define AUTO_LIFT_SLEW	8
#define AUTO_WRST_SLEW	12
#define AUTO_CLAW_SLEW	12

/*Robot States
 What state the robot is currently in...
*/
#define DISABLED	0
#define AUTONOMOUS	1


/*Hit Target
 These values are used in autonomous. If the end-
type is encoder, and the wheels have been driven
far enough, then the variable autoHitTarget is
set to NEXT. If the minimum time is higher than
the current time, it will not execute
autoNextStep() until it is.
 These values are also used as a trigger for a
delay to allow PID controllers to stablize before
the next step is executed.
*/
#define NOT_HIT	0
#define NEXT	1
#define PID		2

/*Line Following
 Edge, and line definitions
*/
#define LINE	50

/*Next Condition
 These are for if the minimum or maximum time are
used in autonomous. If one is used, then a debug
stream message is sent to the debugger. In this
way, one can easily see which steps always time-
out.
*/
#define SENSOR_HIT	0
#define MIN_TIMEOUT	1
#define MAX_TIMEOUT	2

/*Autonomous End and Drive types
 The Drive types are for how the robot drives.
For example:
1 Line Follow
2 Gyro Strafe
3 Normal Drive
 The End types are for what sensor triggers the
step to end.
For example:
1 Left Encoder
2 Absolute Left Ultrasonic
3 Lift Potentiometer
*/
// End Types
#define RESET_AUTO	0	// Autonomous Done (End/Start of array)
#define TIME_LIMIT	1	// Time Limit
#define DRIV_READY	2	// Finished using Drive
#define LIFT_READY	3	// Finished using Lift
#define FULL_READY	4	// Finished using Drive and Lift
#define FRONT_LINE	5	// Center Line sensor hits
// Drive Types
#define SPD		0	//Speed
#define ENC		1	//Encoder
#define STR		2	//Straight
#define CMP_2	3	//Compass turn - 2 Sides
#define CMP_L	4	//Compass turn - Left Side
#define CMP_R	5	//Compass turn - Right Side
#define FLINE	6	//Follow Line

/*Miscellaneous defined values
 The PID zone is so that small error values
owill not be ignored. This is so that the PID
controller can come close to the target, not
come to the exact value.
*/
#define PID_ZONE			25			//If the PID error is within this amount, it is close enough to its target

//--Typedefs--//
/*Structs
T means type
LC means Last/Current (see function-like defines
above; after flags, before values.)
PID means Proportional, Integral and Derivative.
*/
typedef struct
	{
	int curr;
	int last;
	int stepStart;
	}
	T_LC_INT;

typedef struct
	{
	float kp;
	float ki;
	float kd;
	int error;
	int integral;
	int derivative;
	int lastError;
	int output;
	}
	T_PID;
