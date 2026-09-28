#include "tsani.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "toolbox.h"
#include <lab021_2.h>

static int panelHandle;

#define VX_MIN 0.0
#define VX_MAX 5.0
#define VY_MIN 0.0
#define VY_MAX 5.0

#define TRAJ_SIZE 50

static double trajX[TRAJ_SIZE];
static double trajY[TRAJ_SIZE];
static int trajCount = 0;

double VoltageToCoord(double voltage, double vMin, double vMax) {
	double coord = 2.0 * (voltage-vMin)/(vMax-vMin) - 1.0;
	
	if (coord > 1.0) coord = 1.0;
	if (coord < -1.0) coord = -1.0;
	return coord;
}


int main(int argc, char *argv[]) {
	int error = 0;
	
	nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "lab021_2.uir", PANEL));

	ni6251Slot(2); 
	
	trajCount = 0;
	for (int i = 0; i < TRAJ_SIZE; i++) {
		trajX[i] = 0.0;
		trajY[i] = 0.0;
	}
	

	SetCtrlVal(panelHandle, PANEL_AI2_VAL, 0.0);
	SetCtrlVal(panelHandle, PANEL_AI3_VAL, 0.0);
    SetCtrlVal(panelHandle, PANEL_X_VAL, 0.0);
	SetCtrlVal(panelHandle, PANEL_Y_VAL, 0.0);


	SetAxisScalingMode(panelHandle, PANEL_GRAPH, VAL_BOTTOM_XAXIS, VAL_MANUAL,-1.1, 1.1);
	SetAxisScalingMode(panelHandle, PANEL_GRAPH, VAL_LEFT_YAXIS, VAL_MANUAL,-1.1, 1.1);
	
	
	
	
	errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
	ni6251Close();
	DiscardPanel(panelHandle);
	return 0;

}

int CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}


int CVICALLBACK TimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_TIMER_TICK) return 0;
	
	double rawX = 0.0;
	double rawY = 0.0;
	analogIn(2, &rawX);
	analogIn(3, &rawY);
	
	SetCtrlVal(panelHandle, PANEL_AI2_VAL, rawX);
	SetCtrlVal(panelHandle, PANEL_AI3_VAL, rawY);	

	double x = -VoltageToCoord(rawX, VX_MIN, VX_MAX)-0.08;
	double y = VoltageToCoord(rawY, VY_MIN, VY_MAX)+0.1;
	
	
	if (trajCount < TRAJ_SIZE) {
		trajX[trajCount] = x;
		trajY[trajCount] = y;
		trajCount++;
	} else {
		for (int i = 0; i < TRAJ_SIZE - 1; i++) {
			trajX[i] = trajX[i+1];
			trajY[i] = trajY[i+1];
		}
		trajX[TRAJ_SIZE-1] = x;
		trajY[TRAJ_SIZE-1] = y;
	}
	
	SetCtrlVal(panelHandle, PANEL_X_VAL, x);
	SetCtrlVal(panelHandle, PANEL_Y_VAL, y);
	
	DeleteGraphPlot(panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
	PlotXY(panelHandle, PANEL_GRAPH, trajX, trajY, trajCount, VAL_DOUBLE, VAL_DOUBLE, VAL_FAT_LINE, VAL_SOLID_SQUARE, VAL_DOT, 1, VAL_GREEN);
				
		
		
	return 0;
}

















