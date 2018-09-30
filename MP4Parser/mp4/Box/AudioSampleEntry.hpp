//
//  AudioSampleEntry.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef AudioSampleEntry_hpp
#define AudioSampleEntry_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	//audio SampleEntry
	class AudioSampleEntry : public Box
	{
	public:
		AudioSampleEntry(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
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

			reserveds_[0] = buffer_->readBig32();
			reserveds_[1] = buffer_->readBig32();

			channelcount_ = buffer_->readBig16();
			samplesize_   = buffer_->readBig16();

			pre_defined_  = buffer_->readBig16();
			reserved1_   = buffer_->readBig16();
			samplerate_  = buffer_->readBig32() >> 16;
		}

	protected:
		uint32_t reserveds_[2];
		uint16_t channelcount_;
		uint16_t samplesize_;
		uint16_t pre_defined_;
		uint16_t reserved1_;
		uint32_t samplerate_;
	};
}

#endif /* AudioSampleEntry_hpp */
