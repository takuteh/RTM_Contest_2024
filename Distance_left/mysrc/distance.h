#ifndef DISTANCE_H
#define DISTANCE_H
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

class GP2Y0E03 {
  private:
    int file;
    const int register_gpyu = 0x5E;  // 上位11~4bit
    const int register_gpys = 0x5F;  // 下位3~0bit
    int readRegister(int reg, unsigned char buf[]);
  public:
    GP2Y0E03();
    float readDistance(int address);
};

#endif
