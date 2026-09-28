/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2026. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: panelCB */
#define  PANEL_BUTTON2                    2       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON3                    3       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON4                    4       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON0                    5       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON1                    6       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON5                    7       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON6                    8       /* callback function: LEDButtonCB */
#define  PANEL_BUTTON7                    9       /* callback function: LEDButtonCB */
#define  PANEL_LED0                       10
#define  PANEL_LED1                       11
#define  PANEL_LED2                       12
#define  PANEL_LED3                       13
#define  PANEL_LED4                       14
#define  PANEL_LED5                       15
#define  PANEL_LED6                       16
#define  PANEL_LED7                       17
#define  PANEL_TIMER                      18      /* callback function: Timer1 */
#define  PANEL_RUNNING_LIGHT              19      /* callback function: RunningLightCB */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK LEDButtonCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RunningLightCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Timer1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
