#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Kalman defined
typedef struct kalman_parameter
{
	float x_last;		
	float P_current;	
	float P_last;	
	float K;	
	float R_cov;		
	float Q_cov;
	float out;
}kalf;

// Kalmanfilter init
void kalman_init(kalf* user_kfp){
    user_kfp->x_last = 0;
    user_kfp->P_current = 0;
    user_kfp->P_last = 1;
    user_kfp->R_cov = 0.2; 
    user_kfp->Q_cov = 0.0005;
    // printf("user_kfp init end.\n");
}

kalf* createKalf() {
    // Allocate memory and initalise struct variables
	kalf *p;
    // Globle var
 	p=malloc(sizeof(kalf));
 	return p;
}
float kalFilter(kalf* user_klf, float z){
    // Predict
    user_klf->x_last =  user_klf->x_last; 
    user_klf->P_current = user_klf->P_last + user_klf->Q_cov;
    
    // Update
    user_klf->K = user_klf->P_current / (user_klf->P_current + user_klf->R_cov);
    user_klf->out = user_klf->x_last + user_klf->K * (z - user_klf->x_last);
    user_klf->P_last = (1- user_klf->K )*user_klf->P_current;
    return user_klf->out;
}

 /* normal distribution, centered on 0, std dev 1 */
double random_normal() 
{
    /* uniform distribution, (0..1] */
    double drand = (rand()+1.0)/(RAND_MAX+1.0);
    return sqrt(-2*log(drand)) * cos(2*M_PI*drand);
}

int main()
{
    float current_estimation;
    double input_signal[1000];
    kalf *my_klf = createKalf();
    kalman_init(my_klf);
    for (int i=0; i<1000; i++)
    {
        input_signal[i] = 1 + 0.2*random_normal();
        current_estimation = kalFilter(my_klf, input_signal[i]);
        serial print
        printf("%d", i);
        printf(" %.2f", input_signal[i]);
        printf(" %.2f", current_estimation);
        printf("\n");
        
    }
    
    return 0;
}