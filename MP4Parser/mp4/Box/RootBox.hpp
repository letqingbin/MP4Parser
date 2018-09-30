//
//  RootBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef RootBox_hpp
#define RootBox_hpp

#include <stdio.h>
#include <iostream>

#include "FileTypeBox.hpp"
#include "FreeSpaceBox.hpp"
#include "MovieBox.hpp"

namespace ffstl
{
	//root
	class RootBox
	{
	public:
		RootBox()
		{
		}

		void set(std::shared_ptr<FileTypeBox> value)
		{
			ftyp_ = value;
		}

		void set(std::shared_ptr<FreeSpaceBox> value)
		{
			free_ = value;
		}

		void set(std::shared_ptr<MovieBox> value)
		{
			moov_ = value;
		}

		std::shared_ptr<MovieBox> moov()
		{
			return moov_;
		}

	protected:
		std::shared_ptr<FileTypeBox> ftyp_;
		std::shared_ptr<FreeSpaceBox> free_;
		std::shared_ptr<MovieBox> moov_;
	};
}

#endif /* RootBox_hpp */
