//
//  FieldOrderBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef FieldOrderBox_hpp
#define FieldOrderBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	//fiel
	class FieldOrderBox : public Box
	{
	public:
		FieldOrderBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{}

		virtual void parser(size_t& size)
		{
			Box::parser(size);
			field_order_ = buffer_->readBig16();
		}

	protected:
		uint16_t field_order_;
	};
}

#endif /* FieldOrderBox_hpp */
