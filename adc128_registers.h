#pragma once

// register addresses
namespace reg {
    // chip configuration registers
    const uint8_t config          = 0x00;
    const uint8_t int_status      = 0x01;
    const uint8_t int_mask        = 0x03;
    const uint8_t conversion_rate = 0x07;
    const uint8_t chan_disable    = 0x08;
    const uint8_t oneshot         = 0x09;
    const uint8_t deep_shutdown   = 0x0A;
    const uint8_t adv_config      = 0x0B;
    const uint8_t busy            = 0x0C;

    // channel reading registers
    const uint8_t chan0 = 0x20;
    const uint8_t chan1 = 0x21;
    const uint8_t chan2 = 0x22;
    const uint8_t chan3 = 0x23;
    const uint8_t chan4 = 0x24;
    const uint8_t chan5 = 0x25;
    const uint8_t chan6 = 0x26;
    const uint8_t chan7 = 0x27;

    // channel limit registers
    const uint8_t limit0_hi = 0x2A;
    const uint8_t limit0_lo = 0x2B;
    const uint8_t limit1_hi = 0x2C;
    const uint8_t limit1_lo = 0x2D;
    const uint8_t limit2_hi = 0x2E;
    const uint8_t limit2_lo = 0x2F;
    const uint8_t limit3_hi = 0x30;
    const uint8_t limit3_lo = 0x31;
    const uint8_t limit4_hi = 0x32;
    const uint8_t limit4_lo = 0x33;
    const uint8_t limit5_hi = 0x34;
    const uint8_t limit5_lo = 0x35;
    const uint8_t limit6_hi = 0x36;
    const uint8_t limit6_lo = 0x37;
    const uint8_t limit7_hi = 0x38;
    const uint8_t limit7_lo = 0x39;
} // end namespace reg


namespace config {
    const uint8_t start = 1 << 0;
    const uint8_t int_enable = 1 << 1;
    /* bit 2 reserved */
    const uint8_t int_clear = 1 << 3;
    /* bits 4 thru 6 reserved */
    const uint8_t restore_defaults = 1 << 7;
} // end namespace config


namespace conversion_rate {
    const uint8_t continious = 1 << 0;
} // end namespace conversion_rate


namespace chan_disable {
    const uint8_t ch0_disable = 1 << 0;
    const uint8_t ch1_disable = 1 << 1;
    const uint8_t ch2_disable = 1 << 2;
    const uint8_t ch3_disable = 1 << 3;
    const uint8_t ch4_disable = 1 << 4;
    const uint8_t ch5_disable = 1 << 5;
    const uint8_t ch6_disable = 1 << 6;
    const uint8_t ch7_disable = 1 << 7;
} // end namespace chan_disable

namespace oneshot {
    const uint8_t enable = 1 << 0;
} // end namespace oneshot


namespace deep_shutdown {
    const uint8_t enable = 1 << 0;
} // end namespace deep_shutdown


namespace adv_config {
    const uint8_t external_vref = 1 << 0;
    const uint8_t mode_bit0     = 1 << 1;
    const uint8_t mode_bit1     = 1 << 2;
    const uint8_t mode1 = adv_config::mode_bit0;
} // end namespace adv_config


namespace busy {
    const uint8_t busy      = 1 << 0;
    const uint8_t not_ready = 1 << 1;
} // end namespace busy




