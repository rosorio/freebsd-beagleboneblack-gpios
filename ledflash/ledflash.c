#include <stdio.h>
#include <unistd.h>
#include <libgpio.h>
#include <signal.h>

gpio_handle_t handle_red, handle_yellow, handle_green;
void signal_handler(int sig)
{
    gpio_pin_set(handle_red, 26, 0);
    gpio_pin_set(handle_yellow, 14, 0);
    gpio_pin_set(handle_green, 1, 0);

    gpio_close(handle_red);
    gpio_close(handle_yellow);
    gpio_close(handle_green);
    exit(0);
}


int main()
{
    int pinv;
    int counter =0;

    signal(SIGINT, signal_handler);

    handle_red    = gpio_open_device("/dev/gpioc0");
    handle_yellow = gpio_open_device("/dev/gpioc1");
    handle_green  = gpio_open_device("/dev/gpioc2");

    while(1) {
        gpio_pin_set(handle_red, 26, (counter % 4) == 1 ? 1 : 0);
        gpio_pin_set(handle_yellow, 14, (counter % 4) == 2 ? 1 : 0);
        gpio_pin_set(handle_green, 1, (counter % 4) == 3 ? 1 : 0);
        counter++;
        usleep(50000);
    }
    return 0;
}
