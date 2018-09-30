//
//  VisualSampleEntry.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef VisualSampleEntry_hpp
#define VisualSampleEntry_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	//video SampleEntry
	class VisualSampleEntry : public Box
	{
	public:
		VisualSampleEntry(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{}

		virtual void parser(size_t& size)
		{
			Box::parser(size);

			if(size_ > 16)
			{
				buffer_->readBig32();
				buffer_->readBig16();
				buffer_->readBig16();	//dref id
			}

			pre_defined1_ = buffer_->readBig16();
			reserved1_ = buffer_->readBig16();
			for(int i=0;i<3;i++)
			{
				pre_defineds_[i] = buffer_->readBig32();
			}
			width_  = buffer_->readBig16();
			height_ = buffer_->readBig16();

			horizresolution_  = buffer_->readBig32();
			vertresolution_ = buffer_->readBig32();

			reserved2_ = buffer_->readBig32();
			frame_count_ = buffer_->readBig16();

			int len = buffer_->read8();
			if(len > 31)
			{
				len = 31;
				for(int i=0;i<len;i++)
				{
					compressorname_ += char(buffer_->read8());
				}
			}
			else
			{
				buffer_->skip(31-len);
			}
			
			depth_ = buffer_->readBig16();
			pre_defined2_ = buffer_->readBig16();
		}

	protected:
		uint16_t pre_defined1_;
		uint16_t reserved1_;
		uint32_t pre_defineds_[3];
		uint16_t width_;
		uint16_t height_;
		uint32_t horizresolution_;
		uint32_t vertresolution_;
		uint32_t reserved2_;
		uint16_t frame_count_;
		std::string compressorname_;
		uint16_t depth_;
		uint16_t pre_defined2_;
	};
}

#endif /* VisualSampleEntry_hpp */
