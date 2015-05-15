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
 * @file        app.h
 * @author      Janusz Kozerski (j.kozerski@samsung.com)
 * @version     1.0
 * @brief       This file is the implementation of app struct
 */
#ifndef CCHECKER_APP_H
#define CCHECKER_APP_H

#include <string>
#include <vector>
#include <sys/types.h>

namespace CCHECKER {

struct app_t {
    enum class verified_t : int {
        NO      = 0,
        YES     = 1,
        UNKNOWN = 2
    };

    int32_t                  check_id;
    std::string              app_id;
    std::string              pkg_id;
    uid_t                    uid;
    std::vector<std::string> certificates;
    verified_t               verified;

    app_t(void);
    std::string str(void) const;
};

} //CCHECKER

#endif //CCHECKER_APP_H
