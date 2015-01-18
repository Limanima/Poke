#ifndef _PK_STRING_H_
#define _PK_STRING_H_

#include <string>
#include <stdarg.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include "PK_Array.h"
#include "PK_List.h"

namespace PK {

// Classe que estende a classe PK_String
// Não altera o comportamento de PK_String, apenas extende, por isso não deverá
// haver problema entre usar PK_String ou string
class PK_String : public std::string
{

public:
    // string constructor
	PK_String() : std::string() { }
	PK_String( const std::string& s ) : std::string( s ) { }
	PK_String( const std::string& s, std::size_t n ) : std::string( s,n ) { }
	PK_String( const char *s, std::size_t n ) : std::string( s,n ) { }
	PK_String( const char *s ) : std::string( s ) { }
	PK_String( std::size_t n, char c ) : std::string ( n,c ) { }
	template <class InputIterator>
	PK_String( InputIterator first, InputIterator last ) : std::string( first,last ) { }

	void FormatVaArgs(const char * pszFmt, va_list args)
	{
        int len = vsnprintf(NULL, 0, pszFmt, args);
	    resize(len);
	    vsprintf((char*)c_str(), pszFmt, args);
    }

    
	PK_String Format1(const char * pszFmt, ...)
	{
        PK_String str;
		va_list args;
		va_start( args, pszFmt );
        str.FormatVaArgs(pszFmt, args);
        va_end( args );
        return str;
	}

	void Format(const char * pszFmt, ...)
	{
		va_list args;
		va_start( args, pszFmt );
        FormatVaArgs(pszFmt, args);
        va_end( args );
	}

	// Overloading para PK_String
	void Format(const PK_String &fmt, ...)
	{
		Format(fmt.c_str());
	}

	
	void Split(char chDelim, PK_Array<PK_String> &result) const
	{
        PK_List<PK_String> items;
		PK_String aux;
		char strDelim[2];
		strDelim[0] = chDelim;
		strDelim[1] = '\0';
		aux.assign(c_str());
		char * str = (char *)aux.c_str();
		char* token = strtok(str, strDelim);
		while(token != NULL)
		{
			items.Add(token);
			token = strtok(NULL, strDelim);
		}
        result.SetSize(items.GetCount());

        int i = 0;
        for(PK_ListIterator(PK_String) itor = items.Begin(); itor != items.End(); itor++)
        {
            result[i++] = (*itor);
        }
	}

    // Retira a primeira palavra da string e devolve
	inline PK_String ExtractWord(PK_String &delimiter)
	{
        return ExtractWord(delimiter.c_str());
    }

	// Retira a primeira palavra da string e devolve
	PK_String ExtractWord(const char * delimiter)
	{
		unsigned long len = length();
        PK_String sWord;
		char * str = (char *)c_str();
		char * pch = strtok (str, delimiter);
		if (pch != NULL)
		{
		  sWord = pch;
		  char * p = &str[strlen(pch)];
          if (p != &str[len])
		  {
		    p++;
		  }
          assign(p);
        }
        
		return sWord;
	}

    // Retira a ultima palavra da string e devolve
	inline PK_String ExtractLastWord(const PK_String &delimiter)
	{
        return ExtractLastWord(delimiter.c_str());
    }

	// Retira a ultima palavra da string e devolve
	PK_String ExtractLastWord(const char * delimiter)
	{
		PK_String sWord;
		if (length() > 0)
		{
			PK_String aux;
			aux.assign(c_str());
			char * p = (char *) aux.c_str();
			for(int i = (int)length() - 1; i >= 0; i--)
			{
				if (p[i] == delimiter[0])
				{
					sWord = &p[i + 1];
					p[i] = '\0';
					break;
				}
			}
            // Nao encontro o delimitador
            if (sWord.length() == 0)
            {
                // Colocamos toda a string como ultima palavra e limpamos a string
                sWord.assign(p);
                assign("");
            }
            else
            {
                assign(p);
            }
		}
		return sWord;
	}
	
	// trim from start
	static inline PK_String &LTrim(PK_String &s) {
			s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
			return s;
	}

	// trim from end
	static inline PK_String &RTrim(PK_String &s) {
			s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
			return s;
	}

	// trim from both ends
	static inline PK_String &Trim(PK_String &s) {
			return LTrim(RTrim(s));
	}

	// trim from both ends
	inline PK_String & Trim() 
    { 
        PK_String retStr = LTrim(RTrim(*this));
        assign(retStr);
        return *this;
    }
    
    inline bool Contains(const char *str) const
    {
        return (find(str) != std::string::npos);
    }

    inline void Replace(const PK_String & toSearch, const PK_String  & toReplace) 
    {
        Replace(toSearch.c_str(), toReplace.c_str());
    }

    void Replace(const char * toSearch, const char * toReplace) 
    {
        size_t pos = 0;
        while ((pos = find(toSearch, pos)) != std::string::npos) 
        {
             replace(pos, strlen(toSearch), toReplace);
             pos += strlen(toReplace);
        }
    }

    //
    PK_String ToUpper()
    {
        PK_String retStr = (*this);
        for(int i = 0; i < (int)retStr.length(); i++)
        {
            if (retStr[0] >='a' && retStr[0] <='z')
            {
                retStr[0] -= 32;
            }
        }
        return retStr;
    }

    //
    PK_String ToLower()
    {
        PK_String retStr = (*this);
        for(int i = 0; i < (int)retStr.length(); i++)
        {
            if (retStr[0] >='A' && retStr[0] <='Z')
            {
                retStr[0] += 32;
            }
        }
        return retStr;
    }

    //
    inline bool CompareTo(const PK_String &str, bool bCaseInsensitive) const
    {
        return CompareTo(str.c_str(), bCaseInsensitive);
    }

    //
    bool CompareTo(const char * str, bool bCaseInsensitive) const
    {
        if (!bCaseInsensitive)
        {
            return *this==str;
        }
        if (strlen(str) != length())
        {
            return false;
        }
        for(int i = 0; i < (int)length(); i++)
        {
            if ((*this)[i] == str[i])
            {
                continue;
            }
            if ((*this)[i] >= 'a' && (*this)[i] <= 'z')
            {
                if ((*this)[i] == str[i] + 32)
                {
                    continue;
                }
            }
            if ((*this)[i] >= 'A' && (*this)[i] <= 'Z')
            {
                if ((*this)[i] == str[i] - 32)
                {
                    continue;
                }
            }
            return false;
        }
        return true;
    }
};

} // namespace

#endif
