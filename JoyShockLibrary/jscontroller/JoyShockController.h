//
// Created by robin on 3/8/21.
//

#ifndef JOYSHOCKLIBRARY_JOYSHOCKCONTROLLER_H
#define JOYSHOCKLIBRARY_JOYSHOCKCONTROLLER_H

#include "JoyShockLibrary.h"
#include "../SensorFusion.cpp"
#include "../hidapi/hidapi.h"
#include "../tools.cpp"
#include <string>
#include <string>
#include <chrono>

#ifdef __GNUC__
#define _wcsdup wcsdup
#endif

namespace chrono = std::chrono;

enum ControllerClass {
    NintendoSwitch,
    Dualshock4,
    DualSense
};

typedef struct GYRO_AVERAGE_WINDOW {
    float x;
    float y;
    float z;
    float accelMagnitude;
    int numSamples;
} GYRO_AVERAGE_WINDOW;

class JoyShockController {
    protected:
        hid_device* handle;
        int jsl_handle;

        int timeout_counter;

        std::wstring serial;
        std::string name;

        int deviceNumber = 0;// left(0) or right(1) vjoy

        int left_right = 0;// 1: left joycon, 2: right joycon, 3: pro controller

        chrono::steady_clock::time_point last_polled;
        float deltatime;

        JOY_SHOCK_STATE simple_state = {};
        JOY_SHOCK_STATE last_simple_state = {};

        IMU_STATE imu_state = {};
        IMU_STATE last_imu_state = {};

        TOUCH_STATE touch_state = {};
        TOUCH_STATE last_touch_state = {};

        Motion motion;

        int global_count = 0;

    float acc_cal_coeff[3] = {0.0f, 0.0f, 0.0f};
    float gyro_cal_coeff[3] = {0.0f, 0.0f, 0.0f};
    float cal_x[1] = { 0.0f };
    float cal_y[1] = { 0.0f };

    bool has_user_cal_stick_l = false;
    bool has_user_cal_stick_r = false;
    bool has_user_cal_sensor = false;

    ControllerClass controller_type = ControllerClass::NintendoSwitch;
    bool is_usb = false;

    bool cancel_thread = false;
    std::thread* thread;

    // for calibration:
    bool use_continuous_calibration = false;
    bool cue_motion_reset = false;
    float offset_x = 0.0f;
    float offset_y = 0.0f;
    float offset_z = 0.0f;
    float accel_magnitude = 1.0f;

    // for continuous calibration
    static const int num_gyro_average_windows = 16;
    int gyro_average_window_front_index = 0;
    int gyro_average_window_seconds = 600; // TODO: Function to set this for this device and for all devices. Different players might have different settings
    GYRO_AVERAGE_WINDOW gyro_average_window[num_gyro_average_windows];

    // Methods
    virtual int get_gyro_average_window_total_samples_for_device() = 0;
    void get_average_gyro(float& x, float& y, float& z, float& accelMagnitude);
    int get_gyro_average_window_single_samples_for_device();
    JoyShockController() = default;


public:
    virtual int PollDeviceState() = 0;
    void ResetContinousCalibration();
    void PushSensorSamples(float x, float y, float z, float accelMagnitude);
    MOTION_STATE GetMotionState();
    void CalculateAnalogStick2(float &pOutX, float &pOutY, uint16_t x, uint16_t y, uint16_t x_calc[3], uint16_t y_calc[3]);

    JOY_SHOCK_STATE GetSimpleState();
    IMU_STATE GetIMUState();
    TOUCH_STATE GetTouchState();







};

#endif //JOYSHOCKLIBRARY_JOYSHOCKCONTROLLER_H
