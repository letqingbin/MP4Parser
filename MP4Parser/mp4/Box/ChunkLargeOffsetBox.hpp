//
//  ChunkLargeOffsetBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef ChunkLargeOffsetBox_hpp
#define ChunkLargeOffsetBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//co64
	class ChunkLargeOffsetBox : public FullBox
	{
	public:
		ChunkLargeOffsetBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				uint64_t val = buffer_->readBig64();
				entries_.push_back(val);
			}
		}

	protected:
		uint32_t entry_count_;
		std::vector<uint64_t> entries_;
	};
}

#endif /* ChunkLargeOffsetBox_hpp */
