
#ifndef __AP_HAL_LINUX_RCINPUT_H__
#define __AP_HAL_LINUX_RCINPUT_H__

#include <AP_HAL_Linux.h>

#define LINUX_RC_INPUT_NUM_CHANNELS 16

class Linux::LinuxRCInput : public AP_HAL::RCInput {
public:
    LinuxRCInput();
    virtual void init(void* machtnichts);
    bool new_input();
    uint8_t num_channels();
    uint16_t read(uint8_t ch);
    uint8_t read(uint16_t* periods, uint8_t len);

    bool set_overrides(int16_t *overrides, uint8_t len);
    bool set_override(uint8_t channel, int16_t override);
    void clear_overrides();

    // default empty _timer_tick, this is overridden by board
    // specific implementations
    virtual void _timer_tick() {}

 protected:
    void _process_ppmsum_pulse(uint16_t width_usec);

 private:
    volatile bool new_rc_input;
    
    uint16_t _pulse_capt[LINUX_RC_INPUT_NUM_CHANNELS];
    uint8_t  _num_channels;

    // the channel we will receive input from next, or -1 when not synchronised
    int8_t _channel_counter;

    /* override state */
    uint16_t _override[LINUX_RC_INPUT_NUM_CHANNELS];
};

#include "RCInput_PRU.h"

#endif // __AP_HAL_LINUX_RCINPUT_H__
