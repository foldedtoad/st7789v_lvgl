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

    gpio = DEVICE_DT_GET(BACKLIGHT_GPIO_DEV);
    if (!gpio) {
        LOG_ERR("Backlight failure");
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

int main(void)
{
    LOG_INF("%s", __func__);

    if (set_backlight_on() < 0) {
        return -1;
    }

    buttons_init();

    if (display_init() < 0)
        return -2;

    return 0;
}
