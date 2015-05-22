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
 * @file        scoped_resource.h
 * @author      Piotr Marcinkiewicz (p.marcinkiew@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation file of scoped resource pattern
 */
#ifndef CCHECKER_SCOPED_RESOURCE_H
#define CCHECKER_SCOPED_RESOURCE_H

#include <dpl/noncopyable.h>

namespace CCHECKER {
template<typename ClassPolicy>
class ScopedResource :
    private Noncopyable
{
  public:
    typedef typename ClassPolicy::Type ValueType;
    typedef ScopedResource<ClassPolicy> ThisType;

  protected:
    ValueType m_value;

  public:
    explicit ScopedResource(ValueType value) : m_value(value) { }

    ~ScopedResource()
    {
        ClassPolicy::Destroy(m_value);
    }

    ValueType Get() const
    {
        return m_value;
    }

    void Reset(ValueType value = ClassPolicy::NullValue())
    {
        ClassPolicy::Destroy(m_value);
        m_value = value;
    }

    ValueType Release()
    {
        ValueType value = m_value;
        m_value = ClassPolicy::NullValue();
        return value;
    }
    typedef ValueType ThisType::*UnknownBoolType;

    operator UnknownBoolType() const
    {
        return m_value == ClassPolicy::NullValue() ?
               0 : //0 is valid here because it converts to false
               &ThisType::m_value; //it converts to true
    }

    bool operator !() const
    {
        return m_value == ClassPolicy::NullValue();
    }
};
} // namespace CCHECKER

#endif // CCHECKER_SCOPED_RESOURCE_H
