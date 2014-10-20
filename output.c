void output()
	{
	if (sysState.curr == DISABLED)
		{
		zeroMotors();
		}
	else
		{
		writeDebugStreamLine(
			"L:%d\tR:%d\tLift:%d\tWrist:%d\tClaw:%d",
			outDrvL,
			outDrvR,
			outLift,
			outWrst,
			outClaw
		);
		mtrTarget[DRIVE_FL] = outDrvL;
		mtrTarget[DRIVE_BL] = outDrvL;
		mtrTarget[DRIVE_FR] = outDrvR;
		mtrTarget[DRIVE_BR] = outDrvR;
		mtrTarget[LIFT_L] = outLift;
		mtrTarget[LIFT_R] = outLift;
		mtrTarget[WRIST]  = outWrst;
		mtrTarget[CLAW]   = outClaw;
		}

	for (int j=0; j<10; j++)
		{
#ifdef SLEW
		mtrSlewed[j] += slew(mtrTarget[j], mtrSlewed[j], slewConstants[sysState.curr][j]); //SLEW CONTROLLERS
		capValue(-127, mtrSlewed[j], 127); //CAP ALL MOTORS
		motor[j] = mtrSlewed[j]; //ASSIGN MOTORS
#else
		capValue(-127, mtrTarget[j], 127); //CAP ALL MOTORS
		motor[j] = mtrTarget[j]; //ASSIGN MOTORS
#endif
		}
	string temp1,temp2;
	stringFormat(temp1,"Time:%.1f",((float)autoTimer/1000));
	stringFormat(temp2, "Step: %d", autoStep);	//Show step
	displayLCDCenteredString(0,temp1);
	displayLCDCenteredString(1,temp2);
	}
	