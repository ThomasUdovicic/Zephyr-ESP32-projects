#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/devicetree.h>


static const struct gpio_dt_spec led    = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);

int main(void)
{
    if (!device_is_ready(led.port)) {
        printk("LED device not ready\n");
        return 0;
    }

    if (!device_is_ready(button.port)) {
        printk("Button device not ready\n");
        return 0;
    }

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret) {
        printk("Failed to configure LED: %d\n", ret);
        return 0;
    }

    ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
    if (ret) {
        printk("Failed to configure button: %d\n", ret);
        return 0;
    }

    while (1) {
        int v = gpio_pin_get_dt(&button);
        if (v < 0) {
            printk("Button read failed: %d\n", v);
            k_msleep(100);
            continue;
        }

        gpio_pin_set_dt(&led, v);

        k_msleep(10);
    }
}
