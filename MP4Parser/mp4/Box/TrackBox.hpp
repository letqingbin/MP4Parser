//
//  TrackBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef TrackBox_hpp
#define TrackBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "TrackHeaderBox.hpp"
#include "EditBox.hpp"
#include "MediaBox.hpp"

namespace ffstl
{
	//trak
	class TrackBox : public MP4ContainerBox
	{
	public:
		TrackBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<TrackHeaderBox> value)
		{
			tkhd_ = value;
		}

		void set(std::shared_ptr<EditBox> value)
		{
			edts_ = value;
		}

		void set(std::shared_ptr<MediaBox> value)
		{
			mdia_ = value;
		}

		std::shared_ptr<EditBox> edts()
		{
			return edts_;
		}

		std::shared_ptr<MediaBox> mdia()
		{
			return mdia_;
		}

	protected:
		std::shared_ptr<TrackHeaderBox> tkhd_;
		std::shared_ptr<EditBox> edts_;
		std::shared_ptr<MediaBox> mdia_;
	};
}

#endif /* TrackBox_hpp */
