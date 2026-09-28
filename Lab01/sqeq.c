#include <stdio.h>
#include <math.h>

void calcRoots(float A, float B, float C, float *pD, float *pValue1, float *pValue2) {
	*pD = B*B - 4*A*C;
	if (A == 0) {*pValue1 = *pValue2 = 0; return;}
	if (*pD >= 0) {
		*pValue1 = (-B + sqrt(*pD)) / (2 * A);
		*pValue2 = (B + sqrt(*pD)) / (2 * A);
	} else {
		*pValue1 = -B/(2 * A);		//Re
		*pValue2 = sqrt(-*pD)/(2 * A); //Im
	}
}




void main() {
	float A, B, C;
	float D, x1, x2;
	char ch;
	
	do {
		printf("Square equation");
		printf("\nInput A, B, C coeffs:\n");
		scanf("%f %f %f", &A, &B, &C);

		calcRoots(A, B, C, &D, &x1, &x2);
	
		int type = (A == 0) ? ((B == 0) ? 0 : 1) : 2; 
		// A = 0 -  not sq eq, A, B = 0 - degenerate,
		// A != 0, B = 0 - linear,
		// A, B, C != 0 - usual square equation.
	
		switch(type) {
			case 0:
				printf(C == 0 ? "Infinite number of roots\n": "no roots\n");
				break;
			case 1: 
				printf("Linear equation, %.2f\n", -C/B);
				break;
			case 2:
				int disc_type = (D > 0) ? 1 : ((D == 0) ? 2 : 3);
				switch(disc_type) {
				case 1: printf("Two real roots:\nx1 = %.2f, x2 = %.2f\n", x1, x2); break;
				case 2: printf("One root: x1 = x2 = %.2f\n", x1); break;
				case 3: printf("Two complex roots:\nx1 = %.2f + %.2fi\nx2 = %.2f - %.2fi\n", x1, x2, x1, x2); break;
				}
			printf("Top of parabola: (%.2f, %.2f)\n\n", -B/(2*A), A*pow(-B/(2*A), 2) + B * (-B/(2*A))+C);  
		} 
		ch = getchar();
		printf("----------\n");
	}   while (ch != 'q' && ch != 'Q');
}
