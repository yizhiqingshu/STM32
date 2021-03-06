#include "bsp_PID.h"


struct pid_ _PID_;
void pid_Init(void)
{
	_PID_.Set_=0.0;
	_PID_.Actual_=0.0;
	_PID_.err_=0.0;
	_PID_.err_Last_=0.0;
	_PID_.err_Last__=0.0;
	_PID_.Kp_=0.2;
	_PID_.Ki_=0.015;
	_PID_.Kd_=0.2;
	_PID_.Kp_1=0.2;
	_PID_.Ki_1=0.015;
	_PID_.Kd_1=0.2;
	_PID_.voltage_=0.0;
	
	
}

float PID_up(float Current)
{
_PID_.Set_=Current;
_PID_.err_=_PID_.Set_-_PID_.Actual_;
	_PID_.voltage_=_PID_.Kp_*(_PID_.err_-_PID_.err_Last_)
	                +_PID_.Ki_*_PID_.err_+
	                _PID_.Kd_*(_PID_.err_-2*_PID_.err_Last_-_PID_.err_Last__);
	_PID_.err_Last__=_PID_.err_Last_;
	_PID_.err_Last_=_PID_.err_;
	_PID_.voltage__+=_PID_.voltage_;
	return (uint16_t)_PID_.voltage__;
}


