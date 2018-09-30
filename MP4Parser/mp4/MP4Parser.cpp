//
//  MP4Parser.cpp
//  MP4Parser
//
//  Created by dKingbin on 2018/9/18.
//  Copyright © 2018年 dKingbin. All rights reserved.
//

#include "MP4Parser.hpp"

namespace ffstl
{
    void MP4Parser::analyze()
    {
        int64_t length = buffer_->length();
        size_t skip_size = 0;
        
        while (true)
        {
            if(length <= 0) break;
            
            std::shared_ptr<Box> box = std::make_shared<Box>(buffer_);
            box->analyze();
            
            auto fn = names_[box->getType()];
            if(fn == nullptr)
            {
                buffer_->skip(box->getSize());
                skip_size = box->getSize();
            }
            else
            {
                fn(skip_size);
            }
            
            length -= skip_size;
            skip_size = 0;
        }
    }
    
    void MP4Parser::initParsers()
    {
        int key = Box::parseName("ftyp");
        names_[key] = [this](size_t& size){
            std::shared_ptr<FileTypeBox> box = std::make_shared<FileTypeBox>(buffer_);
            box->parser(size);
            
            root_->set(box);
        };
        
        key = Box::parseName("free");
        names_[key] = [this](size_t& size){
            std::shared_ptr<FreeSpaceBox> box = std::make_shared<FreeSpaceBox>(buffer_);
            box->parser(size);
            
            root_->set(box);
        };
        
        key = Box::parseName("skip");
        names_[key] = [this](size_t& size){
            std::shared_ptr<FreeSpaceBox> box = std::make_shared<FreeSpaceBox>(buffer_);
            box->parser(size);
            
            root_->set(box);
        };
        
        key = Box::parseName("moov");
        names_[key] = [this](size_t& size){
            std::shared_ptr<MovieBox> box = std::make_shared<MovieBox>(buffer_);
            box->parser(size);
            
            root_->set(box);
        };
        
        key = Box::parseName("mvhd");
        names_[key] = [this](size_t& size){
            std::shared_ptr<MovieHeaderBox> box = std::make_shared<MovieHeaderBox>(buffer_);
            box->parser(size);
            
            root_->moov()->set(box);
        };
        
        key = Box::parseName("trak");
        names_[key] = [this](size_t& size){
            std::shared_ptr<TrackBox> box = std::make_shared<TrackBox>(buffer_);
            box->parser(size);
            
            root_->moov()->push(box);
        };
        
        key = Box::parseName("tkhd");
        names_[key] = [this](size_t& size){
            std::shared_ptr<TrackHeaderBox> box = std::make_shared<TrackHeaderBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->set(box);
        };
        
        key = Box::parseName("edts");
        names_[key] = [this](size_t& size){
            std::shared_ptr<EditBox> box = std::make_shared<EditBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->set(box);
        };
        
        key = Box::parseName("elst");
        names_[key] = [this](size_t& size){
            std::shared_ptr<EditListBox> box = std::make_shared<EditListBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->edts()->set(box);
        };
        
        key = Box::parseName("mdia");
        names_[key] = [this](size_t& size){
            std::shared_ptr<MediaBox> box = std::make_shared<MediaBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->set(box);
        };
        
        key = Box::parseName("mdhd");
        names_[key] = [this](size_t& size){
            std::shared_ptr<MediaHeaderBox> box = std::make_shared<MediaHeaderBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->set(box);
        };
        
        key = Box::parseName("hdlr");
        names_[key] = [this](size_t& size){
            std::shared_ptr<HandlerReferenceBox> box = std::make_shared<HandlerReferenceBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->set(box);
        };
        
        key = Box::parseName("minf");
        names_[key] = [this](size_t& size){
            std::shared_ptr<MediaInformationBox> box = std::make_shared<MediaInformationBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->set(box);
        };
        
        key = Box::parseName("vmhd");
        names_[key] = [this](size_t& size){
            std::shared_ptr<VideoMediaHeader> box = std::make_shared<VideoMediaHeader>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->set(box);
        };
        
        key = Box::parseName("dinf");
        names_[key] = [this](size_t& size){
            std::shared_ptr<DataInformationBox> box = std::make_shared<DataInformationBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->set(box);
        };
        
        key = Box::parseName("dref");
        names_[key] = [this](size_t& size){
            std::shared_ptr<DataReferenceBox> box = std::make_shared<DataReferenceBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->dinf()->set(box);
        };
        
        key = Box::parseName("stbl");
        names_[key] = [this](size_t& size){
            std::shared_ptr<SampleTableBox> box = std::make_shared<SampleTableBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->set(box);
        };
        
        key = Box::parseName("stsd");
        names_[key] = [this](size_t& size){
            std::shared_ptr<SampleDescriptionBox> box = std::make_shared<SampleDescriptionBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("colr");
        names_[key] = [this](size_t& size){
            std::shared_ptr<ColourInformationBox> box = std::make_shared<ColourInformationBox>(buffer_);
            box->parser(size);
        };
        
        key = Box::parseName("fiel");
        names_[key] = [this](size_t& size){
            std::shared_ptr<FieldOrderBox> box = std::make_shared<FieldOrderBox>(buffer_);
            box->parser(size);
        };
        
        key = Box::parseName("ctts");
        names_[key] = [this](size_t& size){
            std::shared_ptr<CompositionOffsetBox> box = std::make_shared<CompositionOffsetBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("stts");
        names_[key] = [this](size_t& size){
            std::shared_ptr<TimeToSampleBox> box = std::make_shared<TimeToSampleBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("stss");
        names_[key] = [this](size_t& size){
            std::shared_ptr<SyncSampleBox> box = std::make_shared<SyncSampleBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("stsc");
        names_[key] = [this](size_t& size){
            std::shared_ptr<SampleToChunkBox> box = std::make_shared<SampleToChunkBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("stsz");
        names_[key] = [this](size_t& size){
            std::shared_ptr<SampleSizeBox> box = std::make_shared<SampleSizeBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("stz2");
        names_[key] = [this](size_t& size){
            std::shared_ptr<CompactSampleSizeBox> box = std::make_shared<CompactSampleSizeBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("stco");
        names_[key] = [this](size_t& size){
            std::shared_ptr<ChunkOffsetBox> box = std::make_shared<ChunkOffsetBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        key = Box::parseName("co64");
        names_[key] = [this](size_t& size){
            std::shared_ptr<ChunkOffsetBox> box = std::make_shared<ChunkOffsetBox>(buffer_);
            box->parser(size);
            
            root_->moov()->track()->mdia()->minf()->stbl()->set(box);
        };
        
        //mdat
    }
}

