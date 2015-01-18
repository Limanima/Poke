#include "stdafx.h"
#include "refcount.h"

using namespace CoreImpl;

PK_RefCount::PK_RefCount() : refCount(0)
{
}

/**
	Overloading the delete operator forces to call Release on the object
 */
void PK_RefCount::operator delete(void *ptr)
{
	// only release the object if it is not monitored 
	// by a _refcnt_ptr object any more
	if (static_cast<PK_IRefCount*>(ptr)->CanReleaseRef())
	{
		static_cast<PK_IRefCount*>(ptr)->Release();
	}
}

void PK_RefCount::AddRef(bool isSmartPtr)
{
	refCount++;
	if (isSmartPtr)
	{
		refPtrCount++;
	}
}

/**
	Will delete the object even if the reference count has not been incremented
 */
void PK_RefCount::Release(bool isSmartPtr)
{
	if (isSmartPtr)
	{
		--refPtrCount;
	}

	if (refCount > 0)
	{
		--refCount;
	}

	if (refCount == 0)
	{
		::delete this;	// delete the object itself
	}
}

bool PK_RefCount::CanReleaseRef()
{
	return refPtrCount == 0;
}

