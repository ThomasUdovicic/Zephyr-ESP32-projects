#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

#define SLEEP_MS 100

/* Use the board’s “led0” alias from the devicetree */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main(void)
{
    if (!device_is_ready(led.port)) {
        printk("LED device not ready\n");
        return 0;
    }

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret) {
        printk("Failed to configure LED: %d\n", ret);
        return 0;
    }

    while (1) {
        gpio_pin_toggle_dt(&led);
        printk("tick\n");
        k_msleep(SLEEP_MS);
    }
}
