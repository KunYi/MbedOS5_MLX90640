
#ifndef MLX90640_H
#define MLX90640_H
#include "mbed.h"

#define MLX90640_ADDR       (0x33<<1)

typedef struct
{
    int16_t kVdd;
    int16_t vdd25;
    float KvPTAT;
    float KtPTAT;
    uint16_t vPTAT25;
    float alphaPTAT;
    int16_t gainEE;
    float tgc;
    float cpKv;
    float cpKta;
    uint8_t resolutionEE;
    uint8_t calibrationModeEE;
    float KsTa;
    float ksTo[5];
    int16_t ct[5];
    uint16_t alpha[768];    
    uint8_t alphaScale;
    int16_t offset[768];    
    int8_t kta[768];
    uint8_t ktaScale;    
    int8_t kv[768];
    uint8_t kvScale;
    float cpAlpha[2];
    int16_t cpOffset[2];
    float ilChessC[3]; 
    uint16_t brokenPixels[5];
    uint16_t outlierPixels[5];  
} paramsMLX90640;

class MLX90640 {
    /** MLX90640 constructor
        @param i2c a configured i2c object
        @param addr addr of the I2C peripheral as wired
     */
public:
    MLX90640(I2C &i2c, uint8_t addr);
    ~MLX90640();
    int readRegs(uint16_t addr, uint8_t *data, uint32_t len) const;
    uint16_t whoIAM();
    int init(uint16_t buff[832]);
    int getFrameData(uint16_t frameData[834]);
    float getVdd(uint16_t *frameData);
    float getTa(uint16_t *frameData);
    void calculateTo(uint16_t *frameData, float emissivity, float tr, float *result);


protected:
    I2C *_i2c;
    uint8_t _addr;
    void DumpEE(uint16_t data[832]);
    int writeRegs(uint16_t addr, uint16_t data) const;
    paramsMLX90640 params;

};
#endif