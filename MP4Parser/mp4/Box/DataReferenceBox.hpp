//
//  DataReferenceBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/20.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef DataReferenceBox_hpp
#define DataReferenceBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"
#include "FullBox.hpp"

#include "DataEntryUrlBox.hpp"
#include "DataEntryUrnBox.hpp"

namespace ffstl
{
	//dref
	class DataReferenceBox : public FullBox
	{
	public:
		DataReferenceBox(std::shared_ptr<PtrBuffer> buffer) : FullBox(buffer)
		{}

		virtual void parser(size_t& size)
		{
			FullBox::parser(size);

			entry_count_ = buffer_->readBig32();

			for(int i=0;i<entry_count_;i++)
			{
				std::shared_ptr<Box> box = std::make_shared<Box>(buffer_);
				box->analyze();

				if(Box::parseName("url ") == box->getType())
				{
					std::shared_ptr<DataEntryUrlBox> urlBox = std::make_shared<DataEntryUrlBox>(buffer_);
					size_t urlSize = 0;
					urlBox->parser(urlSize);

					url_ = urlBox;
				}
				else if(Box::parseName("urn ") == box->getType())
				{
					std::shared_ptr<DataEntryUrnBox> urnBox = std::make_shared<DataEntryUrnBox>(buffer_);
					size_t urnSize = 0;
					urnBox->parser(urnSize);

					urn_ = urnBox;
				}
			}
		}

	protected:
		uint32_t entry_count_;
		std::shared_ptr<DataEntryUrlBox> url_;
		std::shared_ptr<DataEntryUrnBox> urn_;
	};
}


#endif /* DataReferenceBox_hpp */
