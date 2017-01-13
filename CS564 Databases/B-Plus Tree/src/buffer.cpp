/**
 * @author See Contributors.txt for code contributors and overview of BadgerDB.
 *
 * @section LICENSE
 * Copyright (c) 2012 Database Group, Computer Sciences Department, University of Wisconsin-Madison.
 */

#include <memory>
#include <iostream>
#include "buffer.h"
#include "exceptions/buffer_exceeded_exception.h"
#include "exceptions/page_not_pinned_exception.h"
#include "exceptions/page_pinned_exception.h"
#include "exceptions/bad_buffer_exception.h"
#include "exceptions/hash_not_found_exception.h"
#include "file_iterator.h"

namespace badgerdb { 
/**
 * Constructor for BufMgr class.
 */
BufMgr::BufMgr(std::uint32_t bufs)
	: numBufs(bufs) {
	bufDescTable = new BufDesc[bufs];

  for (FrameId i = 0; i < bufs; i++) 
  {
  	bufDescTable[i].frameNo = i;
  	bufDescTable[i].valid = false;
  }

  bufPool = new Page[bufs];

	int htsize = ((((int) (bufs * 1.2))*2)/2)+1;
  hashTable = new BufHashTbl (htsize);  // allocate the buffer hash table

  clockHand = bufs - 1;
}

/**
 * Desctructer for BufMgr class
 */
BufMgr::~BufMgr() {
  for (uint i = 0; i < numBufs; i++) {
    if (bufDescTable[clockHand].valid == true) {
      if (bufDescTable[clockHand].dirty == true) {
	bufDescTable[clockHand].file->writePage(bufPool[clockHand]);
        bufDescTable[clockHand].dirty = false;
      }
    }
    advanceClock();
  }
  delete [] bufPool;
  delete [] bufDescTable;

}

/**
 * Advance clock to next frame in the buffer pool
 */
void BufMgr::advanceClock()
{
  clockHand = (clockHand + 1)%numBufs;
}

/**
 * Allocate a free frame.
 *
 * @param frame         Frame reference, frame ID of allocated frame returned via this variable
 * @throws BufferExceededException If no such buffer is found which can be allocated
 */
void BufMgr::allocBuf(FrameId & frame) 
{
  uint passes = 0;
  uint pins = 0;

  // Begin major search loop
  while (true) {
    // If the algorithm has passed through all frames, check pinned count
    if (passes == numBufs) {
      // If all of the frames were pinned, throw an exception
      if (pins == numBufs) {
	throw BufferExceededException();
      }
      // Else, start over
      else {
	pins = 0;
	passes = 0;
      }
    }

    // If the frame is valid Check for other conditions
    if (bufDescTable[clockHand].valid == true) {
      // If the frame is pinned, incrememnt pin count and advance
      if (bufDescTable[clockHand].pinCnt > 0) {
	pins++;
	passes++;
	advanceClock();
	continue;
      }
      // If frame is not pinned, continue to check conditions
      else {
	// If the referenced bit is true, update the reference bit and advance
	if (bufDescTable[clockHand].refbit == true) {
	  bufDescTable[clockHand].refbit = false;
	  advanceClock();
	  passes++;
	  continue;
	}
	// If the referenced bit was not true, continue to check conditions
	else {
	  // If the frame was dirty, write back that file frame to memory and clear dirty bit
	  if (bufDescTable[clockHand].dirty == true) {
	    bufDescTable[clockHand].file->writePage(bufPool[clockHand]);
	    bufDescTable[clockHand].dirty = false;
	  }
	}
      }
    }
    // Now put the frameNumber in the reference variable and return
    frame = bufDescTable[clockHand].frameNo;
    if (bufDescTable[clockHand].valid == true) {
      try {
	hashTable->remove(bufDescTable[clockHand].file,bufDescTable[clockHand].pageNo);
      }
      catch (HashNotFoundException& e) {
      }
    }
    return;
  }
}

/**
 * Reads the given page from the file into a frame and returns the pointer to page.
 * If the requested page is already present in the buffer pool pointer to that frame is returned
 * otherwise a new frame is allocated from the buffer pool for reading the page.
 *
 * @param file          File object
 * @param PageNo  Page number in the file to be read
 * @param page          Reference to page pointer. Used to fetch the Page object in which requested page from file is read in.
 */	
void BufMgr::readPage(File* file, const PageId pageNo, Page*& page)
{
  FrameId fr;
  try {
    hashTable->lookup(file,pageNo,fr);
    bufDescTable[fr].refbit = true;
    bufDescTable[fr].pinCnt++;
    page = &(bufPool[fr]);
    return;
  }
  catch ( HashNotFoundException& e) {
    allocBuf(fr);
    bufPool[fr] = file->readPage(pageNo);
    hashTable->insert(file,pageNo,fr);
    bufDescTable[fr].Set(file,pageNo);
    page = &(bufPool[fr]);
    return;
  }

}


/**
 * Unpin a page from memory since it is no longer required for it to remain in memory.
 *
 * @param file          File object
 * @param PageNo  Page number
 * @param dirty         True if the page to be unpinned needs to be marked dirty
 * @throws  PageNotPinnedException If the page is not already pinned
 */
void BufMgr::unPinPage(File* file, const PageId pageNo, const bool dirty) 
{
  FrameId frameNo;
  try {
    hashTable->lookup(file,pageNo,frameNo);
    if (bufDescTable[frameNo].pinCnt <= 0 ) {
      throw PageNotPinnedException(file->filename(),pageNo,frameNo);
    }
    bufDescTable[frameNo].pinCnt--;
    if (dirty) {
      bufDescTable[frameNo].dirty = true;
    }
  }
  catch (HashNotFoundException& e) {
    return;
  }
}

/**
 * Writes out all dirty pages of the file to disk.
 * All the frames assigned to the file need to be unpinned from buffer pool before this function can be successfully called.
 * Otherwise Error returned.
 *
 * @param file          File object
 * @throws  PagePinnedException If any page of the file is pinned in the buffer pool
 * @throws BadBufferException If any frame allocated to the file is found to be invalid
 */
void BufMgr::flushFile(const File* file) 
{
  /* get number of file pages, and iterate over them, checking hashtable for eeach
     if found, check for dirty. If dirty, write back and set dirty bit to false. Remove hash entry either way,
     then invoke clear for that page's bufDesc entry. If a page is pinned, throws PagePinnedException, throws BadBufferException
     if an invalid page belonging to the file is encountered.
  */
  File* fp = (File *) file;
  int pageNo = 0;
  FrameId fr;
  FileIterator fi;
  for (fi = fp->begin(); fi != fp->end(); fi++) {
    try {
      pageNo = (*fi).page_number();
      hashTable->lookup(file,pageNo,fr);
      if (bufDescTable[fr].valid == false) {
        throw BadBufferException(fr,bufDescTable[fr].dirty,bufDescTable[fr].valid,bufDescTable[fr].refbit);
      }
      if (bufDescTable[fr].pinCnt > 0) {
	throw PagePinnedException(fp->filename(),pageNo,fr);
      }
      if (bufDescTable[fr].dirty == true) {
	fp->writePage(bufPool[fr]);
	bufDescTable[fr].dirty = false;
      }
      hashTable->remove(fp,pageNo);
      bufDescTable[fr].Clear();
    }
    catch (HashNotFoundException& e) {
      continue;
    }
  }
}

/**
 * Allocates a new, empty page in the file and returns the Page object.
 * The newly allocated page is also assigned a frame in the buffer pool.
 *
 * @param file          File object
 * @param PageNo  Page number. The number assigned to the page in the file is returned via this reference.
 * @param page          Reference to page pointer. The newly allocated in-memory Page object is returned via this reference.
 */
void BufMgr::allocPage(File* file, PageId &pageNo, Page*& page) 
{
  /* First allocate an empty page w/ file->allocatePage(), Then call allocBuf() to get
     a buffer pool frame, Insert this entry into the hash table, insert into buffer pool, and Set()
     the bufDescTable entry for this. Return both the page and pageNo 
  */
  Page* pg = NULL;
  Page pg1;
  FrameId fr;
  pg1 = file->allocatePage();
  pg = &pg1;
  allocBuf(fr);
  hashTable->insert(file,pg->page_number(),fr);
  bufDescTable[fr].Set(file,pg->page_number());
  bufPool[fr] = *pg;
  pageNo = pg->page_number();
  std::cout << "PageNo : " << pageNo << ". pageaddr: " << pg << "\n";
  page = &bufPool[fr];


}

/**
 * Delete page from file and also from buffer pool if present.
 * Since the page is entirely deleted from file, its unnecessary to see if the page is dirty.
 *
 * @param file          File object
 * @param PageNo  Page number
 */
void BufMgr::disposePage(File* file, const PageId PageNo)
{
  /* Check hash table to be sure page is in buffer pool, if not found then continue,
     if found then the frame is freed (bufDescTable Clear()) and the hash entry is removed.
     Finally, remove delete the actual page from the file.
  */
  FrameId fr;
  try {
    hashTable->lookup(file,PageNo,fr);
    hashTable->remove(file,PageNo);
    bufDescTable[fr].Clear();
  }
  catch (HashNotFoundException& e) {
  }

  file->deletePage(PageNo);

 
}

void BufMgr::printSelf(void) 
{
  BufDesc* tmpbuf;
	int validFrames = 0;
  
  for (std::uint32_t i = 0; i < numBufs; i++)
	{
  	tmpbuf = &(bufDescTable[i]);
		std::cout << "FrameNo:" << i << " ";
		tmpbuf->Print();

  	if (tmpbuf->valid == true)
    	validFrames++;
  }

	std::cout << "Total Number of Valid Frames:" << validFrames << "\n";
}

}
