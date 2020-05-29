#include <iostream>
#include <chrono>
#include <thread>

int resolution = 9;

void switchTo16by9() {
    std::cout << "Switching to 16:9" << std::endl;
    std::string sixteenNine = "echo 0 0 1279 719 > /sys/class/graphics/fb0/window_axis";
    system(sixteenNine.c_str());
    resolution = 9;
};

void switchTo4by3() {
    std::cout << "Switching to 4:3" << std::endl;
    std::string fourThree   = "echo 160 0 1119 719 > /sys/class/graphics/fb0/window_axis";
    system(fourThree.c_str());
    resolution = 4;
}

int main() {
    std::cout << "Pandory - I eat keycodes" << std::endl;
    int pause = 0;
    int mode = 0;
    bool pauseDown = false;
    std::chrono::time_point<std::chrono::steady_clock> pauseDownTime;
    std::chrono::time_point<std::chrono::steady_clock> pauseUpTime;

    std::chrono::time_point<std::chrono::steady_clock> lastTimeFound;
    std::chrono::time_point<std::chrono::steady_clock> aspectTimer = std::chrono::high_resolution_clock::now();

    std::string lineInput;
    while (getline(std::cin, lineInput)) {
        std::size_t psp = lineInput.find("Added shared lib /data/lib/libppsspp_jni.so");
        std::size_t reicast = lineInput.find("gdrom: Opened image");
        std::size_t otherGame = lineInput.find("START u0 {cmp=com.moorechip.gameplayer");
        std::size_t gameMenu = lineInput.find("resumeClassName is com.moorechip.gamemenu.activity.MenuActivity");

        if (psp != std::string::npos || reicast != std::string::npos || gameMenu != std::string::npos) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            switchTo16by9();
        }
        else if (otherGame != std::string::npos) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            switchTo4by3();
        }

        std::size_t found = lineInput.find("fpga2key");
        if (found != std::string::npos) {
            std::cout << lineInput << std::endl;
            std::size_t keyPause = lineInput.find("fpga2key key: 8, press: 1");
            std::size_t keyPauseReleased = lineInput.find("fpga2key key: 8, press: 0");

            if (keyPauseReleased != std::string::npos) {
                pauseUpTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(pauseUpTime - pauseDownTime);
                std::cout << "Pause was held for: " << duration.count() << "ms" << std::endl;
                if (duration.count() > 2000) {
                    if (resolution == 9) {
                        switchTo4by3();
                    } else {
                        switchTo16by9();
                    }
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