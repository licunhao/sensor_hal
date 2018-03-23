#ifndef __SENSOR_MANAGER_H__
#define __SENSOR_MANAGER_H__
#include "sensor.h"
struct sensor_manager_t {
    int (*register_sensor)(struct sensor_t *sensor);
    int (*unregister_sensor)(struct sensor_t *sensor);
    struct sensor_t *(*get_default_sensor)(int type);
    int (*poll_sensors)(struct sensor_event_t **event);
    int (*sensors_suspend)(void);
    int (*sensors_resume)(void);
};
extern struct sensor_manager_t sensor_manager;
#endif
