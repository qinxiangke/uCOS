/*
***********************************************************************************************
* INCLUDE FILES
***********************************************************************************************
*/
#include <app_cfg.h> //(1)
#include <bsp.h>
#include <os.h>
/*
***********************************************************************************************
* LOCAL GLOBAL VARIABLES
***********************************************************************************************
*/
static OS_TCB AppTaskStartTCB; //(2)
static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE]; //(3)
/*
***********************************************************************************************
* FUNCTION PROTOTYPES
***********************************************************************************************
*/
static void AppTaskStart (void *p_arg); //(4)

void main (void)
{
  OS_ERR err;
  BSP_IntDisAll(); //(1)
  OSInit(&err); //(2)
  if (err != OS_ERR_NONE) {
    /* Something didn’t get initialized correctly ... */
    /* ... check os.h for the meaning of the error code, see OS_ERR_xxxx */
  }
  OSTaskCreate((OS_TCB *)&AppTaskStartTCB, //(3)
  (CPU_CHAR *)”App Task Start”, //(4)
  (OS_TASK_PTR )AppTaskStart, //(5)
  (void *)0, //(6)
  (OS_PRIO )APP_TASK_START_PRIO, //(7)
  (CPU_STK *)&AppTaskStartStk[0], //(8)
  (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10, //(9)
  (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,// (10)
  (OS_MSG_QTY )0,
  (OS_TICK )0,
  (void *)0,
  (OS_OPT )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR), //(11)
  (OS_ERR *)&err); (12)
  if (err != OS_ERR_NONE) {
    /* The task didn’t get created. Lookup the value of the error code ... */
   /* ... in os.h for the meaning of the error */
  }
  OSStart(&err); (13)
  if (err != OS_ERR_NONE) {
   /* Your code is NEVER supposed to come back to this point. */
  }
}
static void AppTaskStart (void *p_arg) //(1)
{
	OS_ERR err;
	p_arg = p_arg;
	BSP_Init(); //(2)
	CPU_Init(); //(3)
	BSP_OS_TickInit();// (4)
	BSP_LED_Off(0); //(5)
	while (1) { //(6)
		BSP_LED_Toggle(0); //(7)
		OSTimeDlyHMSM((CPU_INT16U) 0, //(8)
						(CPU_INT16U) 0,
						(CPU_INT16U) 0,
						(CPU_INT32U)100,
						(OS_OPT )OS_OPT_TIME_HMSM_STRICT,
						(OS_ERR *)&err);
		/* Check for ‘err’ */
	}
}
