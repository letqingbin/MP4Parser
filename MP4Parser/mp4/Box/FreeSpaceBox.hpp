//
//  FreeSpaceBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/19.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef FreeSpaceBox_hpp
#define FreeSpaceBox_hpp

#include <stdio.h>
#include <iostream>

#include "PtrBuffer.hpp"
#include "Box.hpp"

namespace ffstl
{
    //free/skip
    class FreeSpaceBox : public Box
    {
    public:
        FreeSpaceBox(std::shared_ptr<PtrBuffer> buffer) : Box(buffer)
        {}
        
        virtual void parser(size_t& size)
        {
            Box::parser(size);
			buffer_->skip(size);
        }
    };
}

#endif /* FreeSpaceBox_hpp */
