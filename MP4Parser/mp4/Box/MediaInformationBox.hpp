//
//  MediaInformationBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MediaInformationBox_hpp
#define MediaInformationBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "VideoMediaHeader.hpp"
#include "DataInformationBox.hpp"
#include "SampleTableBox.hpp"

namespace ffstl
{
	//minf
	class MediaInformationBox : public MP4ContainerBox
	{
	public:
		MediaInformationBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<VideoMediaHeader> value)
		{
			vmhd_ = value;
		}

		void set(std::shared_ptr<DataInformationBox> value)
		{
			dinf_ = value;
		}

		void set(std::shared_ptr<SampleTableBox> value)
		{
			stbl_ = value;
		}

		std::shared_ptr<DataInformationBox> dinf()
		{
			return dinf_;
		}

		std::shared_ptr<SampleTableBox> stbl()
		{
			return stbl_;
		}

	protected:
		std::shared_ptr<VideoMediaHeader> vmhd_;
		std::shared_ptr<DataInformationBox> dinf_;
		std::shared_ptr<SampleTableBox> stbl_;
	};
}

#endif /* MediaInformationBox_hpp */
