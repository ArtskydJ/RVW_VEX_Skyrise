/* VARIABLES
 All variables for joystick sticks, buttons,
robot sensors, autonomous values, debugger
values, and general values.
*/
// SENSORS
int senAddToAbsGyro; //Not actual sensor...
T_LC_INT senGyro;
T_LC_INT senAbsGyro;
T_LC_INT senQSEL;
T_LC_INT senQSER;
T_LC_INT senUS;
T_LC_INT senLight;
T_LC_INT senClaw;
T_LC_INT senLift;
T_LC_INT senWrist;

/* OUTPUT VARIABLES
 These variables are written-to, processed and
read-from, to help assign motor values.
*/
int outDrvL;
int outDrvR;
int outClaw;
int outLift;
int outWrst;

//Autonomous
int autoHitTarget;
int autoStepStatus;
bool autoDriveReady;
bool autoLiftReady;
bool autoClockRunning = false;
int  autoStep = 0;
unsigned int autoTimer = 0;

//System
bool sysAutoMode = true; //Start in auton mode
bool sysDisabledMode = false;
T_LC_INT sysState;
int sysLooptime;

//PID
T_PID PIDClaw;
T_PID PIDLift;
T_PID PIDWrist;
T_PID PIDLineFollow;
T_PID PIDDriveL;
T_PID PIDDriveR;
T_PID PIDGyro1;
T_PID PIDGyro2;

//--Arrays--//
short mtrTarget[10]={0,0,0,0,0,0,0,0,0,0};
short mtrSlewed[10]={0,0,0,0,0,0,0,0,0,0};
char slewConstants[2][10];//Low-Level/Open/Shut		Medium-Open/Shut	High-Open/Shut			Corner-Open/Shut	Drop-Open/Shut	New-Open/Shut
const int presetClaw[] =  {C_SH,	C_OP,	C_SH,		C_OP,	C_SH,		C_OP,	C_SH,		C_OP,	C_SH,		C_OP,	C_SH,	C_OP,	C_SH	};
const int presetLift[] =  {L_LOW,	L_LOW,	L_LOW,		L_MED,	L_MED,		L_HIGH,	L_HIGH,		L_CRNR,	L_CRNR,		0,		0,		0,		0,		};
const int presetWrist[] = {W_LEV,	W_MED,	W_HI,		W_MED,	W_HI,		W_MED,	W_HI2,		W_MED,	W_HI,		W_DRP,	W_DRP,	W_NEW,	W_NEW	};
unsigned int autoTimeRecord[NO_TIME_RECORDS];
