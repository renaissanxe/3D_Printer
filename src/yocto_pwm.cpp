
#include <iostream>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <time.h>
#include <ctime>
#include "yocto_pwm.hpp"

// Allocate exactly 31 bytes for buf
int utc_system_timestamp(char buf[]) {
    const int bufsize = 31;
    const int tmpsize = 21;
    struct timespec now;
    struct tm tm;
    int retval = clock_gettime(CLOCK_REALTIME, &now);
    gmtime_r(&now.tv_sec, &tm);
    strftime(buf, tmpsize, "%Y-%m-%dT%H:%M:%S.", &tm);
    sprintf(buf + tmpsize -1, "%09luZ", now.tv_nsec);
    return retval;
}

void YoctoFreeAll() {
    YAPI::FreeAPI();
}

static void pwmChangeCallbackTest(YPwmInput *fct, const string &value)
{
    struct timespec ts;
    char buf[31];
    utc_system_timestamp(buf);
    std::cerr << buf<< ", PWM Changed " << value<< std::endl;
}


Yocto_PWM::Yocto_PWM() {
    pwm = NULL;
    m = NULL;
}

int Yocto_PWM::Detect(string target) {
    string       errmsg;
    // Setup the API to use local USB devices
    if (YAPI::RegisterHub("usb", errmsg) != YAPI::SUCCESS) {
        std::cerr << "RegisterHub error: " << errmsg << std::endl;
        return -1;
    }
    if(target=="any")
        pwm = YPwmInput::FirstPwmInput();
    else
        pwm = YPwmInput::FindPwmInput(target + ".pwmInput1");
    if(pwm == NULL) {
        std::cerr << "No module connected (Check cable)" << std::endl;
        return -1;
    }

    if (pwm->isOnline()) {
        m = pwm->get_module();
    } else {
        std::cerr << "No module connected (Check cable)" << std::endl;
    }
    return 0;
}

int Yocto_PWM::Test() {
    string       errmsg;
    while (pwm->isOnline()) {
        std::cout << "PWM1 : " << pwm->get_frequency() << " Hz " << pwm->get_dutyCycle()
             << " %  " << pwm->get_pulseCounter() << "pulses edges" << std::endl;

        std::cout << "  (press Ctrl-C to exit)" << std::endl;
        YAPI::Sleep(1000, errmsg);
    }
    std::cout << "Module disconnected" << std::endl;
    return 0;
}

void Yocto_PWM::EnablePWMDetection(YPwmInputValueCallback callback) {
    pwm->registerValueCallback(callback);
}

void Yocto_PWM::EnterEventMode() {
    string       errmsg;
    while (true)
    {
        // inactive waiting loop allowing you to trigger
        // value change callbacks
        YAPI::Sleep(500, errmsg);
    }
}


void yoctoTest(string dev) {
    Yocto_PWM pwm;
    // pwm.Detect("any");
    int err = pwm.Detect(dev);
    // pwm.Test();
    pwm.EnablePWMDetection(pwmChangeCallbackTest);
    pwm.EnterEventMode();
}





// YPwmInput *pwminput = YPwmInput::FindPwmInput("YPWMRX01-123456.pwmInput1");
