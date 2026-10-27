#ifndef JKRARAMBLOCK_H
#define JKRARAMBLOCK_H

#include "types.h"
#include "JSystem/JSupport/JSUList.h"

#ifdef __cplusplus
class JKRAramHeap;

class JKRAramBlock {
  public:
    JKRAramBlock(u32 address, u32 size, u32 freeSize, u8 groupID, bool tempMemory);

    virtual ~JKRAramBlock();

    JKRAramBlock* allocHead(u32 size, u8 groupID, JKRAramHeap* heap);
    JKRAramBlock* allocTail(u32 size, u8 groupID, JKRAramHeap* heap);

    u32 getAddress() const {
        return this->mAddress;
    }
    u32 getSize() const {
        return this->mSize;
    }
    u32 getFreeSize() const {
        return this->mFreeSize;
    }
    bool isTempMemory() const {
        return this->mIsTempMemory;
    }
    void newGroupID(u8 groupID) {
        this->mGroupID = groupID;
    }

    JSULink<JKRAramBlock> mLink;
    u32 mAddress;
    u32 mSize;
    u32 mFreeSize;
    u8 mGroupID;
    bool mIsTempMemory;

    friend class JKRAramHeap;
};
#endif
#endif
