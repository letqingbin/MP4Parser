//
//  MP4ContainerBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MP4ContainerBox_hpp
#define MP4ContainerBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
	//moov/trak/edts/mdia/minf/stbl/dinf
	class MP4ContainerBox : public Box
	{
	public:
		MP4ContainerBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			Box::parser(size);
			size = 8;
		}
	};
}

#endif /* MP4ContainerBox_hpp */
