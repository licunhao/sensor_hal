#ifndef __SENSOR_H__
#define __SENSOR_H__

#include "sensor_type.h"
struct sensor_vec_t {
    union {
        float v[3];
        struct {
            float x;
            float y;
            float z;
        };
        struct {
            float azimuth;
            float pitch;
            float roll;
        };
    };
};

struct sensor_raw_vec_t {
    float x;
    float y;
    float z;
};

struct sensor_event_t {
    int type;
    union {
        float data[16];
        struct sensor_vec_t   acceleration;
        struct sensor_raw_vec_t raw_acceleration;
        struct sensor_vec_t   magnetic;
        struct sensor_raw_vec_t raw_magnetic;
        struct sensor_vec_t   orientation;
        struct sensor_vec_t   gyro;
        struct sensor_raw_vec_t raw_gyro;
        float           temperature;
        float           distance;
        float           light;
        float           pressure;
        float           relative_humidity;
    };
};

enum sensor_rate_e {
    SENSOR_RATE_LOW = 0,
    SENSOR_RATE_NORMAL,
    SENSOR_RATE_HIGH,
};
enum sensor_mode_e {
    SENSOR_MODE_IDLE = 0,
    SENSOR_MODE_RUN,
};
struct sensor_config_t {
    enum sensor_rate_e rate;
    enum sensor_mode_e mode;
    int sensor_range;
};
struct sensor_t {
    struct sensor_t *next;
    struct sensor_t *prev;
    int type;
    int period;
    struct sensor_config_t config;
    char *name;
    int (*init)(void);
    int (*configurate)(struct sensor_config_t config);
    int (*suspend)(void);
    int (*resume)(void);
    struct sensor_event_t (*get_event)(void);
    int (*poll)(struct sensor_event_t *event);
};

#endif
