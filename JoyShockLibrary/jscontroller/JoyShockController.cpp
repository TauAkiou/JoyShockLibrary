//
// Created by robin on 3/8/21.
//

#include "JoyShockController.h"

void JoyShockController::ResetContinousCalibration() {
    for(auto & i : gyro_average_window) {
        i = {};
    }
}

void JoyShockController::get_average_gyro(float &x, float &y, float &z, float &accelMagnitude) {
    float weight = 0.0f;
    float totalX = 0.0f;
    float totalY = 0.0f;
    float totalZ = 0.0f;
    float totalAccelMagnitude = 0.0f;
    int samplesAccumulated = 0;
    int samplesWanted = this->get_gyro_average_window_total_samples_for_device();
    auto samplesPerWindow = (float)(this->get_gyro_average_window_single_samples_for_device());
    //int numSamplesAvailable = 0;
    //for (int i = 0; i < num_gyro_average_windows && samplesWanted > 0; i++) {
    //	numSamplesAvailable += this->gyro_average_window[i].numSamples;
    //}

    // get the average of each window
    // and a weighted average of all those averages, weighted by the number of samples it has compared to how many samples a full window will have.
    // this isn't a perfect rolling average. the last window, which has more samples than we need, will have its contribution weighted according to how many samples it would ideally have for the current span of time.
    for (int i = 0; i < num_gyro_average_windows && samplesWanted > 0; i++) {
        int cycledIndex = (i + this->gyro_average_window_front_index) % num_gyro_average_windows;
        GYRO_AVERAGE_WINDOW* windowPointer = this->gyro_average_window + cycledIndex;
        if (windowPointer->numSamples == 0)
        {
            continue;
        }
        float thisWeight = 1.0f;
        auto fNumSamples = (float)(windowPointer->numSamples);
        if (samplesWanted < windowPointer->numSamples)
        {
            thisWeight = ((float)(samplesWanted)) / windowPointer->numSamples;
            samplesWanted = 0;
        }
        else
        {
            thisWeight = fNumSamples / samplesPerWindow;
            samplesWanted -= windowPointer->numSamples;
        }

        //printf("[%.1f] [%d] [%.1f]; ", \
						//	windowPointer->y,
//	(int)fNumSamples,
//	thisWeight);

        totalX += (windowPointer->x / fNumSamples) * thisWeight;
        totalY += (windowPointer->y / fNumSamples) * thisWeight;
        totalZ += (windowPointer->z / fNumSamples) * thisWeight;
        totalAccelMagnitude += (windowPointer->accelMagnitude / fNumSamples) * thisWeight;
        weight += thisWeight;
    }
    if (weight > 0.0) {
        x = totalX / weight;
        y = totalY / weight;
        z = totalZ / weight;
        accelMagnitude = totalAccelMagnitude / weight;
    }
    //printf("{%.1f, %.1f, %.1f} {%d}\n", x, y, z, numSamplesAvailable);
    //printf("{%.1f} {%d}\n", y, numSamplesAvailable);
}

int JoyShockController::get_gyro_average_window_single_samples_for_device() {
    return get_gyro_average_window_total_samples_for_device() / (num_gyro_average_windows - 2);
}


