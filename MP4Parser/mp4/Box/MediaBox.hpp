//
//  MediaBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MediaBox_hpp
#define MediaBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "MediaHeaderBox.hpp"
#include "HandlerReferenceBox.hpp"
#include "MediaInformationBox.hpp"

namespace ffstl
{
	//mdia
	class MediaBox : public MP4ContainerBox
	{
	public:
		MediaBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<MediaHeaderBox> value)
		{
			mdhd_ = value;
		}

		void set(std::shared_ptr<HandlerReferenceBox> value)
		{
			hdlr_ = value;
		}

		void set(std::shared_ptr<MediaInformationBox> value)
		{
			minf_ = value;
		}

		std::shared_ptr<MediaInformationBox> minf()
		{
			return minf_;
		}

	protected:
		std::shared_ptr<MediaHeaderBox> mdhd_;
		std::shared_ptr<HandlerReferenceBox> hdlr_;
		std::shared_ptr<MediaInformationBox> minf_;
	};
}

#endif /* MediaBox_hpp */
