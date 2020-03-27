#pragma once


#include <stdint.h>


class Accel_Payload
{
    public:
        Accel_Payload() {}
        ~Accel_Payload() {}
        virtual uint64_t allocate(int size) = 0;
        virtual void deallocate() = 0;
        virtual void serialize() = 0;
        virtual void deserialize() = 0;
        uint64_t m_address;
        int m_size;
};


class FPGA_hndl
{
    public:
        FPGA_hndl() {}
        ~FPGA_hndl() {}
        virtual int hardware_init() = 0;
        virtual int software_init() = 0;
        virtual uint64_t waitConfig() = 0;
        virtual int setConfig(Accel_Payload* pyld) = 0;
        virtual uint64_t waitParam() = 0;
        virtual int setParam(Accel_Payload* pyld) = 0;
        virtual int waitStart() = 0;
        virtual int sendStart() = 0;
        virtual int waitComplete() = 0;
        virtual int sendComplete() = 0;
        virtual int getOutput(Accel_Payload* pyld) = 0;
};

