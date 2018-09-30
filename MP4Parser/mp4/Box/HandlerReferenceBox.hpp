//
//  HandlerReferenceBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef HandlerReferenceBox_hpp
#define HandlerReferenceBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//hdlr
	class HandlerReferenceBox : public FullBox
	{
	public:
		HandlerReferenceBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			pre_defined_  = buffer_->readBig32();
			handler_type_ = buffer_->readBig32();

			for(int i=0;i<3;i++)
			{
				reserved_[i] = buffer_->readBig32();
			}

			if(handler_type_ == Box::parseName("vide"))
			{
				//video
			}
			else if(handler_type_ == Box::parseName("soun"))
			{
				//aduio
			}
			else if(handler_type_ == Box::parseName("mla "))
			{
				//mp2
			}
			else if(handler_type_ == Box::parseName("subp")
					|| handler_type_ == Box::parseName("clcp"))
			{
				//subtitle
			}

			size_t len = size_ - 24 - 8;
			while(len > 0)
			{
				uint8_t val = 0;
				buffer_->read(val);
				name_ += char(val);
				len--;
			}
		}

	protected:
		uint32_t pre_defined_;
		uint32_t handler_type_;
		uint32_t reserved_[3];
		std::string name_;
	};
}

#endif /* HandlerReferenceBox_hpp */
