//
//  MP4Parser.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/18.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef MP4Parser_hpp
#define MP4Parser_hpp

#include <iostream>
#include <memory>
#include <fstream>

#include <map>
#include <vector>

#include "PtrBuffer.hpp"

#include "Box.hpp"
#include "FullBox.hpp"
#include "FileTypeBox.hpp"
#include "FreeSpaceBox.hpp"
#include "MovieHeaderBox.hpp"
#include "MediaDataBox.hpp"
#include "TrackHeaderBox.hpp"
#include "EditListBox.hpp"
#include "MediaHeaderBox.hpp"
#include "HandlerReferenceBox.hpp"
#include "MP4ContainerBox.hpp"
#include "VideoMediaHeader.hpp"
#include "DataReferenceBox.hpp"
#include "SampleDescriptionBox.hpp"
#include "TimeToSampleBox.hpp"
#include "SyncSampleBox.hpp"
#include "SampleToChunkBox.hpp"
#include "SampleSizeBox.hpp"
#include "CompactSampleSizeBox.hpp"
#include "ChunkOffsetBox.hpp"
#include "ChunkLargeOffsetBox.hpp"
#include "ColourInformationBox.hpp"
#include "FieldOrderBox.hpp"
#include "CompositionOffsetBox.hpp"

#include "MovieBox.hpp"
#include "TrackBox.hpp"
#include "EditBox.hpp"
#include "MediaBox.hpp"
#include "MediaInformationBox.hpp"
#include "SampleTableBox.hpp"
#include "DataInformationBox.hpp"

#include "RootBox.hpp"

namespace ffstl
{
	class MP4Parser
	{
	public:
		MP4Parser(std::string filePath)
		{
			std::ifstream file;
			file.open(filePath);

			file.seekg(0,std::ios::end);
			int64_t length = file.tellg();
			file.seekg(0,std::ios::beg);

			char* buffer = new char[length];
			file.read(buffer, length);
			file.close();

			buffer_ = std::make_shared<PtrBuffer>((void*)buffer,length);
			root_ = std::make_shared<RootBox>();

			initParsers();
		}

        void analyze();
        void initParsers();
		
	private:
		MP4Parser(const MP4Parser& _rhs);
		MP4Parser& operator= (const MP4Parser& _rhs);

	private:
		std::shared_ptr<PtrBuffer> buffer_;
		std::shared_ptr<RootBox> root_;
		std::map<int,std::function<void(size_t&)>> names_;
	};
}

#endif /* MP4Parser_hpp */
