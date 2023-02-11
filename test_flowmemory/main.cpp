#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include "FlowMemory.h"
int main()
{
    FlowMemory fwmem(8);
    uint8_t *buf=new uint8_t[128];
    for(int i=0;i<128;++i) {
        buf[i]=uint8_t(i);
    }
    fwmem.write(buf,   8);
    fwmem.write(buf+8, 4);
    fwmem.write(buf+8,16);
    return 0;
}
