//
// Created by robin on 3/8/21.
//

#ifndef JOYSHOCKLIBRARY_JSDUALSENSE_H
#define JOYSHOCKLIBRARY_JSDUALSENSE_H

#include "../JoyShockController.h"

#define DS_VENDOR 0x054C
#define DS_USB 0x0CE6

// Special thanks to Neilk1, hyrsh for their work on reverse engineering the DS5.
// https://controllers.fandom.com/wiki/Sony_DualSense

enum Direction : uint8_t {
    North = 0,
    NorthEast,
    East,
    SouthEast,
    South,
    SouthWest,
    West,
    NorthWest,
    None = 8
};

enum PowerState : uint8_t {
    Discharging          = 0x00,
    Charging             = 0x01,
    FullAndCharging      = 0x02,
    VoltOrTempOutOfRange = 0x0A,
    TemperatureError      = 0x0B,
    ChargingError        = 0x0F
};

enum MuteLight : uint8_t {
    Off = 0,
    On,
    Breathing,
    NoAction4,
    NoAction5,
    NoAction6,
    NoAction7,
    NoAction8 = 8
};

enum LightBrightness : uint8_t {
    Bright = 0,
    Mid,
    Dim,
    //NoAction4,
    //NoAction5,
    //NoAction6,
    //NoAction7,
    //NoAction8 = 8
};

enum LightFadeAnimation : uint8_t {
    Nothing = 0,
    FadeIn, // from black to blue
    FadeOut // from blue to black
};

struct ReportFeatureInCalibrateBT {
            uint8_t ReportID; // 0x05 // does this exist on USB? confirm
            int16_t GyroPitchBias;
            int16_t GyroYawBias;
            int16_t GyroRollBias;
            int16_t GyroPitchPlus;
            int16_t GyroPitchMinus;
            int16_t GyroYawPlus;
            int16_t GyroYawMinus;
            int16_t GyroRollPlus;
            int16_t GyroRollMinus;
            int16_t GyroSpeedPlus;
            int16_t GyroSpeedMinus;
            int16_t AccelXPlus;
            int16_t AccelXMinus;
            int16_t AccelYPlus;
            int16_t AccelYMinus;
            int16_t AccelZPlus;
            int16_t AccelZMinus;
            int16_t Unknown;
};

struct TouchFingerData {
    uint8_t Index : 7;
    uint8_t NotTouching : 1;
    uint16_t FingerX : 12;
    uint16_t FingerY : 12;
};

struct TouchData {
    TouchFingerData Finger[2];
    uint8_t Timestamp;
};

struct BTSimpleGetStateData {
    uint8_t LeftStickX;
    uint8_t LeftStickY;
    uint8_t RightStickX;
    uint8_t RightStickY;
    Direction DPad : 4;
    uint8_t ButtonSquare : 1;
    uint8_t ButtonCross : 1;
    uint8_t ButtonCircle : 1;
    uint8_t ButtonTriangle : 1;
    uint8_t ButtonL1 : 1;
    uint8_t ButtonR1 : 1;
    uint8_t ButtonL2 : 1;
    uint8_t ButtonR2 : 1;
    uint8_t ButtonShare : 1;
    uint8_t ButtonOptions : 1;
    uint8_t ButtonL3 : 1;
    uint8_t ButtonR3 : 1;
    uint8_t ButtonHome : 1;
    uint8_t ButtonPad : 1;
    uint8_t Counter : 6;
    uint8_t TriggerLeft;
    uint8_t TriggerRight;
};

struct USBGetStateData {
    uint8_t LeftStickX;
    uint8_t LeftStickY;
    uint8_t RightStickX;
    uint8_t RightStickY;
    uint8_t TriggerLeft;
    uint8_t TriggerRight;
    uint8_t SeqNo; // always 0x01 on BT, Linux driver calls this seq_no
    Direction DPad : 4;
    uint8_t ButtonSquare : 1;
    uint8_t ButtonCross : 1;
    uint8_t ButtonCircle : 1;
    uint8_t ButtonTriangle : 1;
    uint8_t ButtonL1 : 1;
    uint8_t ButtonR1 : 1;
    uint8_t ButtonL2 : 1;
    uint8_t ButtonR2 : 1;
    uint8_t ButtonCreate : 1;
    uint8_t ButtonOptions : 1;
    uint8_t ButtonL3 : 1;
    uint8_t ButtonR3 : 1;
    uint8_t ButtonHome : 1;
    uint8_t ButtonPad : 1;
    uint8_t ButtonMute : 1;
    uint8_t UNK1 : 5; // appears unused
    uint8_t UNK2; // appears unused
    uint32_t UNK_COUNTER; // Linux driver calls this reserved
    int16_t AngularVelocityX;
    int16_t AngularVelocityZ;
    int16_t AngularVelocityY;
    int16_t AccelerometerX;
    int16_t AccelerometerY;
    int16_t AccelerometerZ;
    uint32_t SensorTimestamp;
    uint8_t Temperture; // reserved2 in Linux driver
    TouchData TouchData;
    uint8_t TriggerRightStopLocation: 4;
    uint8_t TriggerRightRange: 4;
    uint8_t TriggerLeftStopLocation: 4;
    uint8_t TriggerLeftRange: 4;
    uint8_t UnkMirroredData[4]; // Unknown purpose, mirrors data from report write
    uint8_t TriggerRightMaxRange: 4;
    uint8_t TriggerLeftMaxRange: 4;
    uint32_t Unk3; // unknown counter
    uint8_t PowerPercent : 4; // 0x00-0x0A
    PowerState PowerState : 4;
    uint8_t PluggedHeadphones : 1;
    uint8_t PluggedMic : 1;
    uint8_t PluggedUnknown : 1; // unknown, EXT detect?
    uint8_t PluggedUsbData : 1;
    uint8_t PluggedUsbPower : 1;
    uint8_t PluggedUnk1 : 3;
    uint8_t PluggedMicConfirmed : 1; // detected it's actually a mic?
    uint8_t PluggedUnk2 : 1;
    uint8_t PluggedUnk3 : 6;
    uint8_t UnknownData[8]; // suspected hash to foil unofficial controllers, unconfirmed
};

template<int N> struct BTCRC {
    uint8_t Buff[N-4];
    uint32_t CRC;
};

struct BTGetStateData {
    USBGetStateData StateData;
    uint8_t UNK1;
    uint8_t BtCrcFailCount;
    uint8_t Pad[10];
};

struct ReportIn31 {
    union {
        BTCRC<78> CRC;
        struct {
            uint8_t ReportID; // 0x31
            uint8_t EnableHID : 1; // GUESS
            uint8_t Unk1 : 7;
            BTGetStateData State;
        } Data;
    };
};

struct SetStateData {
    uint8_t EnableRumbleEmulation : 1;
    uint8_t UseRumbleNotHaptics : 1;
    uint8_t AllowRightTriggerFFB : 1;
    uint8_t AllowLeftTriggerFFB: 1;
    uint8_t AllowAudioVolume: 1;
    uint8_t AllowToggleSpeakerWhileHeadsetConnected: 1;
    uint8_t AllowMicVolume: 1;
    uint8_t AllowMicToggle: 1; // check how this interacts with headsets
    uint8_t AllowMuteLight: 1;
    uint8_t AllowAudioMute: 1;
    uint8_t AllowLedColor: 1;
    uint8_t ResetLights: 1; // Pulse to reset lights to allow RGB control after pairing
    // This cannot be applied during the BT pair animation
    // Suggest using an input report's timer/counter to know if it's safe to pulse
    // Please update this comment with the optimal timing and variable
    uint8_t AllowIndicatorLights: 1;
    uint8_t AllowUnk1: 1;
    uint8_t AllowMotorPowerLevel: 1;
    uint8_t AllowUnk2: 1;
    uint8_t RumbleEmulationRight; // weak
    uint8_t RumbleEmulationLeft; // strong
    uint8_t VolumeHeadphones; // max 0x7f
    uint8_t VolumeSpeaker; // ties in with VolumeSpeaker2 somehow, PS5 appears to only use the range 0x3d-0x64
    uint8_t VolumeInternalMic; // not linier, seems to max at 64, 0 is not fully muted
    uint8_t EnableInternalMic: 1; // in addition to headset
    uint8_t MicActiveState: 1;
    uint8_t UNK_RESET1: 1; // unknown reset, both set high by Remote Play, assumed reset due to DS4 firmware
    uint8_t UNK_RESET2: 1; // unknown reset, both set high by Remote Play, assumed reset due to DS4 firmware
    uint8_t DisableHeadphones: 1; // only works with EnableSpeaker
    uint8_t EnableSpeaker: 1;
    uint8_t UNKBITA1: 1;
    uint8_t UNKBITA2: 1;
    MuteLight MuteLightMode;
    uint8_t UNKBITB1: 1;
    uint8_t UNKBITB2: 1;
    uint8_t UNKBITB3: 1;
    uint8_t UNKBITB4: 1;
    uint8_t MicMute: 1;
    uint8_t UNKBITB6: 1;
    uint8_t AudioMute: 1; // which audio?
    uint8_t UNKBITB8: 1;
    uint8_t RightTriggerFFB[11];
    uint8_t LeftTriggerFFB[11];
    uint8_t UnkMirroredData[4]; // Unknown purpose, mirrored into report read
    int TriggerMotorPowerReduction : 4; // 0x0-0x7 (no 0x8?) Applied in 12.5% reductions
    int RumbleMotorPowerReduction : 4;  // 0x0-0x7 (no 0x8?) Applied in 12.5% reductions
    uint8_t VolumeSpeaker2; // range 0-7, 4 default (maybe there is another volume here?)
    uint8_t AllowLightBrightnessChange: 1;
    uint8_t AllowColorLightFadeAnimation: 1;
    uint8_t UNKBITC: 6;
    uint8_t Unk1; // unused?
    uint8_t UNKBITD1: 1; // appears to set PluggedUnknown of input report, please confirm
    uint8_t UNKBITD2: 7;
    LightFadeAnimation LightFadeAnimation;
    LightBrightness LightBrightness;
    uint8_t PlayerLight1 : 1; // Layout used by PS5: 1 --x--
    uint8_t PlayerLight2 : 1; //                     2 -x-x-
    uint8_t PlayerLight3 : 1; //                     3 x-x-x
    uint8_t PlayerLight4 : 1; //                     4 xx-xx
    uint8_t PlayerLight5 : 1; //                     5 xxxxx
    uint8_t PlayerLightFade: 1; // if low player lights fade in, if high player lights instantly change
    uint8_t PlayerLightUNK : 2;
    uint8_t LedRed;
    uint8_t LedGreen;
    uint8_t LedBlue;
    uint8_t Pad[29];
};

class JSDualSense : JoyShockController {
    private:
    ReportFeatureInCalibrateBT _hidGetCalibrationInfo();
    void _hidSetFeatureReport();
    bool ActivateControllerBluetooth();
    int PollDeviceState() override;

    public:
    JSDualSense(struct hid_device_info *dev, int uniqueHandle);

};


#endif //JOYSHOCKLIBRARY_JSDUALSENSE_H
