#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"


#include "chip/osal.h"
#include "chip/os_port.h"

#define MODULE_NAME "MAIN: "
struct chip_os_task demo_task;

void test_func()
{
    while(1)
    {
        ESP_LOGI(MODULE_NAME, "Hello there");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void app_main(void)
{
    chip_os_task_init(&demo_task, "demo task", &test_func, NULL, 10, 1024 * 3);
    while(1)
    {
        ESP_LOGI(MODULE_NAME, "App main");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
