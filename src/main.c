/* 
 *  main.c - Application main entry point 
 */
#include <stdio.h>
#include <string.h>

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#include <lvgl.h>
#include <lvgl_input_device.h>

#include "display.h"
#include "buttons.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/

#define STACKSIZE 1024
#define PRIORITY 7

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
static int set_backlight_on(void)
{
#if defined(CONFIG_BACKLIGHT_FIRMWARE)
 
    #define BACKLIGHT_GPIO_DEV  DT_PHANDLE_BY_IDX(DT_ALIAS(backlight), gpios, 0)
    #define BACKLIGHT_PIN       DT_GPIO_PIN(DT_ALIAS(backlight), gpios)
    #define BACKLIGHT_FLAGS     DT_GPIO_FLAGS(DT_ALIAS(backlight), gpios)

    static const struct device * gpio;

    LOG_INF("Backlight firmware configured");

    gpio = DEVICE_DT_GET(BACKLIGHT_GPIO_DEV);
    if (!gpio) {
        return -1;
    }

    gpio_pin_configure(gpio, BACKLIGHT_PIN, GPIO_OUTPUT);
    gpio_pin_set(gpio, BACKLIGHT_PIN, 1);

    return 0;

#elif defined(CONFIG_BACKLIGHT_MANUAL)

    LOG_INF("Backlight manually configured");
    return 0;

#else

    LOG_ERR("Set Backlight configuration method");
    return 0     

#endif
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*---------------------------------------------------------------------------*/
void main_thread(void * id, void * unused1, void * unused2)
{
    LOG_INF("%s", __func__);

    if (set_backlight_on() < 0) {
        LOG_ERR("Backlight failure: aborting");
        return;
    }

    buttons_init();

    if (display_init() < 0)
        return;
}

K_THREAD_DEFINE(main_id, STACKSIZE, main_thread, 
                NULL, NULL, NULL, PRIORITY, 0, 0);
