#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

#include "..\common_types\common_defines.h"
#include "stdint.h"

#pragma pack(push, 1)

struct mouse_report_ {
	uint8_t packet_id;
	uint8_t left_button:1;
	uint8_t middle_button:1;
	uint8_t right_button:1;
	uint8_t additional_buttons:5;
	int8_t X_pos;
	int8_t Y_pos;
	int8_t mouse_wheel_pos;
};

struct keyboard_report_ {
	uint8_t packet_id;
	uint8_t left_ctrl:1;
	uint8_t left_shft:1;
	uint8_t left_alt:1;
	uint8_t left_gui:1;
	uint8_t right_ctrl:1;
	uint8_t right_shft:1;
	uint8_t right_alt:1;
	uint8_t right_gui:1;
	uint8_t padding;
	uint8_t key1;
	uint8_t key2;
	uint8_t key3;
	uint8_t key4;
	uint8_t key5;
	uint8_t key6;
};

struct multimedia_report_ {
	uint8_t packet_id;
	uint8_t scan_next:1;
	uint8_t scan_prev:1;
	uint8_t stop:1;
	uint8_t eject:1;
	uint8_t play:1;
	uint8_t volume_mute:1;
	uint8_t volume_down:1;
	uint8_t volume_up:1;
};

struct gamepad_report_ {
	uint8_t packet_id;
	uint64_t buttons;
	uint16_t axis[6];
	uint8_t pov[4];
};

struct sensor_report_ {
	uint8_t packet_id;
	uint8_t operation_code;
	uint16_t sensor_value[MAX_A2B_INPUTS];
    uint16_t min_calib[MAX_A2B_INPUTS];
    uint16_t max_calib[MAX_A2B_INPUTS];
};

struct axis {
    uint16_t axis_min_calib_value;
    uint16_t axis_max_calib_value;
    uint8_t axis_autocalibrate:4;
    uint8_t axis_profile:4;
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

    /*===================================*/
    /*===  packet 5 =====================*/
    uint8_t packet_id5;
    uint8_t operation_code5;

    uint8_t buttons_types1st[32];
    uint8_t dummy5[30];

    /*===================================*/
    /*===  packet 6 =====================*/
    uint8_t packet_id6;
    uint8_t operation_code6;

    uint8_t buttons_types2nd[32];
    uint8_t dummy6[30];

    /*===================================*/
    /*===  packet 7 =====================*/
    uint8_t packet_id7;
    uint8_t operation_code7;

    uint16_t axes_shapes1[MAX_AXES/2][SHAPEVALUES];
    uint8_t dummy7[2];

    /*===================================*/
    /*===  packet 8 =====================*/
    uint8_t packet_id8;
    uint8_t operation_code8;

    uint16_t axes_shapes2[MAX_AXES/2][SHAPEVALUES];
    uint8_t dummy8[2];

    /*===================================*/
    /*===  packet 9 =====================*/
    uint8_t packet_id9;
    uint8_t operation_code9;

    uint8_t profile_names[MAX_AXES][10];
    uint8_t dummy9[2];
};

#pragma pack(pop)

typedef enum {
    Not_Used = 0,
    AnalogNoSmooth = 1,
    AnalogLowSmooth = 2,
    AnalogMedSmooth = 3,
    AnalogHighSmooth = 4,
    Analog2Button = 5,
    Analog2MouseX = 6,
    Analog2MouseY = 7,
    Analog2MouseWheel = 8,
    Chain_Rotary_PINA = 9,
    Chain_Rotary_PINB = 10,
    Chain_Rotary_Enc_1 = 11,
    Chain_Rotary_Enc_2 = 12,
    Single_Rotary_PINA_1 = 13,
    Single_Rotary_PINB_1 = 14,
    Single_Rotary_PINA_2 = 15,
    Single_Rotary_PINB_2 = 16,
    Single_Rotary_PINA_4 = 17,
    Single_Rotary_PINB_4 = 18,
    Button_ROW = 19,
    Button_COLUMN = 20,
    Button = 21,
    Button_GND = 22,
    RotSwPole = 23,
    RotSwWire = 24,
} pintype;

typedef enum {
        axis_mode = 0,
        A2B_mode = 1,
} wid_type;

typedef enum {
        joystick_button = 232,
        joysticksh1_button = 233,
        joysticksh2_button = 234,
        pov1up_button = 235,
        pov1right_button = 236,
        pov1down_button = 237,
        pov1left_button = 238,
        pov2up_button = 239,
        pov2right_button = 240,
        pov2down_button = 241,
        pov2left_button = 242,
        pov3up_button = 243,
        pov3right_button = 244,
        pov3down_button = 245,
        pov3left_button = 246,
        pov4up_button = 247,
        pov4right_button = 248,
        pov4down_button = 249,
        pov4left_button = 250,
        mouseleft_button = 251,
        mousemiddle_button = 252,
        mouseright_button = 253,
        volumeup_button = 128,
        volumedown_button = 129,
        volumemute_button = 127,
        leftcontrol_button = 224,
        leftshift_button = 225,
        leftalt_button = 226,
        leftgui_button = 227,
        rightcontrol_button = 228,
        rightshift_button = 229,
        rightalt_button = 230,
        rightgui_button = 231,
        f1_button = 58,
        f2_button = 59,
        f3_button = 60,
        f4_button = 61,
        f5_button = 62,
        f6_button = 63,
        f7_button = 64,
        f8_button = 65,
        f9_button = 66,
        f10_button = 67,
        f11_button = 68,
        f12_button = 69,
        enter_button = 40,
        escape_button = 41,
        backspace_button = 42,
        tab_button = 43,
        space_button = 44,
        insert_button = 73,
        delete_button = 76,
        home_button = 74,
        end_button = 77,
        pgup_button = 75,
        pgdown_button = 78,
        rightarrow_button = 79,
        leftarrow_button = 80,
        downarrow_button = 81,
        uparrow_button = 82,
        d0_button = 39,
        d1_button = 30,
        d2_button = 31,
        d3_button = 32,
        d4_button = 33,
        d5_button = 34,
        d6_button = 35,
        d7_button = 36,
        d8_button = 37,
        d9_button = 38,
        a_button = 4,
        b_button = 5,
        c_button = 6,
        d_button = 7,
        e_button = 8,
        f_button = 9,
        g_button = 10,
        h_button = 11,
        i_button = 12,
        j_button = 13,
        k_button = 14,
        l_button = 15,
        m_button = 16,
        n_button = 17,
        o_button = 18,
        p_button = 19,
        q_button = 20,
        r_button = 21,
        s_button = 22,
        t_button = 23,
        u_button = 24,
        v_button = 25,
        w_button = 26,
        x_button = 27,
        y_button = 28,
        z_button = 29,
} button_mode;

#endif // COMMON_STRUCTS_H
