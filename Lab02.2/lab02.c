#include "tsani.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "toolbox.h"
#include <lab02_1.h>

static int panelHandle;

void UpdateIndicators(unsigned char state) {
	SetCtrlVal(panelHandle, PANEL_LED0, (state>>0) & 1 ? 1 : 0);
	SetCtrlVal(panelHandle, PANEL_LED1, (state>>1) & 1 ? 1 : 0); 
	SetCtrlVal(panelHandle, PANEL_LED2, (state>>2) & 1 ? 1 : 0); 
	SetCtrlVal(panelHandle, PANEL_LED3, (state>>3) & 1 ? 1 : 0); 
	SetCtrlVal(panelHandle, PANEL_LED4, (state>>4) & 1 ? 1 : 0); 
	SetCtrlVal(panelHandle, PANEL_LED5, (state>>5) & 1 ? 1 : 0); 
	SetCtrlVal(panelHandle, PANEL_LED6, (state>>6) & 1 ? 1 : 0); 
	SetCtrlVal(panelHandle, PANEL_LED7, (state>>7) & 1 ? 1 : 0); 
}

int main (int argc, char *argv[])
{
    int error = 0;
    unsigned char state;
	
	
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "lab02_1.uir", PANEL));
    
	ni6251Slot(2);
	
	portMask(2, 0x07);
	portOut(2, 0x01);
	
	portMask(0, 0xff);
	portOut(0, 0x00);
	
	// checking
	/*
	printf("Line 0\n"); portOut(0, 0x01); Delay(2.0); portOut(0, 0x00);
	printf("Line 1\n"); portOut(0, 0x02); Delay(2.0); portOut(0, 0x00);
	printf("Line 2\n"); portOut(0, 0x04); Delay(2.0); portOut(0, 0x00);
	printf("Line 3\n"); portOut(0, 0x08); Delay(2.0); portOut(0, 0x00);
	printf("Line 4\n"); portOut(0, 0x10); Delay(2.0); portOut(0, 0x00);
	printf("Line 5\n"); portOut(0, 0x20); Delay(2.0); portOut(0, 0x00);
	printf("Line 6\n"); portOut(0, 0x40); Delay(2.0); portOut(0, 0x00);
	printf("Line 7\n"); portOut(0, 0x80); Delay(2.0); portOut(0, 0x00);
	*/
	
	portIn(0, &state);
	UpdateIndicators(state);
	
	
	//SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_ENABLED, 0);
	
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());

Error:
	ni6251Close();
    /* clean up */
    DiscardPanel (panelHandle);
    
	
	
	return 0;
}

int CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}


int CVICALLBACK Timer1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_TIMER_TICK) return 0;
	
	unsigned char state, new_state;
	portIn(0, &state);
	
	new_state = (unsigned char)((state << 1) | (state >> 7)); // shifting 
	
	portOut(0, new_state);
	UpdateIndicators(new_state);
	
	return 0;
}

int CVICALLBACK LEDButtonCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_COMMIT) return 0;
	
	unsigned char state;
	portIn(0, &state);
	
	switch (control) {
		case PANEL_BUTTON0: state ^= (1<<0); break;
		case PANEL_BUTTON1: state ^= (1<<1); break;
		case PANEL_BUTTON2: state ^= (1<<2); break;
		case PANEL_BUTTON3: state ^= (1<<3); break;
		case PANEL_BUTTON4: state ^= (1<<4); break;
		case PANEL_BUTTON5: state ^= (1<<5); break;
		case PANEL_BUTTON6: state ^= (1<<6); break;
		case PANEL_BUTTON7: state ^= (1<<7); break;
	}

	portOut(0, state);
	UpdateIndicators(state);
	
	return 0;
}

int CVICALLBACK RunningLightCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2) {
	if (event != EVENT_COMMIT) return 0; 
	
	int val = 0;
	GetCtrlVal(panelHandle, PANEL_RUNNING_LIGHT, &val);
	SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_ENABLED, val);



	return 0;
}










