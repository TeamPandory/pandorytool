#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <linux/uinput.h>
#include<sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>

int resolution = 9;

void switchTo16by9() {
    std::cout << "Switching to 16:9" << std::endl;
    std::string sixteenNine = "echo 0 0 1279 719 > /sys/class/graphics/fb0/window_axis";
    system(sixteenNine.c_str());
    resolution = 9;
};

void switchTo4by3() {
    std::cout << "Switching to 4:3" << std::endl;
    std::string fourThree = "echo 160 0 1119 719 > /sys/class/graphics/fb0/window_axis";
    system(fourThree.c_str());
    resolution = 4;
}

void emit(int fd, int type, int code, int val) {
    struct input_event ie;

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    write(fd, &ie, sizeof(ie));
}

int initVirtualKeyboard() {
    int returnCode;
    int uInput = open("/dev/uinput", O_WRONLY | O_NDELAY);
    if (uInput) {
        struct uinput_user_dev userDev;
        memset(&userDev, 0, sizeof(userDev));
        strncpy(userDev.name, "PandoryTool VKBD", 20);
        userDev.id.version = 4;
        userDev.id.bustype = BUS_USB;
        ioctl(uInput, UI_SET_EVBIT, EV_KEY);
        for (int i = KEY_1; i < KEY_F12; i++) {
            ioctl(uInput, UI_SET_KEYBIT, i);
        }
        returnCode = write(uInput, &userDev, sizeof(userDev));
        returnCode = (ioctl(uInput, UI_DEV_CREATE));
    }
    return uInput;
}

void mashKey(int pandoryKbd, int keyCode) {
    struct input_event pandoryEvt;
    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_KEY;
    pandoryEvt.code = keyCode;
    pandoryEvt.value = 1;
    write(pandoryKbd, &pandoryEvt, sizeof(pandoryEvt));

    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_SYN;
    pandoryEvt.code = SYN_REPORT;
    pandoryEvt.value = 0;
    write(pandoryKbd, &pandoryEvt, sizeof(pandoryEvt));

    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_KEY;
    pandoryEvt.code = keyCode;
    pandoryEvt.value = 0;
    write(pandoryKbd, &pandoryEvt, sizeof(pandoryEvt));

    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_SYN;
    pandoryEvt.code = SYN_REPORT;
    pandoryEvt.value = 0;
    write(pandoryKbd, &pandoryEvt, sizeof(pandoryEvt));
}

int main() {
    std::cout << "Pandory - I eat keycodes" << std::endl;

    int keyBd = initVirtualKeyboard();

    int edition = 0; /* 0 = shareware, 1 = ultimate */
    int noAspect = 0;
    int pause = 0;
    int mode = 0;

    bool pauseDown = false;
    bool p1CDown = false;
    bool p1DDown = false;
    bool p1EDown = false;
    bool p1FDown = false;
    bool p1StartDown = false;

    std::chrono::time_point<std::chrono::steady_clock> pauseDownTime;
    std::chrono::time_point<std::chrono::steady_clock> pauseUpTime;

    std::chrono::time_point<std::chrono::steady_clock> lastTimeFound;
    std::chrono::time_point<std::chrono::steady_clock> aspectTimer = std::chrono::high_resolution_clock::now();

    std::ifstream meta("/data/meta.bin");
    std::ifstream res("/data/res.bin");
    std::string metaString, resString;
    if (meta.is_open()) {
        getline(meta, metaString);
        if (metaString == "/dev/block/data") {
            edition = 1;
        }
        meta.close();
    }
    if (res.is_open()) {
        getline(res, resString);
        if (resString.substr(0, 3) == "4:3") {
            noAspect = true;
        }
    }

    std::string lineInput;
    while (getline(std::cin, lineInput)) {
        if (edition == 1 && !noAspect) {
            std::size_t psp = lineInput.find("Added shared lib /data/lib/libppsspp_jni.so");
            std::size_t reicast = lineInput.find("gdrom: Opened image");
            std::size_t otherGame = lineInput.find("START u0 {cmp=com.moorechip.gameplayer");
            std::size_t gameMenu = lineInput.find("resumeClassName is com.moorechip.gamemenu.activity.MenuActivity");

            if (psp != std::string::npos || reicast != std::string::npos || gameMenu != std::string::npos) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                switchTo16by9();
            } else if (otherGame != std::string::npos) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                switchTo4by3();
            }
        }

        std::size_t found = lineInput.find("fpga2key");
        if (found != std::string::npos) {
            //std::cout << lineInput << std::endl;

            std::size_t p1CPress = lineInput.find("fpga2key key: 38, press: 1");
            std::size_t p1CRelease = lineInput.find("fpga2key key: 38, press: 0");
            std::size_t p1DPress = lineInput.find("fpga2key key: 39, press: 1");
            std::size_t p1DRelease = lineInput.find("fpga2key key: 39, press: 0");
            std::size_t p1EPress = lineInput.find("fpga2key key: 43, press: 1");
            std::size_t p1ERelease = lineInput.find("fpga2key key: 43, press: 0");
            std::size_t p1FPress = lineInput.find("fpga2key key: 40, press: 1");
            std::size_t p1FRelease = lineInput.find("fpga2key key: 40, press: 0");
            std::size_t p1StartPress = lineInput.find("fpga2key key: 9, press: 1");
            std::size_t p1StartRelease = lineInput.find("fpga2key key: 9, press: 0");
            if (p1CPress != std::string::npos) p1CDown = true;
            if (p1CRelease != std::string::npos) p1CDown = false;
            if (p1DPress != std::string::npos) p1DDown = true;
            if (p1DRelease != std::string::npos) p1DDown = false;
            if (p1EPress != std::string::npos) p1EDown = true;
            if (p1ERelease != std::string::npos) p1EDown = false;
            if (p1FPress != std::string::npos) p1FDown = true;
            if (p1FRelease != std::string::npos) p1FDown = false;
            if (p1StartPress != std::string::npos) p1StartDown = true;
            if (p1StartRelease != std::string::npos) p1StartDown = false;

            if (p1StartDown && p1FDown && p1EDown && p1DDown) {
                system("am start -n com.moorechip.systemsetting/com.moorechip.systemsetting.activity.SystemSettingActivity");
            } else if (p1StartDown && p1EDown) {
                // switch res
                if (edition == 1 && !noAspect) {
                    if (resolution == 9) {
                        switchTo4by3();
                    } else {
                        switchTo16by9();
                    }
                }
            } else if (p1StartDown && p1FDown) {
                system("input text 1"); //pause. found by accident
            }

            std::size_t keyPause = lineInput.find("fpga2key key: 8, press: 1");
            std::size_t keyPauseReleased = lineInput.find("fpga2key key: 8, press: 0");

            if (keyPauseReleased != std::string::npos) {
                pauseDown = false;
                pauseUpTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(pauseUpTime - pauseDownTime);
                std::cout << "Pause was held for: " << duration.count() << "ms" << std::endl;
                if (duration.count() > 30000) {
                    std::cout << "Attempting video debrick. Let's go!" << std::endl;
                    std::string restoreHDMI = "busybox dd if=/data/mtdblock0.img of=/dev/block/mtdblock0";
                    restoreHDMI += " && busybox dd if=/data/mtdblock1.img of=/dev/block/mtdblock1";
                    restoreHDMI += " && settings put global display_outputmode_auto 0";
                    restoreHDMI += " && reboot";
                    system(restoreHDMI.c_str());
                }
            }

            if (keyPause != std::string::npos) {
                pauseDown = true;
                pauseDownTime = std::chrono::high_resolution_clock::now();

                if (pause == 0) {
                    lastTimeFound = std::chrono::high_resolution_clock::now();
                }
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTimeFound);
                std::cout << "Last pause press was " << duration.count() << "ms ago." << std::endl;
                if (duration.count() <= 500) {
                    pause++;
                    if (pause == 5) {
                        std::cout << "Launching" << std::endl;
                        if (mode == 0) {
                            system("am start -n com.android.launcher/com.android.launcher2.Launcher");
                            mode = 1;
                        } else {
                            system("am start -n com.moorechip.gamemenu/com.moorechip.gamemenu.activity.MenuActivity");
                            mode = 0;
                        }
                        pause = 0;
                    }
                }
                lastTimeFound = currentTime;
            } else if (keyPauseReleased == std::string::npos) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTimeFound);
                pause = 0;
            }
        }
    }
};