//
//  TrackHeaderBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef TrackHeaderBox_hpp
#define TrackHeaderBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//tkhd
	class TrackHeaderBox : public FullBox
	{
	public:
		TrackHeaderBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{
			matrix_ = std::vector<std::vector<double>>(3,std::vector<double>(3));
		}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			if(version_ == 1)
			{
				//64
				creation_time_     = buffer_->readBig64();
				modification_time_ = buffer_->readBig64();
				track_ID_          = buffer_->readBig32();
				reserved1st_       = buffer_->readBig32();
				duration_          = buffer_->readBig64();
			}
			else
			{
				//32
				creation_time_     = buffer_->readBig32();
				modification_time_ = buffer_->readBig32();
				track_ID_          = buffer_->readBig32();
				reserved1st_       = buffer_->readBig32();
				duration_          = buffer_->readBig32();
			}

			reserveds_[0] = buffer_->readBig32();
			reserveds_[1] = buffer_->readBig32();
			layer_ = buffer_->readBig16();
			alternate_group_ = buffer_->readBig16();
			volume_ = buffer_->readBig16() >> 8;
			reserved2nd_ = buffer_->readBig16();

			for(int i=0;i<3;i++)
			{
				matrix_[i][0] = buffer_->readBig32() >> 16;
				matrix_[i][1] = buffer_->readBig32() >> 16;
				matrix_[i][2] = buffer_->readBig32() >> 30;
			}

			width_  = buffer_->readBig32() >> 16;
			height_ = buffer_->readBig32() >> 16;
		}

	protected:
		uint64_t creation_time_;
		uint64_t modification_time_;
		uint32_t track_ID_;
		uint32_t reserved1st_;
		uint64_t duration_;
		uint32_t reserveds_[2];

		uint16_t layer_;
		uint16_t alternate_group_;
		uint16_t volume_;           //8.8
		uint16_t reserved2nd_;

		std::vector<std::vector<double>> matrix_;
		uint32_t width_;		//16.16
		uint32_t height_;		//16.16
	};
}

#endif /* TrackHeaderBox_hpp */
