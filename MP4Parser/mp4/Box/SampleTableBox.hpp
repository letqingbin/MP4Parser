//
//  SampleTableBox.hpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/21.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#ifndef SampleTableBox_hpp
#define SampleTableBox_hpp

#include <stdio.h>
#include <iostream>

#include "MP4ContainerBox.hpp"
#include "PtrBuffer.hpp"
#include "Box.hpp"

#include "SampleDescriptionBox.hpp"
#include "TimeToSampleBox.hpp"
#include "SyncSampleBox.hpp"
#include "SampleToChunkBox.hpp"
#include "SampleSizeBox.hpp"
#include "CompactSampleSizeBox.hpp"
#include "ChunkOffsetBox.hpp"
#include "ChunkLargeOffsetBox.hpp"
#include "CompositionOffsetBox.hpp"

namespace ffstl
{
	//stbl
	class SampleTableBox : public MP4ContainerBox
	{
	public:
		SampleTableBox(std::shared_ptr<PtrBuffer> buffer) : MP4ContainerBox(buffer)
		{
			isContainer_ = true;
		}

		virtual void parser(size_t& size)
		{
			MP4ContainerBox::parser(size);
		}

		void set(std::shared_ptr<SampleDescriptionBox> value)
		{
			stsd_ = value;
		}

		void set(std::shared_ptr<TimeToSampleBox> value)
		{
			stts_ = value;
		}

		void set(std::shared_ptr<SyncSampleBox> value)
		{
			stss_ = value;
		}

		void set(std::shared_ptr<SampleToChunkBox> value)
		{
			stsc_ = value;
		}

		void set(std::shared_ptr<SampleSizeBox> value)
		{
			stsz_ = value;
		}

		void set(std::shared_ptr<ChunkOffsetBox> value)
		{
			stco_ = value;
		}

		void set(std::shared_ptr<CompositionOffsetBox> value)
		{
			ctts_ = value;
		}

		void set(std::shared_ptr<CompactSampleSizeBox> value)
		{
			stz2_ = value;
		}

		void set(std::shared_ptr<ChunkLargeOffsetBox> value)
		{
			co64_ = value;
		}

	protected:
		std::shared_ptr<SampleDescriptionBox> stsd_;
		std::shared_ptr<TimeToSampleBox> stts_;
		std::shared_ptr<SyncSampleBox> stss_;
		std::shared_ptr<SampleToChunkBox> stsc_;
		std::shared_ptr<SampleSizeBox> stsz_;
		std::shared_ptr<ChunkOffsetBox> stco_;

		std::shared_ptr<CompositionOffsetBox> ctts_;
		std::shared_ptr<CompactSampleSizeBox> stz2_;
		std::shared_ptr<ChunkLargeOffsetBox> co64_;
	};
}

#endif /* SampleTableBox_hpp */
