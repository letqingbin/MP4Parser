//
//  SampleDescriptionBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef SampleDescriptionBox_hpp
#define SampleDescriptionBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"
#include "VisualSampleEntry.hpp"
#include "AudioSampleEntry.hpp"

namespace ffstl
{
	//stsd
	class SampleDescriptionBox : public FullBox
	{
	public:
		SampleDescriptionBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();
			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<Box> box = std::make_shared<Box>(buffer_);
				box->analyze();

				if(box->getType() == Box::parseName("avc1"))
				{
					//video
					std::shared_ptr<VisualSampleEntry> box = std::make_shared<VisualSampleEntry>(buffer_);
					size_t boxSize = 0;
					box->parser(boxSize);

					video_ = box;
				}
				else if(box->getType() == Box::parseName("mp4a"))
				{
					//audio
					std::shared_ptr<AudioSampleEntry> box = std::make_shared<AudioSampleEntry>(buffer_);
					size_t boxSize = 0;
					box->parser(boxSize);

					audio_ = box;
				}

				//subtile
			}
		}

	protected:
		uint32_t entry_count_;
		std::shared_ptr<VisualSampleEntry> video_;
		std::shared_ptr<AudioSampleEntry> audio_;
	};
}

#endif /* SampleDescriptionBox_hpp */
