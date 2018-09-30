//
//  FileTypeBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/19.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef FileTypeBox_hpp
#define FileTypeBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
    //ftyp
	class FileTypeBox : public Box
	{
	public:
		FileTypeBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
		{}

		virtual void parser(size_t& size)
		{
			Box::parser(size);

			major_brand_   = buffer_->readLittle32();
			minor_version_ = buffer_->readBig32();

            size_t currentSize = size_ - 16;
            
			if(currentSize >= 12)
			{
				while (currentSize >= 4)
				{
					uint32_t brands = buffer_->readBig32();
					compatible_brands_.push_back(brands);
					currentSize -= 4;
				}
			}
		}

	protected:
		uint32_t major_brand_;  //mp42
		uint32_t minor_version_;    //1
		std::vector<int32_t> compatible_brands_; //12 mp41mp42isom
	};
}

#endif /* FileTypeBox_hpp */
