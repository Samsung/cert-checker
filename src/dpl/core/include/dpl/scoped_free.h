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
 * @file        scoped_free.h
 * @author      Przemyslaw Dobrowolski (p.dobrowolsk@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation file of scoped free RAII
 */

#ifndef CCHECKER_SCOPED_FREE_H
#define CCHECKER_SCOPED_FREE_H

#include <malloc.h>
#include <cstddef>

#include <dpl/scoped_resource.h>

namespace CCHECKER {
template<typename Class>
struct ScopedFreePolicy
{
    typedef Class* Type;
    static Type NullValue()
    {
        return NULL;
    }
    static void Destroy(Type ptr)
    {
        free(ptr);
    }
};

template<typename Memory>
class ScopedFree : public ScopedResource<ScopedFreePolicy<Memory> >
{
    typedef ScopedFreePolicy<Memory> Policy;
    typedef ScopedResource<Policy> BaseType;

  public:
    explicit ScopedFree(Memory *ptr = Policy::NullValue()) : BaseType(ptr) { }
};
} // namespace CCHECKER

#endif // CCHECKER_SCOPED_FREE_H
