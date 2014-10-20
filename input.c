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
	senGyro.curr =		SensorValue[GYRO]%3600;
	senQSEL.curr =		SensorValue[QUAD_L];
	senQSER.curr =		SensorValue[QUAD_R];
	senUS.curr =		SensorValue[ULTRA];
	senWrist.curr =		SensorValue[WRIST_POT];
	senLift.curr =		SensorValue[LIFT_ENC];
	senLineL =			SensorValue[LINE_L];
	senLineC =			SensorValue[LINE_C];
	senLineR =			SensorValue[LINE_R];

	if (autoClockRunning)
		autoTimer = time1(T3);

	if (senGyro.last>3400 && senGyro.curr<200) senAddToAbsGyro+=3600;
	if (senGyro.last<200 && senGyro.curr>3400) senAddToAbsGyro-=3600;
	senAbsGyro.curr = senAddToAbsGyro + senGyro.curr;
	}
