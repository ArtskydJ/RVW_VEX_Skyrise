void input()
	{
#ifdef PRACTICE //Practice
	if (sysDisabledMode)	sysState.curr = DISABLED;
	else					sysState.curr = AUTONOMOUS;
#else			//Competition
	if (bIfiRobotDisabled)	sysState.curr = DISABLED;
	else					sysState.curr = AUTONOMOUS;
#endif
	if (changed(sysState))
		{
		switch (sysState.curr)
			{
			case AUTONOMOUS: autoStep=0; break;
			case DISABLED: break;
			}
		}

	//--Robot Sensors--//
	senGyro.curr =		SensorValue[COMPASS]%3600;
	senLight.curr =		SensorValue[LIGHT];
	senUS.curr =		SensorValue[ULTRA];
	senQSEL.curr =		-nMotorEncoder[DRIVE_BL];
	senQSER.curr =		nMotorEncoder[DRIVE_BR];
	senClaw.curr =		nMotorEncoder[CLAW];
	senLift.curr =		nMotorEncoder[LIFT_L];
	senWrist.curr =		nMotorEncoder[WRIST];

	if (autoClockRunning)
		autoTimer = time1(T3);

	if (senGyro.last>3400 && senGyro.curr<200) senAddToAbsGyro+=3600;
	if (senGyro.last<200 && senGyro.curr>3400) senAddToAbsGyro-=3600;
	senAbsGyro.curr = senAddToAbsGyro + senGyro.curr;
	}

////////////////////////////// I/O //////////////////////////////

void output()
	{
	if (sysState.curr == DISABLED)
		{
		zeroMotors();
		}
	else
		{
		mtrTarget[DRIVE_FL] = outDrvL;
		mtrTarget[DRIVE_FR] = outDrvR;
		mtrTarget[DRIVE_BL] = outDrvL;
		mtrTarget[DRIVE_BR] = outDrvR;
		mtrTarget[CLAW]		= outClaw;
		mtrTarget[LIFT_L]	= outLift;
		mtrTarget[LIFT_R]	= outLift;
		mtrTarget[WRIST]	= outWrst;
		}

	capValue(-40, mtrTarget[LIFT_L], 60); //CAP LIFT SLOWER
	capValue(-40, mtrTarget[LIFT_R], 60); //CAP LIFT SLOWER
	for (int j=0; j<10; j++)
		{
#ifdef SLEW
		mtrSlewed[j] += slew(mtrTarget[j], mtrSlewed[j], slewConstants[sysState.curr][j]); //SLEW CONTROLLERS
		capValue(-100, mtrSlewed[j], 100); //CAP ALL MOTORS
		motor[j] = mtrSlewed[j]; //ASSIGN MOTORS
#else
		capValue(-100, mtrTarget[j], 100); //CAP ALL MOTORS
		motor[j] = mtrTarget[j]; //ASSIGN MOTORS
#endif
		}
	string temp1,temp2;
	StringFormat(temp1,"Time:%.1f",((float)autoTimer/1000));
	StringFormat(temp2, "Step: %d", autoStep);	//Show step
	nxtDisplayCenteredTextLine(0,temp1);
	nxtDisplayCenteredTextLine(1,temp2);
	}
