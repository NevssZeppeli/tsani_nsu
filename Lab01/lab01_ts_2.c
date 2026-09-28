//==============================================================================
//
// Title:       lab01_ts_2
// Purpose:     A short description of the application.
//
// Created on:  14.09.2026 at 9:47:02 by TC.
// Copyright:   ANY. All Rights Reserved.
// Author: Nevss
//
//==============================================================================

//==============================================================================
// Include files

#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include <tsani.h>
#include "lab01_ts_2.h"
#include "toolbox.h"
#include <analysis.h>

static int panelHandle;

double A[1000]; // data
double F[1000]; // Fourier
double U_0 = 5.0; // Initial ampl
double freq = 1.0; // Freq
double noiselevel = 0; // Initial noise level

void createSignal(double ampl, double freq, double noiselevel) {
	double R = fabs(noiselevel);
	for (int t = 0; t < 1000; t++){
		A[t] = ampl * sin(2*3.1415926 * freq * t/1000.0) + Random(-R, R); //A(t) = Ampl * sin(2pi*f*t / 1000) +- Random
	}
}

void createSpectrum() {
	double re[1000];
	double im[1000];
	
	for (int t = 0; t < 1000; t++) {
		re[t] = A[t];
		im[t] = 0.0;
	}
	
	FFT(re, im, 1000);
	
	for (int t = 0; t < 1000; t++) {
		F[t] = sqrt(re[t]*re[t] + im[t]*im[t]);
	}
}



void DrawGraph() {
	SetAxisScalingMode(panelHandle, PANEL_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, 1000); // x scale
	SetAxisScalingMode(panelHandle, PANEL_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL, -30, 30);  // y scale
	DeleteGraphPlot(panelHandle, PANEL_GRAPH,-1, VAL_IMMEDIATE_DRAW); // delete old fig
	PlotY(panelHandle, PANEL_GRAPH, A, 1000, VAL_DOUBLE, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_DOT, 1, VAL_GREEN); // draw new fig
}

void DrawGraph2() {
	SetAxisScalingMode(panelHandle, PANEL_GRAPH2, VAL_BOTTOM_XAXIS, VAL_MANUAL, 0, 1000); // x scale
	SetAxisScalingMode(panelHandle, PANEL_GRAPH2, VAL_LEFT_YAXIS, VAL_MANUAL, 0, 500);  // y scale
	DeleteGraphPlot(panelHandle, PANEL_GRAPH2,-1, VAL_IMMEDIATE_DRAW); // delete old fig
	PlotY(panelHandle, PANEL_GRAPH2, F, 1000, VAL_DOUBLE, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_DOT, 1, VAL_RED); // draw new fig
}

void Save() {
	FILE *pF = fopen("save_graph.txt", "w");
	if (pF == NULL) {
		return; // if we can't open file - just return nothing
	}
	for (int i = 0; i < 1000; i++) {
		fprintf(pF, "%d\t%f\n", i, A[i]); // if we found file, we can write data there	
	}
	fclose(pF);
	printf("File saved to save_graph.txt\n");
}

int main (int argc, char *argv[])
{
    int error = 0;
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "lab01_ts_2.uir", PANEL));
    
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}

//==============================================================================
// UI callback function prototypes

int CVICALLBACK panelCB(int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}

int CVICALLBACK Timer1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	switch(event) {
		case EVENT_TIMER_TICK:
			GetCtrlVal(panelHandle, PANEL_Ampl, &U_0);
			GetCtrlVal(panelHandle, PANEL_Freq, &freq);
			GetCtrlVal(panelHandle, PANEL_Noise, &noiselevel);
	
			createSignal(U_0, freq, noiselevel);
			DrawGraph();
			
			createSpectrum();
			DrawGraph2();
			break;
		
		case EVENT_DISCARD:
			break;
	}			
	return 0;
}

int CVICALLBACK Save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	switch(event) {
		case EVENT_COMMIT:
			Save();
			break;
		case EVENT_LEFT_CLICK:
		case EVENT_RIGHT_CLICK:
		case EVENT_GOT_FOCUS:
		case EVENT_DISCARD:
			break;
	}
	return 0;
}    
