#pragma once

#include "refcount.h"

namespace PK
{
	class PK_PtrBase
	{
	};

	/**
		This class is inspired from the smart pointer class of COM. The pointer it's managing 
		must implement PK_IRefCount. It gives a class a COM like behavior by insuring that it is destroyed 
		only when it is no longer used.
	 */
	template<class T> class PK_Ptr sealed : public PK_PtrBase
	{
	private:
		PK_IRefCount* m_ptr;	// The pointer to manage

	public:
		/**
			Create an empty PK_Ptr
		 */
		PK_Ptr() : m_ptr(nullptr)		
		{
		}

		/**
			Copy constructor
		 */
		PK_Ptr(const PK_Ptr<T>& otherPtr) : m_ptr(otherPtr.m_ptr)
		{
			_AddRef();
		}

		/**
			Construct from a pointer
		 */
		PK_Ptr(T* ptr)  : m_ptr(ptr)
		{
			_AddRef();
		}

		/**
			Destruct the current instance and try to release the managed pointer
		 */
		~PK_Ptr()
		{
			_Release();
		}

		/**
			Overload operator ->
		 */
		T* operator->()
		{
			return static_cast<T*>(m_ptr);
		}

		/**
			Overload operator *
		 */
		T& operator* ()
		{
			return  *static_cast<T*>(m_ptr);
		}

		/**
			Overload cast operator
		 */
		operator T*()
		{
			return static_cast<T*>(m_ptr);
		}

		/**
			Overload operator = 
		 */
		PK_Ptr<T>& operator=(const PK_Ptr<T>& otherPtr)
		{
			if (this != &otherPtr)
			{
				_Release();
				m_ptr = otherPtr.m_ptr;
				_AddRef();
			}

			return *this;
		}

	private:
		void _AddRef()
		{
			if (m_ptr != nullptr)
			{
				m_ptr->AddRef(true);
				//m_ptr->AddRefPtr();
			}
		}

		void _Release()
		{
			if (m_ptr != nullptr)
			{
				m_ptr->Release(true);
				//m_ptr->ReleaseRefPtr();
			}
		}
	};
}