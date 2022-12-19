#include <stdio.h>
#include <unistd.h>
#include <libgpio.h>
#include <signal.h>

gpio_handle_t handle_0, handle_1, handle_2;
void signal_handler(int sig)
{
    gpio_pin_set(handle_2,  4, 0);
    gpio_pin_set(handle_1, 12, 0);
    gpio_pin_set(handle_0, 26, 0);
    gpio_pin_set(handle_1, 14, 0);

    gpio_close(handle_0);
    gpio_close(handle_1);
    gpio_close(handle_2);
    exit(0);
}


int main()
{
    int pinv;
    int counter =0;

    signal(SIGINT, signal_handler);

    handle_0    = gpio_open_device("/dev/gpioc0");
    handle_1   = gpio_open_device("/dev/gpioc1");
    handle_2     = gpio_open_device("/dev/gpioc2");
	
    while(1) {
        gpio_pin_set(handle_2,  4, (counter % 5) == 1 ? 1 : 0); // 68
        gpio_pin_set(handle_1, 12, (counter % 5) == 2 ? 1 : 0); // 44
        gpio_pin_set(handle_0, 26, (counter % 5) == 2 ? 1 : 0); // 26
        gpio_pin_set(handle_1, 14, (counter % 5) == 3 ? 1 : 0); // 46
        counter++;
        usleep(90000);
    }
    return 0;
}
