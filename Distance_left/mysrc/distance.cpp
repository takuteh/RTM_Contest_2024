#include"distance.h"
#include<iostream>

GP2Y0E03::GP2Y0E03() {
        // I2Cデバイスファイルを開く（/dev/i2c-1を使用）
        const char *device = "/dev/i2c-1";
        if ((file = open(device, O_RDWR)) < 0) {
            std::cerr << "Failed to open the I2C device." << std::endl;
            exit(1);
        }
}

float GP2Y0E03::readDistance(int address) {
        float data = 0.0;
        unsigned char buf[2];

        // I2Cアドレスを設定
        if (ioctl(file, I2C_SLAVE, address) < 0) {
            std::cerr << "Failed to set I2C address." << std::endl;
            exit(1);
        }

        // 10回センサーからデータを読み取る
        for (int i = 0; i < 10; ++i) {
            // 上位11~4bitのデータを読み取る
            if (readRegister(this->register_gpyu, buf) < 0) {
                std::cerr << "Failed to read register." << std::endl;
                exit(1);
            }
            int ue = buf[0];

            // 下位3~0bitのデータを読み取る
            if (readRegister(this->register_gpys, buf) < 0) {
                std::cerr << "Failed to read register." << std::endl;
                exit(1);
            }
            int shita = buf[0];

            // 距離を計算
            float kobetu = ((ue * 16 + shita) / 16.0) / 4.0;
            data += kobetu;
            usleep(5000);  // 5ms待つ
        }

        // 平均値を計算して返す
        float average = data / 10.0;
        return average;
    }

int GP2Y0E03::readRegister(int reg, unsigned char buf[]) {
        if (write(this->file, &reg, 1) != 1) {
            return -1;
        }
        if (read(this->file, buf, 1) != 1) {
            return -1;
        }
        return 0;
    }

