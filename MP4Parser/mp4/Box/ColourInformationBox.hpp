//
//  ColourInformationBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef ColourInformationBox_hpp
#define ColourInformationBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	//colr
	class ColourInformationBox : public Box
	{
	public:
		ColourInformationBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{
			colour_primaries_         = -1;
			transfer_characteristics_ = -1;
			matrix_coefficients_ = -1;
			full_range_flag_     = -1;
		}

		virtual void parser(size_t& size)
		{
			Box::parser(size);

			colour_type_ = buffer_->readBig32();

			if(colour_type_ == Box::parseName("nclx"))
			{
				colour_primaries_ = buffer_->readBig16();
				transfer_characteristics_ = buffer_->readBig16();
				matrix_coefficients_ = buffer_->readBig16();

				full_range_flag_ = buffer_->read8() >> 7;
			}
		}

	protected:
		uint32_t colour_type_;
		int colour_primaries_;
		int transfer_characteristics_;
		int matrix_coefficients_;
		uint8_t full_range_flag_;
	};
}

#endif /* ColourInformationBox_hpp */
