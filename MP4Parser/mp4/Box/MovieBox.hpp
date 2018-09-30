//
//  MovieBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MovieBox_hpp
#define MovieBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "MovieHeaderBox.hpp"
#include "TrackBox.hpp"

namespace ffstl
{
	//moov
	class MovieBox : public MP4ContainerBox
	{
	public:
		MovieBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<MovieHeaderBox> value)
		{
			mvhd_ = value;
		}

		void push(std::shared_ptr<TrackBox> value)
		{
			tracks_.push_back(value);
		}

		std::shared_ptr<TrackBox> track()
		{
			if(tracks_.size() > 0)
			{
				return tracks_[tracks_.size()-1];
			}

			return nullptr;
		}

	protected:
		std::shared_ptr<MovieHeaderBox> mvhd_;
		std::vector<std::shared_ptr<TrackBox>> tracks_;
	};
}

#endif /* MovieBox_hpp */
