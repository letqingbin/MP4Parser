//
//  MovieHeaderBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/19.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MovieHeaderBox_hpp
#define MovieHeaderBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
    //mvhd
    class MovieHeaderBox : public FullBox
    {
    public:
        MovieHeaderBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
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
				timescale_         = buffer_->readBig32();
				duration_          = buffer_->readBig64();
            }
            else
            {
                //32
				creation_time_     = buffer_->readBig32();
				modification_time_ = buffer_->readBig32();
				timescale_         = buffer_->readBig32();
				duration_          = buffer_->readBig32();
            }

			rate_   = buffer_->readBig32() >> 16;
			volume_ = buffer_->readBig16() >> 8;
			reserved_[0] = buffer_->readBig16();
			reserved_[1] = buffer_->readBig32();
			reserved_[2] = buffer_->readBig32();

			for(int i=0;i<3;i++)
			{
				matrix_[i][0] = buffer_->readBig32() >> 16;
				matrix_[i][1] = buffer_->readBig32() >> 16;
				matrix_[i][2] = buffer_->readBig32() >> 30;
			}

			for(int i=0;i<6;i++)
			{
				pre_defined_[i] = buffer_->readBig32();
			}

			next_track_ID_ = buffer_->readBig32();
        }
        
    protected:
        uint64_t creation_time_;
        uint64_t modification_time_;
        uint32_t timescale_;
        uint64_t duration_;
        uint32_t rate_;             //16.16
        uint16_t volume_;           //8.8
        uint32_t reserved_[3];
		std::vector<std::vector<double>> matrix_;
        uint32_t pre_defined_[6];
        uint32_t next_track_ID_;
    };
}

#endif /* MovieHeaderBox_hpp */
