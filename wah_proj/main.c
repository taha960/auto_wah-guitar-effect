#include "dsk6713_aic23.h"
#include "AutoWah.h"

Uint32 input_sample();
void output_sample(int out_data);
void comm_intr();
double AutoWah_process(int xin);
void AutoWah_init(short effect_rate,short sampling,short maxf,short minf,short Q,double gainfactor,short freq_step);
void AutoWah_sweep(void);

Uint32 fs = DSK6713_AIC23_FREQ_16KHZ;
short Xn;
short XnBuf[1600];
short ynBuf[1600];
Uint16 i = 0;
short xin;
short yout;


interrupt void c_int11()
{
	/*Xn = input_sample();
	XnBuf[i] = Xn;
	i = (i + 1) % 128; //incrumetation

	output_sample(Xn);*/
	AutoWah_init(2000,fs,3000,500,4,0.705,10);
	            /*When there's new sample at your ADC or CODEC input*/
	            /*Read the sample*/
	            xin = input_sample();
	            ynBuf[i]= xin;


	            /*Apply AutoWah_process function to the sample*/
	            yout =AutoWah_process(xin);
	            XnBuf[i] = yout;
	            i = (i + 1) % 1600;

	            /*Send the output value to your DAC or codec output*/
	            output_sample(yout);
	            /*Makes the LFO vary*/
	            AutoWah_sweep();
	            return;



}

main()
 {
	comm_intr();
	while(1);
}
