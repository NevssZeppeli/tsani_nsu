#include "tsani.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "toolbox.h"
#include <lab021_1.h>

static int panelHandle;

int main(int argc, char *argv[]) {
	int error = 0;
	
	nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "lab021_1.uir", PANEL));


	ni6251Slot(2);
	
	analogOut(0, 0.0);
	analogOut(1, 0.0);

	SetCtrlVal(panelHandle, PANEL_AO0, 0.0);
	SetCtrlVal(panelHandle, PANEL_AI0, 0.0);
    SetCtrlVal(panelHandle, PANEL_AI1, 0.0);


	errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
	analogOut(0, 0.0);
	analogOut(1, 0.0);
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


int CVICALLBACK AOSlideCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_COMMIT && event != EVENT_VAL_CHANGED) return 0;

	double val = 0.0;
	GetCtrlVal(panelHandle, PANEL_AO0, &val);
	
	analogOut(0, val);
	analogOut(1, val);
	return 0;
}

int CVICALLBACK TimerCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_TIMER_TICK) return 0;
	
	double v0 = 0.0;
	double v1 = 0.0;
	
	analogIn(0, &v0);
	analogIn(1, &v1);
	
	SetCtrlVal(panelHandle, PANEL_AI0, v0);
	SetCtrlVal(panelHandle, PANEL_AI1, v1); 

	return 0;
}
