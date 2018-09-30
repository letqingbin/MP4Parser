//
//  Box.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/19.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"

namespace ffstl
{
	class Box
	{
	public:
		Box(std::shared_ptr<PtrBuffer> buffer)
		{
			type_ = 0;
			size_ = 0;
			isContainer_ = false;
			buffer_ = buffer;
		}

		virtual void parser(size_t& size)
		{
			size_ = buffer_->readBig32();
			type_ = buffer_->readLittle32();

			if(size_ == 1)
			{
				size_ = buffer_->readBig64() - 8;
			}
			else if(size_ == 0)
			{
				//end of box
			}

			size_t copySize = size_;
			size = copySize;
		}

		virtual void analyze()
		{
			size_ = buffer_->readBig32(0, false);
			type_ = buffer_->readBig32(4, false);

            printTypeName(type_);
            
			if(size_ == 1)
			{
				size_ = buffer_->readBig64(8, false) - 8;
			}
			else if(size_ == 0)
			{
				return;
			}
		}

		static int parseName(const std::string& str)
		{
			if(str.length() < 4) return -1;
			int val = str[0]<<24 | str[1]<<16 | str[2]<<8 | str[3];
			return val;
		}
        
        void printTypeName(int32_t number)
        {
            char ch1st = char(number>>24);
            
            int temp = number << 8;
            char ch2nd = char(temp>>24);
            
            temp = number << 16;
            char ch3rd = char(temp>>24);
            
            temp = number << 24;
            char ch4th = char(temp>>24);
            
            std::cout<<ch1st<<ch2nd<<ch3rd<<ch4th<<std::endl;
        }

		int64_t getSize() const
		{
			return size_;
		}

		uint32_t getType() const
		{
			return type_;
		}

	private:
		Box(const Box& _rhs);
		Box& operator= (const Box& _rhs);
		
	protected:
		int64_t size_;
		uint32_t type_;
		bool isContainer_;
		std::shared_ptr<PtrBuffer> buffer_;
	};
}

#endif /* Box_hpp */
