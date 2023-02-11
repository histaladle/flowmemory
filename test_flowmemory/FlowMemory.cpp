#include "FlowMemory.h"

FlowMemory::FlowMemory() : _buffer(nullptr),_bufferSize(0),_readableCount(0)
{}

FlowMemory::FlowMemory(FlowMemory &other) : _buffer(nullptr),_bufferSize(0),_readableCount(0)
{
    this->_buffer=new uint8_t[other._bufferSize];
    memcpy(_buffer,other._buffer,size_t(_bufferSize));
    this->_bufferSize=other._bufferSize;
}

FlowMemory::FlowMemory(int buffersize) : _buffer(nullptr),_bufferSize(0),_readableCount(0)
{
    this->_buffer=new uint8_t[buffersize];
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

int FlowMemory::dump(int count)
{
    count=count<_readableCount?count:_readableCount;
    movebyte(reinterpret_cast<char*>(_buffer),count,_readableCount-1,-count);
    _readableCount-=count;
    return count;
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
