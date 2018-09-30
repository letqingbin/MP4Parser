//
//  FullBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/19.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef FullBox_hpp
#define FullBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	class FullBox : public Box
	{
	public:
		FullBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{
			version_ = 0;
			flags_   = 0;
		}

		virtual void parser(size_t& size)
		{
			Box::parser(size);

			version_ = buffer_->read8();
			flags_   = buffer_->readBig24();
		}

	protected:
		uint8_t version_;
		uint32_t flags_;
	};
}

#endif /* FullBox_hpp */
