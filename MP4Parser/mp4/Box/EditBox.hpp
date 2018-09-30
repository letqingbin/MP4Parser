//
//  EditBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef EditBox_hpp
#define EditBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "EditListBox.hpp"

namespace ffstl
{
	//edts
	class EditBox : public MP4ContainerBox
	{
	public:
		EditBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<EditListBox> value)
		{
			elst_ = value;
		}
		
		std::shared_ptr<EditListBox> elst()
		{
			return elst_;
		}

	protected:
		std::shared_ptr<EditListBox> elst_;
	};
}

#endif /* EditBox_hpp */
