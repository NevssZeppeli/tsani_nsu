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
#define  PANEL_GRAPH2                     2
#define  PANEL_GRAPH                      3
#define  PANEL_Ampl                       4
#define  PANEL_Freq                       5
#define  PANEL_Noise                      6
#define  PANEL_Save                       7       /* callback function: Save1 */
#define  PANEL_TIMER                      8       /* callback function: Timer1 */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK panelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Timer1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
