//
//  EasyString.hpp
//
//  Created by dylan on 12/2/17.
//  Copyright © 2017 Dylan McSweeney. All rights reserved.
//

#pragma once

#include <string>
#include <regex>

class EasyString {
public:
    EasyString():
        m_str()
    {}
    
    EasyString(const char *str):
        m_str(str)
    {}
    
    EasyString(const std::string &str):
        m_str(str)
    {}
    
    EasyString(std::string &&str):
    	m_str(std::move(str))
    {}
    
    EasyString& operator=(const char *rhs)
    {
        m_str = rhs;
        return *this;
    }
    
    EasyString& operator=(const std::string &rhs)
    {
        m_str = rhs;
        return *this;
    }
    
    EasyString& operator=(std::string &&rhs)
    {
        m_str = std::move(rhs);
        return *this;
    }
    
    const std::string& str() const
    {
        return m_str;
    }
    
    const char * c_str() const
    {
        return m_str.c_str();
    }
    
    template<typename strtype>
    bool match(strtype&& regex) const
    {
        return std::regex_match(m_str, std::regex(std::forward<strtype>(regex), std::regex_constants::extended));
    }
    
    template<>
    bool match<const EasyString&>(const EasyString& regex) const
    {
        return match(regex.str());
    }
    
private:
    std::string m_str;
    
    //friends
    friend EasyString operator+(const EasyString& lhs, const EasyString& rhs);
    friend EasyString operator+(const EasyString& lhs, const std::string& rhs);
    friend EasyString operator+(const std::string& lhs, const EasyString& rhs);
    template<typename strtype>
    friend EasyString& operator+=(EasyString& lhs, strtype&& rhs);
    friend std::string& operator+=(std::string& lhs, const EasyString& rhs);
    template<typename strtype>
    friend bool operator==(const EasyString& lhs, strtype&& rhs);
    friend std::ostream& operator<<(std::ostream& os, const EasyString& estr);
    friend std::istream& operator>>(std::istream& is, EasyString& estr);
};

EasyString operator+(const EasyString& lhs, const EasyString& rhs)
{
    return EasyString(lhs.m_str + rhs.m_str);
}

EasyString operator+(const EasyString& lhs, const std::string& rhs)
{
    return EasyString(lhs.m_str + rhs);
}

EasyString operator+(const std::string& lhs, const EasyString& rhs)
{
    return EasyString(lhs + rhs.m_str);
}

template<typename strtype>
EasyString& operator+=(EasyString& lhs, strtype&& rhs)
{
    lhs.m_str += std::forward<strtype>(rhs);
    return lhs;
}

template<>
EasyString& operator+=<const EasyString&>(EasyString& lhs, const EasyString& rhs)
{
    return lhs += rhs.m_str;
}

std::string& operator+=(std::string& lhs, const EasyString& rhs)
{
    lhs += rhs.m_str;
    return lhs;
}

template<typename strtype>
bool operator==(const EasyString& lhs, strtype&& rhs)
{
    return lhs.m_str == rhs;
}

std::ostream& operator<<(std::ostream& os, const EasyString& estr)
{
    os << estr.m_str;
    return os;
}

std::istream& operator>>(std::istream& is, EasyString& estr)
{
    is >> estr.m_str;
    return is;
}
