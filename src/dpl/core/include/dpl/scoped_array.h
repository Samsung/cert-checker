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
/*!
 * @file        scoped_ptr.h
 * @author      Przemyslaw Dobrowolski (p.dobrowolsk@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation file of scoped array RAII
 */
#ifndef CCHECKER_SCOPED_ARRAY_H
#define CCHECKER_SCOPED_ARRAY_H

#include <cstddef>

#include <dpl/assert.h>
#include <dpl/scoped_resource.h>

namespace CCHECKER {
template<typename Class>
struct ScopedArrayPolicy
{
    typedef Class* Type;
    static Type NullValue()
    {
        return NULL;
    }
    static void Destroy(Type ptr)
    {
        delete[] ptr;
    }
};

template<typename Class>
class ScopedArray : public ScopedResource<ScopedArrayPolicy<Class> >
{
    typedef ScopedArrayPolicy<Class> Policy;
    typedef ScopedResource<Policy> BaseType;

  public:
    explicit ScopedArray(Class *ptr = Policy::NullValue()) : BaseType(ptr) { }

    Class &operator [](std::ptrdiff_t k) const
    {
        Assert(this->m_value != Policy::NullValue() &&
               "Dereference of scoped NULL array!");
        Assert(k >= 0 && "Negative array index");

        return this->m_value[k];
    }
};
} // namespace CCHECKER

#endif // CCHECKER_SCOPED_PTR_H
