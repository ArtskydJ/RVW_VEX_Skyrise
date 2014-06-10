void autoReset(int INcurrentStep)
	{
	zeroMotors();
	if (INcurrentStep == 0) //Runs at start of Autonomous
		{
		ClearTimer(T1);
		ClearTimer(T3);
		autoTimer=0;
		autoClockRunning = true;
		autoStep = 0;
		setToZero(senQSEL);
		setToZero(senQSER);
		setToZero(senClaw);
		setToZero(senLift);
		setToZero(senWrist);
		}
	else //Runs at end of Autonomous
		{
		instantZeroMotors();
		writeDebugStreamLine("----------------");
		writeDebugStreamLine("Time: %.1f",((float)autoTimer/1000));
		writeDebugStreamLine("----------------");
		autoClockRunning = false;
		setToZero(senQSEL);
		setToZero(senQSER);
		setToZero(senClaw);
		setToZero(senLift);
		setToZero(senWrist);
		}
	}


void auto(int INdrvType, long INdrvLft, long INdrvRht, int INlift, int INendType, int INdelayPID)
	{

	//Next Step...
	string msg1;
	if (autoStep < NO_TIME_RECORDS)
		autoTimeRecord[autoStep] = time1(T1);
	if (time1(T1)<1000)
		writeDebugStreamLine("%d\t\t|%d",time1(T1),autoStep);
	else
		writeDebugStreamLine("%d\t|%d",time1(T1),autoStep);
	autoClockRunning=true;
	autoDriveReady = false;
	autoLiftReady = false;
	autoHitTarget = NOT_HIT;
	autoStepStatus = SENSOR_HIT;
	autoStep++;
	nMotorEncoder[DRIVE_BL]=0;
	nMotorEncoder[DRIVE_BR]=0;
	setToZero(senQSEL);
	setToZero(senQSER);

	//--Step start values--//
	setStep(senGyro);
	setStep(senAbsGyro);
	setStep(senQSEL);
	setStep(senQSER);
	setStep(senClaw);
	setLast(senLift);
	setLast(senWrist);
	ClearTimer(T1);
	/*while(time1(T1)<2000){} //DELAY BETWEEN STEPS
	ClearTimer(T1);*/


	while(autoHitTarget!=NEXT)
		{
		input();

		//--Set Outputs--//
		if (INlift==0)
			{
			outClaw = 0;
			outLift = 0;
			outWrst = 0;
			autoLiftReady = true;
			}
		else
			{
			if (time1(T1)<SHUT_CLAW_MS)
				outClaw = updatePIDController(PIDClaw,	presetClaw[INlift-1] - senClaw.curr);
			else
				outClaw = updatePIDController(PIDWrist,	C_SH - senClaw.curr); //Shut claw after SHUT_CLAW_MS
			outLift =	updatePIDController(PIDLift,	presetLift[INlift-1] - senLift.curr);
			outWrst =	updatePIDController(PIDWrist,	presetWrist[INlift-1]- senWrist.curr); //Shut claw after 1.5 sec
			if (abs(PIDClaw.error) < PID_ZONE &&
				abs(PIDLift.error) < PID_ZONE &&
				abs(PIDWrist.error) < PID_ZONE)	autoLiftReady = true;
			}


		/* Drive Outputs */
		outDrvL = 0;
		outDrvR = 0;
		switch (INdrvType)
			{
			case SPD:
				outDrvL = INdrvLft;
				outDrvR = INdrvRht;
				autoDriveReady = true;
				break;
			case ENC:
				updatePIDController(PIDDriveL,INdrvLft - diffStep(senQSEL));
				updatePIDController(PIDDriveR,INdrvRht - diffStep(senQSER));
				outDrvL = PIDDriveL.output;
				outDrvR = PIDDriveR.output;
				if (abs(PIDDriveL.error)<PID_ZONE && abs(PIDDriveR.error)<PID_ZONE) autoDriveReady = true;
				break;
			case STR:											//Gyro keep straight
				updatePIDController(PIDGyro2, INdrvLft-senAbsGyro.curr);
				updatePIDController(PIDDriveL,INdrvRht - (diffStep(senQSEL) + diffStep(senQSER))/2 );
				outDrvL = PIDDriveL.output;		//Left
				capValue(-TURN,outDrvL,TURN);
				outDrvL+=PIDGyro2.output;
				outDrvR = PIDDriveL.output;		//Right
				capValue(-TURN,outDrvR,TURN);
				outDrvR-=PIDGyro2.output;
				if (abs(PIDDriveL.error) < PID_ZONE && abs(PIDDriveR.error) < PID_ZONE) autoDriveReady = true;
				break;
			case FLINE:											//Follow Line
				updatePIDController(PIDLineFollow,senLight.curr-LINE);
				outDrvL = INdrvLft - PIDLineFollow.output;
				outDrvR = INdrvLft + PIDLineFollow.output;
				break;
			case CMP_2:											//Gyro turn both
				updatePIDController(PIDGyro2, INdrvLft-diffStep(senGyro));
				outDrvL =  PIDGyro2.output; capValue(-abs(INdrvRht),outDrvL,abs(INdrvRht));
				outDrvR = -PIDGyro2.output; capValue(-abs(INdrvRht),outDrvL,abs(INdrvRht));
				if (abs(PIDGyro2.error) < PID_ZONE) autoDriveReady = true;
				break;
			case CMP_L:											//Gyro turn left - GOOD
				updatePIDController(PIDGyro1, INdrvLft-diffStep(senAbsGyro));
				outDrvL = PIDGyro1.output; capValue(-abs(INdrvRht),outDrvR,abs(INdrvRht));
				outDrvR = 0;
				if (abs(PIDGyro1.error) < PID_ZONE) autoDriveReady = true;
				break;
			case CMP_R:											//Gyro turn right - GOOD
				updatePIDController(PIDGyro1, -INdrvLft+diffStep(senAbsGyro));
				outDrvL = 0;
				outDrvR = PIDGyro1.output; capValue(-abs(INdrvRht),outDrvR,abs(INdrvRht));
				if (abs(PIDGyro1.error) < PID_ZONE) autoDriveReady = true;
				break;
			}

		if (autoHitTarget==NOT_HIT)
			{
			if (INendType!=RESET_AUTO && INendType!=TIME_LIMIT) //INdelayPID is used as time limit in TIME_LIMIT
				{
				if (INdelayPID<NEXT) INdelayPID=NEXT;
				if (INdelayPID>PID)  INdelayPID=PID;
				}
			ClearTimer(T2); //Timer for PID wait
			switch(INendType) // This code asks what type of target condition are we looking for? Have we met it?
				{
				case TIME_LIMIT: if (time1(T1)>=INdelayPID)				autoHitTarget=NEXT;		  break;
				case DRIV_READY: if (autoDriveReady)					autoHitTarget=INdelayPID; break;
				case LIFT_READY: if (autoLiftReady)						autoHitTarget=INdelayPID; break;
				case FULL_READY: if (autoDriveReady && autoLiftReady)	autoHitTarget=INdelayPID; break;
				default: break; //nothing
				}
			}
		if (autoHitTarget==PID && time1(T2)>=PID_WAIT_MS)	autoHitTarget=NEXT; //PID timeout

		output();

		//--Sensors--//
		setLast(senGyro);
		setLast(senAbsGyro);
		setLast(senQSEL);
		setLast(senQSER);
		setLast(senClaw);
		setLast(senLift);
		setLast(senWrist);
		//--System--//
		setLast(sysState);

		sysLooptime=time1(T4);
		while (time1(T4) < MIN_LOOP_MS) {}
		ClearTimer(T4);
		}
	}
