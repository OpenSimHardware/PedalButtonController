#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

#include "..\common_types\common_defines.h"

#pragma pack(push, 1)
struct axis {
    uint16_t axis_min_calib_value;
    uint16_t axis_max_calib_value;
    uint8_t axis_special;
};

struct analog_2_button {
    uint8_t buttons_number;
    uint8_t buttons_intervals[MAX_A2B_BUTTONS];
};

struct total_config_ {
    /*===================================*/
    /*===  packet 1 =====================*/
    uint8_t packet_id1;
    uint8_t operation_code1;

    struct axis axes[MAX_AXES];

    uint8_t pin[USEDPINS];

    /*===================================*/
    /*===  packet 2 =====================*/
    uint8_t packet_id2;
    uint8_t operation_code2;

    uint16_t rotary_press_time;
    uint16_t rotary_debounce_time;
    uint16_t button_debounce_time;
    uint16_t rotswitch_press_time;
    uint16_t combined_axis1_mincalib_value;
    uint16_t combined_axis1_maxcalib_value;
    uint16_t combined_axis2_mincalib_value;
    uint16_t combined_axis2_maxcalib_value;

    uint8_t usb_ps_uniq[10];
    uint8_t usb_exchange_rate;

    uint8_t combined_axis_enabled;

    uint8_t POV_config;

    uint8_t total_single_encoders;
    uint8_t single_encoder_pinA[MAX_SINGLE_ENCODERS];
    uint8_t single_encoder_pinB[MAX_SINGLE_ENCODERS];


    uint8_t combined_axis_separate:1;
    uint8_t combined_axis_cooperate:1;
    uint8_t combined_axis_pin1_autocalib:1;
    uint8_t combined_axis_pin2_autocalib:1;

    uint8_t combined_axis_percent;
    uint8_t combined_axis_pin1;
    uint8_t combined_axis_pin2;

    /*===================================*/
    /*===  packet 3 =====================*/
    uint8_t packet_id3;
    uint8_t operation_code3;

    uint8_t config_version;
    uint16_t rotswitch_min_time;
    uint16_t analog_2_button_min_time;
    uint16_t analog_2_button_press_time;

    struct analog_2_button a2b_1st5[5];

    /*===================================*/
    /*===  packet 4 =====================*/
    uint8_t packet_id4;
    uint8_t operation_code4;

    uint8_t analog_2_button_inputs;

    struct analog_2_button a2b_2nd5[5];
    uint8_t dummy4[6];

};
#pragma pack(pop)

typedef enum {
    Not_Used = 0,
    AnalogNoSmooth = 1,
    AnalogLowSmooth = 2,
    AnalogMedSmooth = 3,
    AnalogHighSmooth = 4,
    Analog2Button = 5,
    Chain_Rotary_PINA = 6,
    Chain_Rotary_PINB = 7,
    Chain_Rotary_Enc_1 = 8,
    Chain_Rotary_Enc_2 = 9,
    Chain_Rotary_Enc_4 = 10,
    Single_Rotary_PINA_1 = 11,
    Single_Rotary_PINB_1 = 12,
    Single_Rotary_PINA_2 = 13,
    Single_Rotary_PINB_2 = 14,
    Single_Rotary_PINA_4 = 15,
    Single_Rotary_PINB_4 = 16,
    Button_ROW = 17,
    Button_COLUMN = 18,
    Button = 19,
    Button_GND = 20,
    RotSwPole = 21,
    RotSwWire = 22,
} pintype;

typedef enum {
        axis_mode = 0,
        A2B_mode = 1,
} wid_type;


#endif // COMMON_STRUCTS_H
