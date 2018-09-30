//
//  MediaHeaderBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MediaHeaderBox_hpp
#define MediaHeaderBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//mdhd
	class MediaHeaderBox : public FullBox
	{
	public:
		MediaHeaderBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			if(version_ == 1)
			{
				//64
				creation_time_     = buffer_->readBig64();
				modification_time_ = buffer_->readBig64();
				timescale_          = buffer_->readBig32();
				duration_          = buffer_->readBig64();
			}
			else
			{
				//32
				creation_time_     = buffer_->readBig32();
				modification_time_ = buffer_->readBig32();
				timescale_         = buffer_->readBig32();
				duration_          = buffer_->readBig32();
			}

			language_ = buffer_->readBig16();
			pre_defined_ = buffer_->readBig16();
		}

	protected:
		uint64_t creation_time_;
		uint64_t modification_time_;
		uint32_t timescale_;
		uint64_t duration_;

		uint16_t language_;
		uint16_t pre_defined_;
	};
}

#endif /* MediaHeaderBox_hpp */
