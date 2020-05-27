#include <controller.h>
#include <spi.h>

controller_input_t get_controller_state(short controller_number)
{
    select_slave(controller_number);
    controller_input_t input;
    input.raw_data = spi_transfer(0xAC);
    return input;
}