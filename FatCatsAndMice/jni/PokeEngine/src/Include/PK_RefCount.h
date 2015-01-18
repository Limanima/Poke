#pragma once

#if defined(TESTCLASSIMPL_EXPORTS)
#define REFCNTDECL __declspec(dllexport)
#else
#define REFCNTDECL __declspec(dllimport)
#endif

namespace PK
{
	/**
		The reference counter interface. Abstract class in C++ 
	*/
	class REFCNTDECL PK_IRefCount
	{
		friend class PK_RefCount;
		
	public:
		/**
			Call to increment the reference count
		 */
		virtual void AddRef(bool isSmartPtr = false) = 0;

		/**
			Call to decrement the reference count until it's 0 and call delete 
			on the object pointer itself
		 */
		virtual void Release(bool isSmartPtr = false) = 0;

	protected:
		virtual bool CanReleaseRef() = 0;
	};

	/**
		Implements the PK_IRefCount interface. A class that want's to have reference counting
		capability must inherit from that class. As C++ supports multiple inheritance this 
		is just a matter of inheriting from that class.
	 */
	class REFCNTDECL PK_RefCount : public PK_IRefCount
	{
	private:
		int refCount;		// The reference counter
		int refPtrCount;	// Number of _refcnt_ptr monitoring that class instance

	protected:
		/**
			Default contructor, initializes the PK_RefCount object
		 */
		PK_RefCount();

	public:
		/**
			Overload of the delete operator for all the objects based on that 
			class
		 */
		void operator delete(void *ptr);

		/**
			Call to increment the reference count
		 */
		virtual void AddRef(bool isSmartPtr = false);

	/**
		Implements the PK_IRefCount interface. A class that want's to have reference counting
		capability must inherit from that class. As C++ supports multiple inheritance this 
		is just a matter of inheriting from that class.
	 */
		virtual void Release(bool isSmartPtr = false);

	protected:
		virtual bool CanReleaseRef();
	};
}
