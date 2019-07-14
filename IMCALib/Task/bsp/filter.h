#ifndef _FILTER_H_
#define _FILTER_H_

#define mat         arm_matrix_instance_f32 
#define mat_init    arm_mat_init_f32
#define mat_add     arm_mat_add_f32
#define mat_sub     arm_mat_sub_f32
#define mat_mult    arm_mat_mult_f32
#define mat_trans   arm_mat_trans_f32
#define mat_inv     arm_mat_inverse_f32

typedef struct{
	double raw_value;
	double xbuf[18];
	double ybuf[18];
	double filtered_value;
}Filter_t;

double NUM[18] = {
  0.0001539807224874,-0.001633551718237, 0.008285871521075, -0.02655137141783,
    0.05976268341326, -0.09892004512411,   0.1209510267949,  -0.1024952672175,
    0.04044670396161,  0.04044670396161,  -0.1024952672175,   0.1209510267949,
   -0.09892004512411,  0.05976268341326, -0.02655137141783, 0.008285871521075,
  -0.001633551718237,0.0001539807224874
};
double DEN[18] = {
                   1,   -12.83384996104,    77.93650732675,   -297.3335694968,
      797.9129616887,   -1597.972651706,    2472.494945198,   -3018.357074163,
      2942.681165509,   -2303.842335957,    1448.206814835,   -726.6729407251,
      287.4544421962,   -87.75235536838,    19.96212762001,      -3.188300212,
     0.3191936459711, -0.01508036852769
};

typedef struct
{
  float raw_value;
  float filtered_value[2];
  mat xhat, xhatminus, z, A, H, AT, HT, Q, R, P, Pminus, K;
} kalman_filter_t;

typedef struct
{
  float raw_value;
  float filtered_value[2];
  float xhat_data[2], xhatminus_data[2], z_data[2],Pminus_data[4], K_data[4];
  float P_data[4];
  float AT_data[4], HT_data[4];
  float A_data[4];
  float H_data[4];
  float Q_data[4];
  float R_data[4];
} kalman_filter_init_t;

double Chebyshev50HzLPF(Filter_t *F);
void kalman_filter_init(kalman_filter_t *F, kalman_filter_init_t *I);
float *kalman_filter_calc(kalman_filter_t *F, float signal1, float signal2);

#endif

