void initialize(int INinitPoint)
	{
	zeroMotors();
	//--SET VALUES--//
	//PID Controllers
	PIDLift.kp = 0.8;
	PIDLift.ki = 0.00;
	PIDLift.kd = 0.00;

	PIDWrist.kp = 0.8;
	PIDWrist.ki = 0.00;
	PIDWrist.kd = 0.00;

	PIDLineFollow.kp = 0.2;
	PIDLineFollow.ki = 0.00;
	PIDLineFollow.kd = 0.00;

	PIDDriveL.kp = 0.8;
	PIDDriveL.ki = 0.00;
	PIDDriveL.kd = 0.00;

	PIDDriveR.kp = 0.8;
	PIDDriveR.ki = 0.00;
	PIDDriveR.kd = 0.00;

	PIDGyro1.kp = 1.8; //1 side
	PIDGyro1.ki = 0.00;
	PIDGyro1.kd = 0.02;

	PIDGyro2.kp = 1.2; //2 sides
	PIDGyro2.ki = 0.00;
	PIDGyro2.kd = 0.00;
	//Motor Slew Constants
	for (int j=0; j<10; j++)
		slewConstants[DISABLED][j]		= FULL;				//DISABLED
	slewConstants[AUTONOMOUS][DRIVE_FL]	= AUTO_DRIV_SLEW;	//AUTONOMOUS
	slewConstants[AUTONOMOUS][DRIVE_BL]	= AUTO_DRIV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_FR]	= AUTO_DRIV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BR]	= AUTO_DRIV_SLEW;
	slewConstants[AUTONOMOUS][WRIST]	= AUTO_WRST_SLEW;
	slewConstants[AUTONOMOUS][CLAW] 	= AUTO_CLAW_SLEW;
	slewConstants[AUTONOMOUS][LIFT_L]	= AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][LIFT_R]	= AUTO_LIFT_SLEW;

	//--RESET TIMERS--//
	clearTimer(T1); //Current Autonomous Step
	clearTimer(T2); //PID wait
	clearTimer(T3); //Entire Autonomous Time
	clearTimer(T4); //unassigned

	//--MISCELLANEOUS--//
	writeDebugStreamLine("================");
	sysState.curr=AUTONOMOUS;
	setToZero(senWrist);
	setToZero(senLift);
	setToZero(senQSEL);
	setToZero(senQSER);
	senAddToAbsGyro=INinitPoint;
	}
