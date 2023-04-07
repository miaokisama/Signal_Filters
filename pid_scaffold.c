
#include <stdio.h>
#include <stdlib.h>


// pid
typedef struct pid_parameter
{
	float Target;		// Goal
	float Current;		// 实际值(反馈值)
	float Error;		// 偏差值(当前偏差)
	float Last_error;	// 上次偏差值
	float Integral;		// 积分值
	float Kp,Ki,Kd;		// 比例,积分,微分系数
	float Out;			// 输出值
}pid;

pid* createPID() {
	// Allocate memory and initalise struct variables
	pid *p;
	// Globle var
 	p=malloc(sizeof(pid));
 	return p;
}

// Algorithm of PID
float PID(pid* user_pid, float target)
{
	//*************************************************
	//将用户输入的目标传入目标值
	//误差=目标值 - 实际值
	//积分项为累加误差
	//pid输出值计算
	//更新误差
	//*************************************************
	user_pid->Target = target;
	user_pid->Error = user_pid->Target - user_pid->Current;
	user_pid->Integral += user_pid->Error;
	user_pid->Out = user_pid->Kp*user_pid->Error + user_pid->Ki*user_pid->Integral + user_pid->Kd*(user_pid->Error-user_pid->Last_error);
	user_pid->Last_error = user_pid->Error;
	user_pid->Current +=  user_pid->Out;
	return user_pid->Out ;	// Actural output from PID
}

// PID init
void Pid_setup(pid* user_pid)
{
	printf("user_pid init...\n");
	user_pid->Kp=0.2;   // Propotional
	user_pid->Ki=0.2;   // Integral
	user_pid->Kd=0.4;   // Differential
	user_pid->Target=0;   
	user_pid->Current=20;
	user_pid->Error=0;
	user_pid->Last_error=0;
	user_pid->Integral=0;
	user_pid->Out=0;
	printf("user_pid init end.\n");
}


void main() {
  float current_system_state;
  float goal = 150;
  pid *my_pid = createPID();
  Pid_setup(my_pid);
  for(int i = 0; i < 150; i++)
  {
	current_system_state = my_pid->Current + PID(my_pid, goal);
  	printf("%.2f \n", current_system_state);
  }
}
  