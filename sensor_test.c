#include "sensor_manager.h"
#include "stdio.h"
struct sensor_t test_sensor;
int test_sensor_init(void)
{
    printf("test sensor init\n");
}
int test_sensor_configurate(struct sensor_config_t config)
{
    printf("test sensor configurate\n");
}
int test_sensor_suspend(void)
{
    printf("test sensor suspend\n");
}
int test_sensor_resume(void)
{
    printf("test sensor resume\n");
}
struct sensor_event_t test_sensor_get_event(void)
{
    printf("test sensor get event\n");
}
int test_sensor_poll(struct sensor_event_t *event)
{
    printf("test sensor get poll\n");
}
void test_sensor_register(void)
{
    test_sensor.type = SENSOR_TYPE_ACCELEROMETER;
    test_sensor.name = "test";
    test_sensor.period = 100;
    test_sensor.init = test_sensor_init;
    test_sensor.configurate = test_sensor_configurate;
    test_sensor.suspend = test_sensor_suspend;
    test_sensor.resume = test_sensor_resume;
    test_sensor.get_event = test_sensor_get_event;
    test_sensor.poll = test_sensor_poll;
    sensor_manager.register_sensor(&test_sensor);
}
void main(void)
{
    struct sensor_t *sensor;
    struct sensor_event_t event;
    struct sensor_config_t config;
    test_sensor_register();
    sensor = sensor_manager.get_default_sensor(SENSOR_TYPE_ACCELEROMETER);
    //sensor = sensor_manager.get_default_sensor(3);
    if(sensor != NULL) {
        printf("sensor is %d manager is %d\n", sizeof(struct sensor_t), sizeof(struct sensor_manager_t));
        sensor->init();
        sensor->configurate(config);
        sensor->suspend();
        sensor->resume();
        event = sensor->get_event();
        sensor->poll(&event);
    } else {
        printf("NULL!\n");
    }
    printf("sensor_hal test program!\n");
}
