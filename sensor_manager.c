#include <stdio.h>
#include <string.h>
#include "sensor_manager.h"

static struct sensor_t *sensor_list = NULL;

int sensor_register(struct sensor_t *sensor)
{
    if(sensor == NULL)
        return -1;

    if(sensor_list == NULL) {
        sensor->prev = sensor->next = sensor;
    } else {
        sensor_list->prev->next = sensor;
        sensor->prev = sensor_list->prev;

        sensor_list->prev = sensor;
        sensor->next = sensor_list;
    }

    sensor_list = sensor;

    return 0;
}

int sensor_unregister(struct sensor_t *sensor)
{
    if(sensor == NULL)
        return -1;

    sensor->next->prev = sensor->prev;
    sensor->prev->next = sensor->next;

    if (sensor == sensor_list) {
        if (sensor->next == sensor) sensor_list = NULL;
        else sensor_list = sensor->next;
    }

    sensor->next = sensor->prev = sensor;
    return 0;
}

struct sensor_t *get_default_sensor(int type)
{
    struct sensor_t *sensor = sensor_list;
    if (sensor == NULL) return NULL;

    do {
        if(sensor->type == type) return sensor;

        sensor = sensor->next;
    } while(sensor != sensor_list);

    return NULL;
}

int sensors_poll(struct sensor_event_t **event)
{
    struct sensor_t *sensor = sensor_list;
    if (sensor == NULL) return -1;


    if(*event == NULL || event == NULL) return -1;


    do {
        sensor->poll(*event);
        *event++;
        sensor = sensor->next;
    } while(sensor != sensor_list);
    return 0;
}

int sensors_suspend(void)
{
    struct sensor_t *sensor = sensor_list;
    if (sensor == NULL) return -1;

    do {
        sensor->suspend();
        sensor = sensor->next;
    } while(sensor != sensor_list);
    return 0;
}

int sensors_resume(void)
{
    struct sensor_t *sensor = sensor_list;
    if (sensor == NULL) return -1;

    do {
        sensor->resume();
        sensor = sensor->next;
    } while(sensor != sensor_list);
    return 0;
}

struct sensor_manager_t sensor_manager = {
    sensor_register,
    sensor_unregister,
    get_default_sensor,
    sensors_poll,
    sensors_suspend,
    sensors_resume,
};
