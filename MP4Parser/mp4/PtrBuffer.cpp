//
//  PtrBuffer.cpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/18.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#include "PtrBuffer.hpp"

namespace ffstl
{
    size_t PtrBuffer::read(void* _pBuffer, size_t _nLen, off_t _nPos, bool isSeek)
    {
        size_t nRead = length_ - _nPos;
        nRead = std::min(nRead, _nLen);
        memcpy(_pBuffer, buffer_ + _nPos, nRead);
        
        if(isSeek)
        {
            pos_ = pos_ + nRead;
        }
        
        return nRead;
    }
    
    //read
    size_t PtrBuffer::read(void* _pBuffer, size_t _len, bool isSeek)
    {
        if(_pBuffer == NULL) return -1;
        
        size_t nRead = read(_pBuffer, _len, pos_, isSeek);
        return nRead;
    }

    uint8_t PtrBuffer::read8(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint8_t val = 0;
        read(nPos, val, isSeek);
        return val;
    }
    
    //little endian
    uint16_t PtrBuffer::readLittle16(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint16_t val = 0;
        read(nPos, val, isSeek);
        return val;
    }
    
    unsigned int PtrBuffer::readLittle24(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = readLittle16(offset, isSeek);
        offset += 2;
        val |= read8(offset, isSeek) << 16;
        return val;
    }
    
    uint32_t PtrBuffer::readLittle32(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint32_t val = 0;
        read(nPos, val, isSeek);
        return val;
    }
    
    uint64_t PtrBuffer::readLittle64(size_t offset, bool isSeek)
    {
        size_t nPos = pos_ + offset;
        
        uint64_t val = 0;
        read(nPos, val,isSeek);
        return val;
    }
    
    //big endian
    uint16_t PtrBuffer::readBig16(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = read8(offset, isSeek) << 8;
        offset = isSeek ? 0 : offset+1;
        val |= read8(offset, isSeek);
        return val;
    }
    
    unsigned int PtrBuffer::readBig24(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = readBig16(offset, isSeek) << 8;
        offset = isSeek ? 0 : offset+2;
        val |= read8(offset, isSeek);
        return val;
    }
    
    uint32_t PtrBuffer::readBig32(size_t offset, bool isSeek)
    {
        unsigned int val = 0;
        
        val = readBig16(offset, isSeek) << 16;
        offset = isSeek ? 0 : offset+2;
        val |= readBig16(offset, isSeek);
        return val;
    }
    
    uint64_t PtrBuffer::readBig64(size_t offset, bool isSeek)
    {
        uint64_t val = 0;
        val = (uint64_t)readBig32(offset, isSeek) << 32;
        offset = isSeek ? 0 : offset+4;
        val |= (uint64_t)readBig32(offset, isSeek);
        return val;
    }
    
    //skip
    void PtrBuffer::skip(size_t len)
    {
        size_t nRead = length_ - pos_;
        nRead = std::min(nRead, len);
        
        pos_ += nRead;
    }
    
    void PtrBuffer::write(const void* _pBuffer, size_t _nLen, off_t _nPos)
    {
        size_t nWrite = length_ - _nPos;
        nWrite = std::min(nWrite, _nLen);
        memcpy(buffer_ + _nPos, _pBuffer, nWrite);
        
        pos_ += nWrite;
    }
}

