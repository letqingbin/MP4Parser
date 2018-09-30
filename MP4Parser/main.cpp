//
//  main.cpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/30.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#include <iostream>
#include "MP4Parser.hpp"

int main(int argc, const char * argv[])
{
	//input your mp4 file's url
	std::shared_ptr<ffstl::MP4Parser> mp4 = std::make_shared<ffstl::MP4Parser>("");
	mp4->analyze();

	return 0;
}
