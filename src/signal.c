#include <stdio.h>
#include <FreeRTOS.h>
#include <task.h>
#include "signaling.h"

void signal_handle_calculation(SemaphoreHandle_t request,
                               SemaphoreHandle_t response,
                               struct signal_data *data)
{
    printf("Handle : Waiting for request\n");
    xSemaphoreTake(request, portMAX_DELAY);
    printf("Handle : Handling calculation\n");
    data->output = data->input + 5;
    vTaskDelay(10);
    printf("Handle : Done with calculation; I: %d, O: %d\n", data->input, data->output);
    xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request,
                                    SemaphoreHandle_t response,
                                    struct signal_data *data)
{
    printf("Request: Give to worker\n");
    xSemaphoreGive(request);
    printf("Request: Waiting for results\n");
    BaseType_t res = xSemaphoreTake(response, 100);
    printf("Request: Result ready\n");
    return res;
}