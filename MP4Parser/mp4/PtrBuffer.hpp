//
//  PtrBuffer.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/18.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef PtrBuffer_hpp
#define PtrBuffer_hpp

#include <iostream>
#include <cassert>

namespace ffstl
{
	class PtrBuffer
	{
	public:
		PtrBuffer(void* _ptr,size_t _len) :
          buffer_((unsigned char*)_ptr)
		, pos_(0)
		, length_(_len)
		{}

		~PtrBuffer()
		{
			delete[] buffer_;
			
			buffer_ = NULL;
			pos_ = 0;
			length_ = 0;
		}

        size_t length() const
        {
            return length_;
        }
        
        //read
        size_t read(void* _pBuffer, size_t _len, bool isSeek = true);
        size_t read(void* _pBuffer, size_t _nLen, off_t _nPos, bool isSeek = true);
        
		template<typename T>
		void read(T& val, bool isSeek = true)
		{
			size_t nRead = read((void*)&val,sizeof(val), isSeek);
			assert(nRead == sizeof(val));
		}

		template<class T>
		void read(size_t _nPos, const T& _val, bool isSeek = true)
		{
			read((void*)&_val, sizeof(_val), _nPos, isSeek);
		}

        uint8_t read8(size_t offset = 0, bool isSeek = true);
        
		//little endian
        uint16_t readLittle16(size_t offset = 0, bool isSeek = true);
        unsigned int readLittle24(size_t offset = 0, bool isSeek = true);
        uint32_t readLittle32(size_t offset = 0, bool isSeek = true);
        uint64_t readLittle64(size_t offset = 0, bool isSeek = true);
        
		//big endian
        uint16_t readBig16(size_t offset = 0, bool isSeek = true);
        unsigned int readBig24(size_t offset = 0, bool isSeek = true);
        uint32_t readBig32(size_t offset = 0, bool isSeek = true);
        uint64_t readBig64(size_t offset = 0, bool isSeek = true);

        //skip
        void skip(size_t len);

        //write
        template<class T>
        void write(const T& _val)
        {
            write(&_val, sizeof(_val));
        }
        
        template<class T>
        void write(int _nPos, const T& _val)
        {
            write(&_val, sizeof(_val), _nPos);
        }
        
        void write(const char* const _val)
        {
            write(_val, (unsigned int)strlen(_val));
        }
        
        void write(int _nPos, const char* const _val)
        {
            write(_val, (unsigned int)strlen(_val), _nPos);
        }
        
        void write(const void* _pBuffer, size_t _nLen)
        {
            write(_pBuffer, _nLen, pos_);
        }
        
        void write(const void* _pBuffer, size_t _nLen, off_t _nPos);
        
        //rest pos_
        void reset()
        {
            pos_ = 0;
        }
        
	private:
		PtrBuffer(const PtrBuffer& _rhs);
		PtrBuffer& operator= (const PtrBuffer& _rhs);

	private:
		unsigned char* buffer_;
		size_t pos_;
		size_t length_;
	};
}

#endif /* PtrBuffer_hpp */
