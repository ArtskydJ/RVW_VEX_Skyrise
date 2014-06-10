void initialize(int INinitPoint)
	{
	zeroMotors();
	//--SET VALUES--//
	//PID Controllers
	PIDClaw.kp = 2.5;
	PIDClaw.ki = 0.00;
	PIDClaw.kd = 0.00;

	PIDLift.kp = 1.1;
	PIDLift.ki = 0.00;
	PIDLift.kd = 0.00;

	PIDWrist.kp = 1;
	PIDWrist.ki = 0.00;
	PIDWrist.kd = 0.00;

	PIDLineFollow.kp = 0.2;
	PIDLineFollow.ki = 0.00;
	PIDLineFollow.kd = 0.00;

	PIDDriveL.kp = 0.5;
	PIDDriveL.ki = 0.00;
	PIDDriveL.kd = 0.00;

	PIDDriveR.kp = 0.5;
	PIDDriveR.ki = 0.00;
	PIDDriveR.kd = 0.00;

	PIDGyro1.kp = 1.8; //1 wheel
	PIDGyro1.ki = 0.00;
	PIDGyro1.kd = 0.02;

	PIDGyro2.kp = 1.2; //2 wheels
	PIDGyro2.ki = 0.00;
	PIDGyro2.kd = 0.00;
	//Motor Slew Constants
	for (int j=0; j<10; j++)
		slewConstants[DISABLED][j]		= FULL;				//DISABLED
	slewConstants[AUTONOMOUS][DRIVE_FL]	= AUTO_DRV_SLEW;	//AUTONOMOUS
	slewConstants[AUTONOMOUS][DRIVE_FR]	= AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BL]	= AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][DRIVE_BR]	= AUTO_DRV_SLEW;
	slewConstants[AUTONOMOUS][LIFT_L]	= AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][LIFT_R]	= AUTO_LIFT_SLEW;
	slewConstants[AUTONOMOUS][WRIST]	= AUTO_WRST_SLEW;
	slewConstants[AUTONOMOUS][CLAW]		= AUTO_CLAW_SLEW;

	//--RESET TIMERS--//
	ClearTimer(T1); //Current Autonomous Step
	ClearTimer(T2); //PID wait
	ClearTimer(T3); //Entire Autonomous Time
	ClearTimer(T4); //unassigned

	//--MISCELLANEOUS--//
	writeDebugStreamLine("================");
	sysState.curr=AUTONOMOUS;
	setToZero(senClaw);
	setToZero(senLift);
	setToZero(senWrist);
	setToZero(senQSEL);
	setToZero(senQSER);
	senAddToAbsGyro=INinitPoint;
	}
