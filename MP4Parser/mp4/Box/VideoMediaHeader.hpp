//
//  VideoMediaHeader.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef VideoMediaHeader_hpp
#define VideoMediaHeader_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//vmhd
	class VideoMediaHeader : public FullBox
	{
	public:
		VideoMediaHeader(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			graphicsmode_  = buffer_->readBig16();

			for(int i=0;i<3;i++)
			{
				opcolor_[i] = buffer_->readBig16();
			}
		}

	protected:
		uint16_t graphicsmode_;
		uint16_t opcolor_[3];
	};
}

#endif /* VideoMediaHeader_hpp */
