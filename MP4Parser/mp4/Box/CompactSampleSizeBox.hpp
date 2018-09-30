//
//  CompactSampleSizeBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef CompactSampleSizeBox_hpp
#define CompactSampleSizeBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//stz2
	class CompactSampleSizeBox : public FullBox
	{
	public:
		CompactSampleSizeBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			reserved_ = buffer_->readBig24();
			field_size_ = buffer_->read8();
			sample_count_ = buffer_->readBig32();

			for(int i=0;i<sample_count_;i++)
			{
				uint64_t val = 0;
				buffer_->read(&val, field_size_);
				entries_.push_back(val);
			}
		}

	protected:
		uint16_t reserved_;
		uint8_t field_size_;
		uint32_t sample_count_;
		std::vector<int64_t> entries_;
	};
}

#endif /* CompactSampleSizeBox_hpp */
