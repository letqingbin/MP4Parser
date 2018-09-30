//
//  CompositionOffsetBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef CompositionOffsetBox_hpp
#define CompositionOffsetBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//ctts
	class CompositionOffsetBox : public FullBox
	{
		typedef struct {
			uint32_t sample_count_;
			int64_t sample_offsets_;
		} ctts;

	public:
		CompositionOffsetBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				uint32_t count = buffer_->readBig32();
				int64_t offset = buffer_->readBig32();
				for(int j=0;j<count;j++)
				{
					auto elem = std::make_shared<ctts>();
					elem->sample_count_   = 1;
					elem->sample_offsets_ = offset;
					entries_.push_back(elem);
				}
			}
		}

	protected:
		uint32_t entry_count_;
		std::vector<std::shared_ptr<ctts>> entries_;
	};
}

#endif /* CompositionOffsetBox_hpp */
