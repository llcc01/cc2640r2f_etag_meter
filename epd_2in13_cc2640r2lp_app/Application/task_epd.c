#include <stdio.h>
#include <string.h>

#include <icall.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/knl/Queue.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Task.h>
#include <util.h>
#include <xdc/std.h>
/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

// #include "board.h"
#include "epd_driver.h"
#include "task_epd.h"

#define EPD_TASK_PRIORITY 1
#define EPD_TASK_STACK_SIZE 512
Task_Struct EPDTask = {0};
Char EPDTaskStack[EPD_TASK_STACK_SIZE] = {0};

// Entity ID globally used to check for source and/or destination of messages
static ICall_EntityID selfEntity;

// Event globally used to post local events and pend on system and
// local events.
static ICall_SyncHandle syncEvent;

// TBD: need this?
uint32_t epoch_time = 0;

// Event used to control the EPD thread
Event_Struct EPDEvent;
// Event_Handle hEPDEvent;

// #define EPDTASK_EVENT_RX_REQUEST        Event_Id_00
#define EPDTASK_EVENT_PERIODIC Event_Id_02

#define EPDTASK_EVENT_ALL (EPDTASK_EVENT_PERIODIC)

// static Clock_Struct periodicClock;

// static void handle_cmd();
void TaskEPD_taskFxn(UArg a0, UArg a1);
// static void post_epd_response(uint8_t *buf, uint16_t len);

void TaskEPD_createTask(void) {
  Task_Params taskParams;

  // Configure task
  Task_Params_init(&taskParams);
  taskParams.stack = EPDTaskStack;
  taskParams.stackSize = EPD_TASK_STACK_SIZE;
  taskParams.priority = EPD_TASK_PRIORITY;

  Task_construct(&EPDTask, TaskEPD_taskFxn, &taskParams, NULL);
}

void EPDTask_Update(void) { Event_post(syncEvent, EPDTASK_EVENT_PERIODIC); }

void EPDTask_clockHandler(UArg arg) { Event_post(syncEvent, arg); }

void TaskEPD_taskInit(void) {
  // Register the current thread as an ICall dispatcher application
  // so that the application can send and receive messages.
  ICall_registerApp(&selfEntity, &syncEvent);

  // second period timer
  // Util_constructClock(&periodicClock, EPDTask_clockHandler,
  //                    1000, 0, false, EPDTASK_EVENT_PERIODIC);

  u8g2_t u8g2;
  u8g2_Setup_ssd1680_250x122_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi,
                                      u8x8_cc2640_gpio_and_delay);
  u8g2_InitDisplay(&u8g2);

  u8g2_ClearBuffer(&u8g2);

  u8g2_DrawCircle(&u8g2, 64, 32, 10, U8G2_DRAW_ALL);

  u8g2_SendBuffer(&u8g2);

  while (1) {
    Task_sleep(1000);
  }

  // init EPD
  EPD_Init();

  // start timer
  // Util_startClock(&periodicClock);
}

void TaskEPD_taskFxn(UArg a0, UArg a1) {
  TaskEPD_taskInit();

  while (1) {
    UInt events;
    events = Event_pend(syncEvent, Event_Id_NONE, EPDTASK_EVENT_ALL,
                        ICALL_TIMEOUT_FOREVER);

    if (events & EPDTASK_EVENT_PERIODIC) {
      if (EPD_Update()) {
        // Util_startClock(&periodicClock);
      }
    }
  }
}
