#if 0
/*-License-
  Poke Engine
  Copyright (C) 2014-2015 Jorge Lima <limanima@limanima.com>
  
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-/License- */
    
#ifndef _PK_MEMORYPOOL_H_
#define _PK_MEMORYPOOL_H_

#include "PK_Object.h"
#include "PK_Array.h"
#include "PK_Exceptions.h"
#include "PK_Environment.h"

#define PK_DEFAULT_POOL_SIZE        10
#define PK_MAX_MEMORY_POOL_SIZE     65535

namespace PK {
/// @brief The PK_MemoryPool allocates and manages a pool of object instances that can be retrieved and used by it's clientes. 
///
/// The PK_MemoryPool is a template class that can be used to speed up the process of memory allocation of objects. 
/// Memory allocation can be a slow process, and when a lot of objects of the same type will be created/destroyd, it's
/// faster to use a PK_MemoryPool instead of using new/delete.
/// The pool starts by allocating the number of objects specified in the constructor in a single block of memory.
/// Then, the method GetInstance() can be used to retrieve an instance previously allocated. This method will not call 
/// the new operator to allocate memory, because it is already allocated. That's why it is faster.
/// To free an instance use the method FreeInstance(). The object instance will be returned to the pool and can be
/// re-used.
/// If the pool get's out of instances to serve (this can happen you request more objects then the size of the pool),
/// it will create a new batch of object instances and add them to the pool thus increasing the pool size. This will happen
/// if AutoGowth is specified (the default). The pool will double it's size when this happens. Example: pool size is 2, 
/// user asks for 3 objects, the pool will allocate 2 new objects doubling it's size to 4, the 8, the 16, etc.
/// If AutoGowth is false and the pool get's out of objects, an PK_OutOfMemoryException will be thrown.
///
/// Limitations of the pool:
///  -The objects in the pool must derive from PK_Object
///  -The pool can only serve objects of the same type, the type is specified in the template parameter
///  -Objects must implement the default constructor
template <class T> 
class PK_MemoryPool : public PK::PK_Object
{
private:
  struct Block
  {
    char * m_pMemBuffer;
  };
  PK_List<Block *> m_pBlocks;
  PK_Array<T *> m_poolInstances;
  int  m_iLastUsedInstance;
  bool m_bAutoGrowth;
  int m_iBlockSize;
  int m_iInstancesPerBlock;
  typename PK_ListIterator(Block *) m_currentBlock;

public:
  /// @brief Creates a new instance of PK_MemoryPool.
  ///
  /// The object type is specified in the object declaration in the template parameter.
  /// @param iPoolSize - The size of the pool. Must be greater then 0. The default value is 10.
  /// @param bAutoGrowth - Specifies if the pool should automatically grow when out of instances. The default value is true.
  /// @param sPoolName - The pool name. Default value is "".
  PK_MemoryPool<T>(int iPoolSize = PK_DEFAULT_POOL_SIZE, bool bAutoGrowth = true, const PK_String &sPoolName = "") :
      PK_Object(sPoolName)
  {
    m_bAutoGrowth = bAutoGrowth;
    m_iInstancesPerBlock = iPoolSize;
    m_iBlockSize = m_iInstancesPerBlock * sizeof(T);
    m_iLastUsedInstance = 0;
    Grow();
    m_currentBlock = m_pBlocks.Begin();
  }

  ~PK_MemoryPool()
  {
    for(PK_ListIterator(Block *) itor = m_pBlocks.Begin(); itor != m_pBlocks.End(); itor++)
    {
      Block *pBlock = (*itor);
      for(int i = 0; i < m_iInstancesPerBlock; i++)
      {
        T *pObj = (T*)(&pBlock->m_pMemBuffer[i * sizeof(T)]);
        if (pObj != NULL)
        {
            pObj->~T();
        }
      }
      delete [] pBlock->m_pMemBuffer;
      delete pBlock;
    }
  }
  
  /// @brief Gets a free instance from the pool.
  ///
  /// If the pool has no free instances and AutoGrowth is true it will automatically grow and return a valid instance.
  /// The pool doubles it's size in this case. If AutoGrowth is false, and the pool gets out of instances a PK_OutOfMemoryException will be thrown.
  /// The constructor on the instance is only called the first time the instance is returned. Reused instances will not run the constructor.
  T & GetInstance()
  {
    if ((unsigned int)m_iLastUsedInstance >=  m_poolInstances.GetCount())
    {
      if (m_bAutoGrowth == false)
      {
        throw PK_OutOfMemoryException("PK_MemoryPool", 0, __FILE__, __LINE__);
      }
      Grow();
      m_currentBlock++;
    }
    T *pObj;
    if (m_poolInstances[m_iLastUsedInstance] == NULL)
    {
      pObj = (T*) &((*m_currentBlock)->m_pMemBuffer[(m_iLastUsedInstance % m_iInstancesPerBlock) * sizeof(T)]);
      new(pObj) T();
    }
    else
    {
       pObj = m_poolInstances[m_iLastUsedInstance];
    }
    m_iLastUsedInstance++;
    return *pObj;
  }

  /// @brief Returns an object instance back to the pool. 
  ///
  /// This instance is considered to be free and can be returned in the
  /// future by GetInstance().
  /// In debug mode, a PK_SystemException is thrown if this method is called with a object instance that was not allocated by the pool
  /// or if you try to free a instance that is already free in the pool. In release this checks are not performed.
  /// The destructor on the instance will not be called when an instance is freed. The destructors are called when the pool is destroyed.
  /// @param instance - The instance to free.
  void FreeInstance(T &instance)
  {
    if (PK_Environment::IsDebug())
    {       
      // Check if the instance is already free
      for(unsigned int i = m_iLastUsedInstance; i < m_poolInstances.GetCount(); i++)
      {
        if (m_poolInstances[i] == &instance)
        {
          throw PK_SystemException("Object instance to be freed is already free.", __FILE__, __LINE__);
        }
      }
      
      // Check if the instance belongs to the pool
      bool belongs = false;
      for(PK_ListIterator(Block *) itor = m_pBlocks.Begin(); itor != m_pBlocks.End(); itor++)
      {
        Block *pBlock = (*itor);
        for(int i = 0; i < m_iInstancesPerBlock; i++)
        {
            if ((T*)(&pBlock->m_pMemBuffer[i * sizeof(T)]) == &instance)
            {
              belongs = true;
              break;
            }
        }
      }
      if (!belongs)
      {
        throw PK_SystemException("Object instance to be freed does not belong to this memory pool.", __FILE__, __LINE__);
      }
      
   }
   m_poolInstances[--m_iLastUsedInstance] = &instance;
   if (m_iLastUsedInstance > 0 && m_iLastUsedInstance % m_iInstancesPerBlock == 0)
   {
       m_currentBlock--;
   }
  }

  /// Returns the pool size.
  inline int GetSize() { return m_poolInstances.GetLength(); }

  /// @brief Turns on/off auto grow.
  ///
  /// If AutoGrow is true, the pool will automatically grow when an instance is requested and there aren't any more
  /// available instances. The pool doubles in size when this happens. 
  /// If the pool needs to be resized and grows behind PK_MAX_MEMORY_POOL_SIZE, a PK_OutOfMemoryException is thrown.
  /// @param bAutoGrow - The automatic grow behaviour. 
  void SetAutoGrow(bool bAutoGrow) { m_bAutoGrowth = bAutoGrow; }

  /// Returns the automatic grow value.
  inline bool GetAutoGrow() { return m_bAutoGrowth; }

  /// Returns the number of available instances.
  inline bool GetAvailableInstancesCount() { return m_iNumInstances - m_iLastUsedInstance; }

private:
  void Grow()
  {
    // Create block
    Block *pNewBlock = new Block();
    pNewBlock->m_pMemBuffer = new char[m_iBlockSize];
    m_pBlocks.Add(pNewBlock);
    // Resize the instances array
    m_poolInstances.SetSize(m_pBlocks.GetCount() * m_iInstancesPerBlock);
    // Set instances array to 0 (no need to set the instaces addresses on the array because we can calculate the address 
    // of each instance)
    memset(&m_poolInstances[m_pBlocks.GetCount() - 1], NULL, m_iInstancesPerBlock);
  }
};
}
#endif

#endif // if 0
