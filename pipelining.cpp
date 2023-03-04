// g++ -O0 -std=c++11 pipelining.cpp && ./a.out

#include <stdio.h>
#include "utils.h"

void baseline(long n, double *a, double *b) {
	double s = 0;
	int i;

	for (i=0; i<n; i++)
	 s += a[i]*b[i];
}

void modified_1(long n, double *a, double *b) {
	double s = 0;
	double sum1 = 0;
	double sum2 = 0;
	int i;

	for (i = 0; i < n/2-1; i++) {
		sum1 += a[2*i] * b[2*i];
		sum2 += a[2*i+1] * b[2*i+1];
	}
	s = sum2 + sum1;
}

void modified_2(long n, double *a, double *b) {
	double s = 0;
	double sum1 = 0;
	double sum2 = 0;
	double temp1 = 0;
	double temp2 = 0;
	int i;

	for (i = 0; i < n/2-1; i++) {
		temp1 = *(a + 0) * *(b + 0);
		temp2 = *(a + 1) * *(b + 1);
		sum1 += temp1; sum2 += temp2;
		a += 2; b += 2;
	}
	s = sum2 + sum1;
}

void modified_3(long n, double *a, double *b) {
	double s = 0;
	double sum1 = 0;
	double sum2 = 0;
	double temp1 = 0;
	double temp2 = 0;
	int i;

	for (i = 0; i < n/2-1; i++) {
		sum1 += temp1;
		temp1 = *(a + 0) * *(b + 0);

		sum2 += temp2;
		temp2 = *(a + 1) * *(b + 1);
		 
		a += 2; b += 2;
	}
	s = sum2 + sum1;
	// printf("s, unrolled 2: %f\n", s);
}

void mod_unroll4(long n, double *a, double *b) {
	double s = 0;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;
	double sum4 = 0;
	double temp1 = 0;
	double temp2 = 0;
	double temp3 = 0;
	double temp4 = 0;

	int i;

	for (i = 0; i < n/4-1; i++) {
		sum1 += temp1;
		temp1 = *(a + 0) * *(b + 0);

		sum2 += temp2;
		temp2 = *(a + 1) * *(b + 1);

		sum3 += temp3;
		temp3 = *(a + 2) * *(b + 2);

		sum4 += temp4;
		temp4 = *(a + 3) * *(b + 3);

		 
		a += 4; b += 4;
	}
	s = sum1 + sum2 + sum3 + sum4;
	// printf("s, unrolled 4: %f\n", s);
}


int main(int argc, char** argv) {
	const long NREPEATS = 10;
	const long PFIRST = 100;
	const long PLAST = 550;
	const long PINC = 50;

	printf(" Dimension       Time    Gflop/s       GB/s\n");
	for (long p = PFIRST; p < PLAST; p += PINC) {

		long n = p * 1000000;
		double* a = (double*) malloc(n * sizeof(double));
		double* b = (double*) malloc(n * sizeof(double)); 

		// Initialize matrices
		for (long i = 0; i < n; i++) a[i] = drand48();
		for (long i = 0; i < n; i++) b[i] = drand48();


		Timer t1;
		t1.tic();
		for (long rep = 0; rep < NREPEATS; rep++) {
			// baseline(n,a,b);
			// modified_1(n,a,b);
			// modified_2(n,a,b);
			// modified_3(n,a,b);
			mod_unroll4(n,a,b);
		}

		double time1 = t1.toc();
		double flops1 = 2 * n * NREPEATS/ 1e9 / time1;
		double bandwidth1 = 3 * n * NREPEATS * sizeof(double) / 1e9 / time1;
		printf("%10lu %10f %10f %10f\n", n, time1, flops1, bandwidth1);

		free(a);
		free(b);

  }

  return 0;
}