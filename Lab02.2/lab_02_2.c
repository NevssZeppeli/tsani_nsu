#include "tsani.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "toolbox.h"
#include <lab02_2.h>

static int panelHandle; 

int main (int argc, char *argv[])
{
    int error = 0;
	
    nullChk(InitCVIRTE(0, argv, 0));
	errChk (panelHandle = LoadPanel (0, "lab02_2.uir", PANEL));
	
	ni6251Slot(2);
	
	analogOut(0, 0.0);
	
	SetCtrlVal(panelHandle, PANEL_ADC_METER, 0.0);
	SetCtrlVal(panelHandle, PANEL_DAC_SLIDE, 0.0);
	
	/* initialize and load resources */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
	/* clean up */
	analogOut(0, 0.0);
	ni6251Close();
    DiscardPanel (panelHandle);
	return 0;
}



int CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2) {
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}

int CVICALLBACK MeasureCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)  {
	if (event != EVENT_COMMIT) return 0;
	
	double measured = 0.0;
	
	if (analogIn(0, &measured) != 0) {
		MessagePopup("Error", "Cannot read ADC");
		return 0;
	}

	SetCtrlVal(panelHandle, PANEL_ADC_METER, measured);
	return 0;
}

int CVICALLBACK DacSlideCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_COMMIT && event != EVENT_VAL_CHANGED) return 0;
	

	double val = 0.0;
	GetCtrlVal(panelHandle, PANEL_DAC_SLIDE, &val);
	SetCtrlVal(panelHandle, PANEL_DAC_VALUE, val);
	analogOut(0, val);
	return 0;

}
