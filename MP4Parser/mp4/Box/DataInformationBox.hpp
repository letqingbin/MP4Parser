//
//  DataInformationBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef DataInformationBox_hpp
#define DataInformationBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "DataReferenceBox.hpp"

namespace ffstl
{
	//dinf
	class DataInformationBox : public MP4ContainerBox
	{
	public:
		DataInformationBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<DataReferenceBox> value)
		{
			dref_ = value;
		}

	protected:
		std::shared_ptr<DataReferenceBox> dref_;
	};
}

#endif /* DataInformationBox_hpp */
