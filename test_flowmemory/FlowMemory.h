#ifndef FLOWMEMORY_H
#define FLOWMEMORY_H
#include <cstdint>
#include <cstring>
void movebyte(char *data,int start_byte,int end_byte,int offset);
class FlowMemory
{
public:
    FlowMemory();
    FlowMemory(FlowMemory &other);
    FlowMemory(int buffersize);
    ~FlowMemory();
    uint8_t *readableBuffer();
    uint8_t *writableBuffer();
    int readableCount();
    int writableCount();
    int dump(int count);
    int read(uint8_t *buf,int buflen);
    int write(uint8_t *buf,int buflen);
    uint8_t *_buffer;
    int _bufferSize;
    int _readableCount;
    FlowMemory &operator=(FlowMemory &other) = delete;
};

#endif // FLOWMEMORY_H
