//Drv Type,	Left,	Right,	Lift,	Dump,	Intake,	End type,	Action	//START AT RED HANGING ZONE

auto(GYRO2, TURN_R,	FULL,	L_DRIV,	0,		0,		DRIV_READY,	PID);	//Turn
auto(STR,	HANG_Z,	770,	L_INTK,	0,		FWD,	DRIV_READY,	NEXT);	//Straight
auto(STR,	HANG_Z,	-1500,	L_DRIV,	0,		0,		DRIV_READY,	NEXT);	//Reverse
auto(STR,	HANG_Z,	-950,	L_GOA2,	0,		0,		DRIV_READY,	NEXT);	//Reverse
auto(SPD,	0,		0,		L_DRIV,	0,		0,		TIME_LIMIT,	300);	//Wait
auto(STR,	HANG_Z,	-970,	L_DRIV,	0,		0,		DRIV_READY,	NEXT);	//Reverse
auto(GYRO2, -1100,	FULL,	L_GOAL,	0,		0,		DRIV_READY,	PID);	//Turn + Lift
auto(STR,	700,	980,	L_GOAL,	0,		0,		DRIV_READY,	NEXT);	//Forward + Lift
auto(GYRO2, 200,	FULL,	L_GOA2,	-100,	0,		DRIV_READY,	PID);	//Align
auto(SPD,	0,		0,		L_GOA2,	REV,	0,		TIME_LIMIT,	2500);	//Dump - 1st double red