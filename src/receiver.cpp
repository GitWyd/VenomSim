/*

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "config.h"
#include "mathHelp.h"
#include "receiver.h"

receiver::receiver()
{
	this->roll_pwm = RECEIVER_ROLL_KEY_PWM;
	this->pitch_pwm	= RECEIVER_PITCH_KEY_PWM;
	this->yaw_pwm = RECEIVER_YAW_KEY_PWM;
	this->throttle_pwm = RECEIVER_THROTTLE_KEY_PWM;

	this->output_blocked = false;
}

receiver::~receiver()
{
}

void receiver::get_desired_theta(Vector3d &theta_d,double _roll,double _pitch, double _yaw)
{
	// zero signals in case no input or blocked
	theta_d(0) = RECEIVER_PWM_ZERO_SIGNAL;
	theta_d(1) = RECEIVER_PWM_ZERO_SIGNAL;
	theta_d(2) = RECEIVER_PWM_ZERO_SIGNAL;

	theta_d(0) += mapp<double>(_roll, ROLL_MIN,ROLL_MAX,RECEIVER_PWM_MIN - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2, RECEIVER_PWM_MAX - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2);
	theta_d(1) += mapp<double>(_pitch,PITCH_MIN,PITCH_MAX,RECEIVER_PWM_MIN - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2, RECEIVER_PWM_MAX - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2);
	theta_d(2) += mapp<double>(_yaw,  YAW_MIN,YAW_MAX,RECEIVER_PWM_MIN - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2, RECEIVER_PWM_MAX - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2);

}

void receiver::get_desired_throttle(double &throttle,double _throttle)
{	
	// user has to put stick in hover position if he does not want to climb/sink	
	throttle = getPWMinPointOfEquilibirum();

	//to make sure that the drone remain stable we input throttle is 0
	throttle += mapp<double>(_throttle,-1,1,RECEIVER_PWM_MIN - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2,RECEIVER_PWM_MAX - (RECEIVER_PWM_MIN + RECEIVER_PWM_MAX)/2);


}

void receiver::block_receiver(bool blocked)
{
	this->output_blocked = blocked;
}


