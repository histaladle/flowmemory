#ifndef FLOWMEMORY_H
#define FLOWMEMORY_H
#include <cstdint>
#include <cstring>
#include <algorithm>
void movebyte(char *data,int start_byte,int last_byte,int offset);
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
    int dump(int max_count);
    int take(int offset, int max_count);
    int read(uint8_t *buf,int buflen);
    int write(uint8_t *buf,int buflen);
    int copy(uint8_t *dst, int size, int offset);
    uint8_t at(int index);
    uint8_t *_buffer;
    int _bufferSize;
    int _readableCount;
    FlowMemory &operator=(FlowMemory &other) = delete;
};

#endif // FLOWMEMORY_H
