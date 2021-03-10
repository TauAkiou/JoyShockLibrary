//
// Created by robin on 3/8/21.
//

#include "JSDualSense.h"
#include "../ControllerExceptions.h"
#include <exception>

JSDualSense::JSDualSense(struct hid_device_info *dev, int uniqueHandle) {
    name = std::string("Dualsense");
    left_right = 3;
    controller_type = ControllerClass::DualSense;
    is_usb = true; // To be determined;

    serial = std::wstring(_wcsdup(dev->serial_number));
    jsl_handle = uniqueHandle;

    handle = hid_open_path(dev->path);
    if(handle == nullptr) throw;

    is_usb = ActivateControllerBluetooth();

    ResetContinousCalibration();
}

ReportFeatureInCalibrateBT JSDualSense::_hidGetCalibrationInfo() {
    ReportFeatureInCalibrateBT btcal{};

    uint8_t buffer[100];

    hid_get_feature_report(handle, buffer, 100);

    memcpy(&btcal, &buffer[1], sizeof(btcal));
    return btcal;
}

bool JSDualSense::ActivateControllerBluetooth() {
    uint8_t buffer[64];
    memset(buffer, 0, 64);

    _hidGetCalibrationInfo();

    // Read two reports from the device to ensure that the device has been flushed properly and bluetooth is set.
    hid_read_timeout(handle, buffer, 64, 100);
    hid_read_timeout(handle, buffer, 64, 100);

    return buffer[0] != 0x31; // If the controller has switched to 0x31 packets, we are using bluetooth.
}

void JSDualSense::_hidSetFeatureReport() {

}

// Return a code based on success state.
int JSDualSense::PollDeviceState() {

    uint8_t Buffer[100] = {};
    int bytes_read = 0;

    try {
        bytes_read = hid_read_timeout(handle, Buffer, 100, 1000);
        if(!bytes_read) {
            throw new ControllerTimeout(jsl_handle);
        }
    }
    catch(ControllerTimeout &excpt) {

    }


}

