//
//  SampleToChunkBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef SampleToChunkBox_hpp
#define SampleToChunkBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//stsc
	class SampleToChunkBox : public FullBox
	{
		typedef struct {
			uint32_t first_chunk_;
			uint32_t samples_per_chunk_;
			uint32_t sample_description_index_;
		} stsc;

	public:
		SampleToChunkBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<stsc> elem = std::make_shared<stsc>();
				elem->first_chunk_ = buffer_->readBig32();
				elem->samples_per_chunk_ = buffer_->readBig32();
				elem->sample_description_index_ = buffer_->readBig32();
				entries_.push_back(elem);
			}
		}

	protected:
		uint32_t entry_count_;
		std::vector<std::shared_ptr<stsc>> entries_;
	};
}


#endif /* SampleToChunkBox_hpp */
