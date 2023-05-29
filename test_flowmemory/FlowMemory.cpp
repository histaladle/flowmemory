#include "FlowMemory.h"

FlowMemory::FlowMemory() : _buffer(nullptr),_bufferSize(0),_readableCount(0)
{}

FlowMemory::FlowMemory(FlowMemory &other) : _buffer(nullptr),_bufferSize(0),_readableCount(0)
{
#ifdef __cplusplus
    this->_buffer=new uint8_t[size_t(other._bufferSize)];
#else
    this->_buffer=new uint8_t[(size_t)(other._bufferSize)];
#endif
    memcpy(_buffer,other._buffer,size_t(_bufferSize));
    this->_bufferSize=other._bufferSize;
}

FlowMemory::FlowMemory(int buffersize) : _buffer(nullptr),_bufferSize(0),_readableCount(0)
{
#ifdef __cplusplus
    this->_buffer=new uint8_t[size_t(buffersize)];
#else
    this->_buffer=new uint8_t[(size_t)(buffersize)];
#endif
    this->_bufferSize=buffersize;
    memset(_buffer,0,size_t(_bufferSize));
}

FlowMemory::~FlowMemory()
{
    _bufferSize=0; delete _buffer; _buffer=nullptr;
}

uint8_t *FlowMemory::readableBuffer()
{
    return _buffer;
}

uint8_t *FlowMemory::writableBuffer()
{
    return _buffer+_readableCount;
}

int FlowMemory::readableCount()
{
    return _readableCount;
}

int FlowMemory::writableCount()
{
    return _bufferSize-_readableCount;
}

int FlowMemory::dump(int max_count)
{
    max_count=max_count<_readableCount?max_count:_readableCount;
    movebyte(reinterpret_cast<char*>(_buffer),max_count,_readableCount-1,-max_count);
    _readableCount-=max_count;
    return max_count;
}

int FlowMemory::take(int offset, int max_count)
{
    int res=0;
    if(max_count<=0) {
        return res;
    }
    if(offset<0) {
        return res;
    }
    if(offset>=_readableCount) {
        return res;
    }
    res=_readableCount-offset;
    res=std::min(res,max_count);
    movebyte(reinterpret_cast<char*>(_buffer),offset+res,_readableCount-1,-res);
    return res;
}

int FlowMemory::read(uint8_t *buf, int buflen)
{
    int len=0;
    len=_readableCount<buflen?_readableCount:buflen;
    memcpy(buf,_buffer,size_t(len));
    _readableCount-=len;
    return len;
}

int FlowMemory::write(uint8_t *buf, int buflen)
{
    int offset=0;
    offset=_readableCount+buflen-_bufferSize;
    if(offset<=0) {
        memcpy(_buffer+_readableCount,buf,size_t(buflen));
        _readableCount+=buflen;
    }
    else if(offset<_readableCount) {
        dump(offset);
        memcpy(_buffer+_readableCount,buf,size_t(buflen));
        _readableCount=_bufferSize;
    }
    else {
        memcpy(_buffer,buf+(buflen-_bufferSize),size_t(_bufferSize));
        _readableCount=_bufferSize;
    }
    return buflen;
}

int FlowMemory::copy(uint8_t *dst, int size, int offset)
{
    int res=size;
    memcpy(dst,_buffer+offset,size_t(size));
    return res;
}

uint8_t FlowMemory::at(int index)
{
    return _buffer[index];
}
