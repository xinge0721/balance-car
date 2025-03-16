#ifndef __MPU6050_H
#define __MPU6050_H

#include "sys.h"
#include "IO_Core.h"

class MPU6050
{
private:
    class I2C
    {
    private:
        GPIO SCL;
        GPIO SDA;
    public:
        void W_SCL(uint8_t BitValue);
        void W_SDA(uint8_t BitValue);
        uint8_t R_SDA(void);
        I2C(GPIO_TypeDef* _SCL_GPIOx, uint16_t _sclPin, GPIO_TypeDef* _SDA_GPIOx, uint16_t _sdaPin);
        void Stop(void);
        void Start(void);  
        void SendByte(uint8_t Byte);
        uint8_t ReceiveByte(void);
        void SendAck(uint8_t AckBit);
        uint8_t ReceiveAck(void);
    };

    I2C IIC;
public:
    int16_t AccX;
    int16_t AccY;
    int16_t AccZ;
    int16_t GyroX;
    int16_t GyroY;
    int16_t GyroZ;

    void WriteReg(uint8_t RegAddress, uint8_t Data);
    uint8_t ReadReg(uint8_t RegAddress);
    MPU6050(GPIO_TypeDef* _SCL_GPIOx, uint16_t _sclPin, GPIO_TypeDef* _SDA_GPIOx, uint16_t _sdaPin);
    uint8_t GetID(void);
    void GetData(int16_t* AccX, int16_t* AccY, int16_t* AccZ,  // 修正为指针参数
                int16_t* GyroX, int16_t* GyroY, int16_t* GyroZ);
    void GetData(void);  
};

#endif
