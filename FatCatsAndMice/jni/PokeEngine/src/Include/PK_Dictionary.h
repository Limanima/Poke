#ifndef _PK_DICTIONARY_H_
#define _PK_DICTIONARY_H_

#include <map>


#define PK_MapIterator(K,V) std::map<K, V>::iterator

namespace PK {


template <class K, class V> class PK_Dictionary
{
private:
    std::map<K,V>               m_map;
    
public:
    PK_Dictionary()
    {
    }
     
    inline V& operator[] (K idx) {
        return m_map[idx];
    }

	inline typename PK_MapIterator(K,V) Begin()
	{
		return m_map.begin();
	}
	inline typename PK_MapIterator(K,V) End()
	{
		return m_map.end();
	}
 
    void Clear()
    {
        m_map.clear();
    }
    
    void Add(K key, V value)
    {
        m_map[key] = value;
    }

    void Remove(K key)
    {
        m_map.remove(key);
    }
   
    inline unsigned int GetCount() { return (unsigned int)m_map.size(); }

};

}
#endif
