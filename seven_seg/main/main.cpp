#include <cstdio>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define SEG_A GPIO_NUM_33
#define SEG_B GPIO_NUM_32
#define SEG_C GPIO_NUM_22
#define SEG_D GPIO_NUM_21
#define SEG_E GPIO_NUM_13
#define SEG_F GPIO_NUM_26
#define SEG_G GPIO_NUM_27

static void display(int a, int b, int c, int d, int e, int f, int g)
{
  gpio_set_level(SEG_A, a);
  gpio_set_level(SEG_B, b);
  gpio_set_level(SEG_C, c);
  gpio_set_level(SEG_D, d);
  gpio_set_level(SEG_E, e);
  gpio_set_level(SEG_F, f);
  gpio_set_level(SEG_G, g);
}

static void show_digit(char c)
{
  switch (c) {
    case '0': display(1, 1, 1, 1, 1, 1, 0); break;
    case '1': display(0, 1, 1, 0, 0, 0, 0); break;
    case '2': display(1, 1, 0, 1, 1, 0, 1); break;
    case '3': display(1, 1, 1, 1, 0, 0, 1); break;
    case '4': display(0, 1, 1, 0, 0, 1, 1); break;
    case '5': display(1, 0, 1, 1, 0, 1, 1); break;
    case '6': display(1, 0, 1, 1, 1, 1, 1); break;
    case '7': display(1, 1, 1, 0, 0, 0, 0); break;
    case '8': display(1, 1, 1, 1, 1, 1, 1); break;
    case '9': display(1, 1, 1, 0, 0, 1, 1); break;
    case 'a': case 'A': display(1, 1, 1, 0, 1, 1, 1); break;
    case 'b': case 'B': display(0, 0, 1, 1, 1, 1, 1); break;
    case 'c': case 'C': display(1, 0, 0, 1, 1, 1, 0); break;
    case 'd': case 'D': display(0, 1, 1, 1, 1, 0, 1); break;
    case 'e': case 'E': display(1, 0, 0, 1, 1, 1, 1); break;
    case 'f': case 'F': display(1, 0, 0, 0, 1, 1, 1); break;
    default:
      printf("Invalid input: %c (use 0-9 or A-F)\n", c);
      break;
  }
}

static void setup_pins(void)
{
  const gpio_num_t pins[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G};
  for (gpio_num_t p : pins) {
    gpio_reset_pin(p);
    gpio_set_direction(p, GPIO_MODE_OUTPUT);
  }
}

extern "C" void app_main(void)
{
  setup_pins();
  printf("Type a digit (0-9 or A-F) and press Enter:\n");

  while (true) {
    int c = getchar();
    if (c == EOF) {
      vTaskDelay(pdMS_TO_TICKS(20));  // no input yet, wait a bit
      continue;
    }
    if (c == '\n' || c == '\r') {
      continue;                        // ignore Enter
    }
    show_digit((char)c);
  }
}