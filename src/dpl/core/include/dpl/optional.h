/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/*
 * @file        optional_value.h
 * @author      Lukasz Wrzosek (l.wrzosek@samsung.com)
 * @version     1.0
 */

#ifndef CCHECKER_OPTIONAL_H
#define CCHECKER_OPTIONAL_H

#include <dpl/exception.h>

namespace CCHECKER {
template <typename Type>
class Optional
{
    class Exception
    {
      public:
        DECLARE_EXCEPTION_TYPE(CCHECKER::Exception, Base)
        DECLARE_EXCEPTION_TYPE(Base, NullReference)
    };

  public:
    Optional() :
        m_null(true),
        m_value()
    {}

    Optional(const Type& t) :
        m_null(false),
        m_value(t)
    {}

    bool IsNull() const
    {
        return m_null;
    }

    Type& operator*()
    {
        if (m_null) {
            Throw(typename Exception::NullReference);
        }
        return m_value;
    }

    const Type& operator*() const
    {
        if (m_null) {
            Throw(typename Exception::NullReference);
        }
        return m_value;
    }

    const Type* operator->() const
    {
        if (m_null) {
            Throw(typename Exception::NullReference);
        }
        return &m_value;
    }

    Type* operator->()
    {
        if (m_null) {
            Throw(typename Exception::NullReference);
        }
        return &m_value;
    }

    bool operator!() const
    {
        return m_null;
    }

    Optional<Type>& operator=(const Type& other)
    {
        m_null = false;
        m_value = other;
        return *this;
    }

    bool operator==(const Optional<Type>& aSecond) const
    {
        return LogicalOperator<true>(*this, aSecond,
                                     std::equal_to<Type>(), std::equal_to<bool>());
    }

    bool operator==(const Type& aSecond) const
    {
        return Optional<Type>(aSecond) == *this;
    }

    bool operator!=(const Optional<Type>& aSecond) const
    {
        return !(*this == aSecond);
    }

    bool operator<(const Optional<Type>& aSecond) const
    {
        return LogicalOperator<false>(*this, aSecond,
                                      std::less<Type>(), std::less<bool>());
    }

    bool operator>(const Optional<Type>& aSecond) const
    {
        return LogicalOperator<false>(*this, aSecond,
                                      std::greater<Type>(), std::greater<bool>());
    }

    bool operator<=(const Optional<Type>& aSecond) const
    {
        return *this == aSecond || *this < aSecond;
    }

    bool operator>=(const Optional<Type>& aSecond) const
    {
        return *this == aSecond || *this > aSecond;
    }

    static Optional<Type> Null;

  private:
    bool m_null;
    Type m_value;

    template <bool taEquality, typename taComparator, typename taNullComparator>
    static bool LogicalOperator(const Optional<Type>& aFirst,
                                const Optional<Type>& aSecond,
                                taComparator aComparator,
                                taNullComparator aNullComparator)
    {
        if (aFirst.m_null == aSecond.m_null) {
            if (aFirst.m_null) {
                return taEquality;
            } else {
                return aComparator(aFirst.m_value, aSecond.m_value);
            }
        } else {
            return aNullComparator(aFirst.m_null, aSecond.m_null);
        }
    }
};

template<typename Type>
Optional<Type> Optional<Type>::Null = Optional<Type>();
} //namespace CCHECKER

template<typename Type>
std::ostream& operator<<(std::ostream& aStream,
                         const CCHECKER::Optional<Type>& aOptional)
{
    if (aOptional.IsNull()) {
        return aStream << "null optional";
    } else {
        return aStream << *aOptional;
    }
}

#endif // CCHECKER_OPTIONAL_VALUE_H
