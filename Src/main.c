#define STM32F446xx  1
#include <stm32f4xx.h>
#include <stdio.h>
#include "arm_math.h"
#include "bit_calc.h"
#include "FPU.h"
#include "USART.h"
#include "systick.h"
#include "signals.h"

float32_t g_in_sig_sample;


extern float32_t _5hz_signal[LENGTH_SIGNAL_5HZ];
extern float32_t inputSignal_f32_1kHz_15kHz[LENGTH_SIGNAL_1KHZ_15KHZ];
extern float32_t _signal_ecg[LENGTH_SIGNAL_ECG];

void get_dft_output_mag(float32_t* real_sig,float32_t* img_sig,float32_t* out_sig,uint16_t sig_length);
void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_length);
void calc_sig_idft(float32_t *sig_rex_arr, float32_t *sig_imx_arr,float32_t *sig_out_arr, uint32_t sig_length);


void plot_signal(float32_t * sig,uint32_t length_signal);
void plot_signal_UART(float32_t * sig,uint32_t length_signal);
void pseuodo_delay(uint32_t delay);

uint8_t counter=0;


int main(void)
{

	 uint16_t length_sig=LENGTH_SIGNAL_1KHZ_15KHZ;

	 float32_t real_sig[length_sig];
	 float32_t img_sig[length_sig];
	 float32_t out_sig[length_sig];


	 FPU_init();
	 USART_TX_init();


	  calc_sig_dft(inputSignal_f32_1kHz_15kHz,real_sig,img_sig,length_sig);
	  get_dft_output_mag(real_sig, img_sig, out_sig,length_sig);
	  calc_sig_idft(real_sig,img_sig,out_sig,length_sig);


      while(1){


     plot_signal_UART(out_sig,length_sig);

	}
}

void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_length)
{
	uint16_t i,k,j;
	for(j=0;j<sig_length;j++)
	{
		 sig_dest_rex_arr[j] =0;
		  sig_dest_imx_arr[j] =0;
	}

	 for(k=0;k<sig_length;k++)
	{
		for(i=0;i<sig_length;i++)
		{
					sig_dest_rex_arr[k] += sig_src_arr[i]*cos(2*PI*k*i/sig_length);
				    sig_dest_imx_arr[k] -= sig_src_arr[i]*sin(2*PI*k*i/sig_length);


		}

	}
}

void calc_sig_idft(float32_t *sig_rex_arr, float32_t *sig_imx_arr,float32_t *sig_out_arr,uint32_t sig_length){

	 uint16_t i,k,j;
	 for(j=0;j<sig_length;j++){

		 sig_out_arr[j] =0;

	}

	 for(k=0;k<sig_length;k++)
	{
		for(i=0;i<sig_length;i++)
		{
					sig_out_arr[k] += (sig_rex_arr[i]*cos(2*PI*k*i/sig_length)-sig_imx_arr[i]*sin(2*PI*k*i/sig_length));


		}

		sig_out_arr[k]/=sig_length;

	}

}


void get_dft_output_mag(float32_t* real_sig,float32_t* img_sig,float32_t* out_sig,uint16_t sig_length){


	for(uint16_t k=0;k<sig_length;k++){
	 out_sig[k] = sqrt((pow(real_sig[k],2) + pow(img_sig[k],2)));
	}
}

void plot_signal(float32_t * sig,uint32_t length_signal){

	for(uint16_t counter=0; counter<length_signal;counter++){
		g_in_sig_sample=sig[counter];
		pseuodo_delay(9000);
	}
	g_in_sig_sample=0;
}

void plot_signal_UART(float32_t * sig,uint32_t length_signal){
	for(uint16_t counter=0; counter<length_signal;counter++){
			printf("%f\r\n",sig[counter]);
			pseuodo_delay(9000);
			}
}

void pseuodo_delay(uint32_t delay){

	for(uint16_t counter=0; counter<delay;counter++);
}


