//
//  EditListBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef EditListBox_hpp
#define EditListBox_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

namespace ffstl
{
	//elst
	class EditListBox : public FullBox
	{
		typedef struct {
			uint64_t duration_;
			uint64_t time_;
			uint32_t rate_;
		} elst;
		
	public:
		EditListBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();

			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<elst> element = std::make_shared<elst>();
				if(version_ == 1)
				{
					//64
					element->duration_ = buffer_->readBig64();
					element->time_ = buffer_->readBig64();
				}
				else
				{
					//32
					element->duration_ = buffer_->readBig32();
					element->time_ = buffer_->readBig32();
				}
				element->rate_  = buffer_->readBig32() >> 16;

				entries.push_back(element);
			}
		}

	protected:
		uint32_t entry_count_;
		std::vector<std::shared_ptr<elst>> entries;
	};
}

#endif /* EditListBox_hpp */
