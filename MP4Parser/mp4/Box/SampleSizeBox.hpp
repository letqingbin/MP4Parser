//
//  SampleSizeBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef SampleSizeBox_hpp
#define SampleSizeBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//stsz
	class SampleSizeBox : public FullBox
	{
	public:
		SampleSizeBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			sample_size_ = buffer_->readBig32();
			sample_count_ = buffer_->readBig32();
			if(sample_size_ == 0)
			{
				for(int i=0;i<sample_count_;i++)
				{
					int val = buffer_->readBig32();
					entries_.push_back(val);
				}
			}
		}

	protected:
		uint32_t sample_size_;
		uint32_t sample_count_;
		std::vector<int> entries_;
	};
}

#endif /* SampleSizeBox_hpp */
