#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "chip/osal.h"
#include "chip/os_port.h"
#include "../actor-framework/include/actor.h"

#define MODULE_NAME             "MAIN: "
#define TEST_FRAMEWORK          1
#define TEST_DYNAMIC_EVT        0


struct chip_os_task demo_task;

/***************************************************************************************************/
/* System active objects --------------------------------------------------------------*/
/* Definitions for Running_Actor */

Active Actor_Sys;

static eStatus Sys_StateRunning(StateMachine_t* const me, const EvtHandle_t p_event)
{
    return STATUS_IGNORE;

}
static eStatus Sys_StateSleep(StateMachine_t* const me, const EvtHandle_t p_event)
{
    switch (p_event->sig)
    {
        case INIT_SIG:
        {
            ESP_LOGI("ACTOR", "INIT");
            return STATUS_HANDLE;
        }

        case SIG_IDLE:
        {
            ESP_LOGI("ACTOR", "INIT");
            return STATUS_HANDLE;
        }
        
    
        default:
            return STATUS_IGNORE;
            
    }
    return STATUS_IGNORE;
}


/***************************************************************************************************/

void test_func()
{
    Evt test_me = {
        .sig = SIG_IDLE
    };

    while(1)
    {
        ESP_LOGI("TEST FUNC", "ENTER5");
        // vTaskDelay(pdMS_TO_TICKS(500));
        Active_post(&Actor_Sys, &test_me);
        Active_post(&Actor_Sys, &test_me);

        ESP_LOGI("TEST FUNC", "EXIT5");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Default_Task(void *argument)
{

#if TEST_FRAMEWORK
	#if TEST_DYNAMIC_EVT
	/* ******************************************************* */
	test_evt* test_me = (test_evt*)Event_New(SIG_IDLE, sizeof(test_evt));
	for(uint8_t idx=0; idx<10; idx++)
	{
		test_me->imvip[idx] = idx+10;
	}
	Active_post(&Actor_Sys, test_me);

	/* ******************************************************* */
	#else
	Evt test_me = {
			.sig = SIG_IDLE
	};
	Active_post(&Actor_Sys, &test_me);

	#endif  /* End of TEST_DYNAMIC_EVT */
#endif  /* End of TEST_FRAMEWORK */
}

void app_main(void)
{
    Framework_Init();
    Active_Init(&Actor_Sys, &Sys_StateSleep, 11, 1024*4, (void*) 0 ,  (void*) 0 , 20);
    chip_os_task_init(&demo_task, "demo task", &test_func, NULL, 10, 1024 * 3);
    
    while(1)
    {
        ESP_LOGI(MODULE_NAME, "App main");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
