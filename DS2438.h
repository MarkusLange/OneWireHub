// 0x26  Smart Battery Monitor

#ifndef ONEWIRE_DS2438_H
#define ONEWIRE_DS2438_H

// TODO: reduce footprint - 40 Bytes user-space
static const uint8_t MemDS2438[64] =
        {
                0x09, 0x20, 0x14, 0xAC, 0x00, 0x40, 0x01, 0x00,
                0x5A, 0xC8, 0x05, 0x02, 0xFF, 0x08, 0x00, 0xFC,
                0x00, 0x00, 0x00, 0x00, 0x6D, 0x83, 0x03, 0x02,
                0xF2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x26, 0xBF, 0x8E, 0x30, 0x01, 0x00, 0x00, 0x00,
                0x2D, 0x07, 0xDB, 0x15, 0x00, 0x00, 0x00, 0x00,
                0x28, 0x80, 0xDC, 0x1B, 0x03, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
        };

// 092014AC004001005AC80502FF0800FC000000006D830302F20000000000000026BF8E30010000002D07DB15000000002880DC1B030000000000000000000000
// 0AE813EF010000003D980502000800FC0000000000000000F4000000000000003A78E90700000000000000000000000000000000000000000000000000000000
// 08B013C501000000D6920202000800FC0000000000000000F4000000000000003AFCF4070000000000000000000000000000000000000000F300000000000000
// 09D813D301020080FDE80702FF1000FC000000001BDAFF01F20000000000000000000000000000001207DA0D000000002828520E020000000000000000000000
// 080014C501000000BC850702000800FC0000000000000000000000000000000026BCBF30010000002C07DB1500000000284C9E1B030000000000000073010000

#pragma pack(push, 1)
struct DS2438_page0 // TODO: overlay with memory if possible
{
    uint8_t flags;
    int16_t temp;
    int16_t volt;
    int16_t curr;
    uint8_t threshold;
};
#pragma pack(pop)

class DS2438 : public OneWireItem
{
private:

    static constexpr bool    dbg_sensor  = 0; // give debug messages for this sensor
    static constexpr uint8_t family_code = 0x26;

    // Register Addresses
    static constexpr uint8_t DS2438_IAD  = 0x01;
    static constexpr uint8_t DS2438_CA   = 0x02;
    static constexpr uint8_t DS2438_EE   = 0x04;
    static constexpr uint8_t DS2438_AD   = 0x08;
    static constexpr uint8_t DS2438_TB   = 0x10;
    static constexpr uint8_t DS2438_NVB  = 0x20;
    static constexpr uint8_t DS2438_ADB  = 0x40;

    uint8_t memory[64];

    bool duty(OneWireHub *hub);

public:
    DS2438(uint8_t ID1, uint8_t ID2, uint8_t ID3, uint8_t ID4, uint8_t ID5, uint8_t ID6, uint8_t ID7);

    void setTemp(const float   temp_degC);
    void setTemp(const uint8_t temp_degC);

    void setVolt(const uint16_t voltage_10mV);

    void setCurr(const uint16_t value);
};

#endif