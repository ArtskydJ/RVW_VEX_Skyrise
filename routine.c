//Drv Type,	Left,	Right,	Lift,	Wrist,	Claw,	End type,	Action	//START AT RED HANGING ZONE

auto(GYROL, 450,	FULL,	L_CUBE,	W_FWD,	0,		DRIV_READY,	PID);	//Turn
auto(STR,	450,	770,	L_CUBE,	0,		FWD,	DRIV_READY,	NEXT);	//Straight
auto(STR,	450,	-500,	L_CUBE,	0,		0,		DRIV_READY,	NEXT);	//Reverse
auto(STR,	HANG_Z,	-950,	L_CUBE,	0,		0,		DRIV_READY,	NEXT);	//Reverse
auto(SPD,	0,		0,		L_CUBE,	0,		0,		TIME_LIMIT,	300);	//Wait
auto(STR,	HANG_Z,	-970,	L_CUBE,	0,		0,		DRIV_READY,	NEXT);	//Reverse
auto(GYRO2, -1100,	FULL,	L_CUBE,	0,		0,		DRIV_READY,	PID);	//Turn + Lift
auto(STR,	700,	980,	L_CUBE,	0,		0,		DRIV_READY,	NEXT);	//Forward + Lift
auto(GYRO2, 200,	FULL,	L_CUBE,	-100,	0,		DRIV_READY,	PID);	//Align
auto(SPD,	0,		0,		L_CUBE,	REV,	0,		TIME_LIMIT,	2500);	//Dump - 1st double red
