/*
 *  Copyright (c) 2016, https://github.com/zhatalk
 *  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MEDIATESVR_MEDIATE_HTTP_HANDLER_H_
#define MEDIATESVR_MEDIATE_HTTP_HANDLER_H_

#include "nebula/net/handler/http/http_request_handler.h"

// 初始化路由表
void UpdateRouteTable(const proxygen::HTTPMessage& headers,
                      folly::IOBufQueue* body, proxygen::ResponseBuilder* r);

void RemoveAllocSvr(const proxygen::HTTPMessage& headers,
                    folly::IOBufQueue* body, proxygen::ResponseBuilder* r);

// add
static std::vector<std::string> ipvec;
static bool update_ip_list(std::vector<std::string>& ipvec, std::string upIp);
static bool remove_ip_node(std::vector<std::string>& ipvec, std::string dwIp);
// vector has ip addresses
#endif  // MEDIATESVR_MEDIATE_HTTP_HANDLER_H_
