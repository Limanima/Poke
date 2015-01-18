#ifndef _PK_ARRAY_H_
#define _PK_ARRAY_H_

#include <vector>

namespace PK {

template <class T> class PK_Array
{
private:
    std::vector<T> m_Vector;

public:
    PK_Array() { }
    
    inline T& operator[] (int idx) {
        return m_Vector[idx];
    }
    
    bool Contains(const T toFind)
    {
        for(typename std::vector<T>::iterator itor = m_Vector.begin(); itor != m_Vector.end(); itor++)
	    {
		   if ((*itor) == toFind)
           {
               return true;
           }
	    }
        return false;
    }
    
    void Add(T item)
    {
        m_Vector.push_back(item);
    }
    
    void Clear()
    {
        m_Vector.clear();
    }
    void SetSize(unsigned long lSize) { m_Vector.resize(lSize); }
    inline unsigned long GetCount() { return m_Vector.size(); }
    inline unsigned long GetSize() { return m_Vector.size(); }
};

}
#endif
