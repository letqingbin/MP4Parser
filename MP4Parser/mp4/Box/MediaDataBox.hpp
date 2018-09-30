//
//  MediaDataBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MediaDataBox_hpp
#define MediaDataBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	//mdat
	class MediaDataBox : public Box
	{
	public:
		MediaDataBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{}

		virtual void parser(size_t& size)
		{
			Box::parser(size);
			buffer_->skip(size_-8);
		}
	};
}

#endif /* MediaDataBox_hpp */
