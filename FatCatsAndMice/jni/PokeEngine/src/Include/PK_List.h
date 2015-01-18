#ifndef _PK_LIST_H_
#define _PK_LIST_H_

#include <list>


#define PK_ListIterator(T) std::list<T>::iterator

namespace PK {
  


template <class T> class PK_List
{
private:
    std::list<T>           m_List;
    typename std::list<T>::iterator m_itor;
    
public:
    PK_List()
    {
    }

	inline typename PK_ListIterator(T) Begin()
	{
		return m_List.begin();
	}
	inline typename PK_ListIterator(T) End()
	{
		return m_List.end();
	}
 
    void Clear()
    {
        m_List.clear();
    }
    
    void Add(T item)
    {
        m_List.push_back(item);
    }

    void Remove(T item)
    {
      m_List.remove(item);
    }
    
    T GetFirst()
    {
      return (*m_List.begin());
    }
    
    void InsertAtBeginning(T item)
    {
        m_List.insert(m_List.begin(), item);
    }

    typename PK_ListIterator(T) Erase(typename PK_ListIterator(T) itor)
    {
      return m_List.erase(itor);
    }
    
    bool Contains(const T toFind)
    {
        for(typename std::list<T>::iterator itor = m_List.begin(); itor != m_List.end(); itor++)
	    {
		   if ((*itor) == toFind)
           {
               return true;
           } 
	    }
        return false;
    }
   
    inline unsigned int GetCount() { return (unsigned int)m_List.size(); }

};

}
#endif
