/*
 * Copyright (c) 2015 Samsung Electronics Co., Ltd All Rights Reserved
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
 * @file        app.cpp
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation of app struct
 */

#include <sstream>
#include <string>
#include <vector>
#include <sys/types.h>

#include <app.h>

namespace CCHECKER {

app_t::app_t(void):
        check_id(-1),   // -1 as invalid check_id - assume that in database
                        // all check_ids will be positive
        uid((uid_t)-1), // (uid_t)-1 (0xFF) is defined to be invalid uid. According
                        // to chown manual page, you cannot change file group of owner
                        // to (uid_t)-1, so we'll use it as initial, invalid value.
        verified(verified_t::UNKNOWN)
{}

std::ostream & operator<< (std::ostream &out, const app_t &app)
{
    out << "app: " << app.app_id << ", pkg: " << app.pkg_id << ", uid: " << app.uid;
    return out;
}

std::string app_t::str() const
{
    std::stringstream ss;
    ss << this;
    return ss.str();
}

} //CCHECKER
