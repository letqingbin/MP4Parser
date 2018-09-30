//
//  TimeToSampleBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef TimeToSampleBox_hpp
#define TimeToSampleBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//stts
	class TimeToSampleBox : public FullBox
	{
		typedef struct {
			uint32_t sample_count_;
			uint32_t sample_delta_;
		} stts;

	public:
		TimeToSampleBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<stts> elem = std::make_shared<stts>();
				elem->sample_count_ = buffer_->readBig32();
				elem->sample_delta_ = buffer_->readBig32();
				entries_.push_back(elem);
			}
		}

	protected:
		uint32_t entry_count_;
		std::vector<std::shared_ptr<stts>> entries_;
	};
}

#endif /* TimeToSampleBox_hpp */
