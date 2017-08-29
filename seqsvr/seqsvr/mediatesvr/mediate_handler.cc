/*
 *  Copyright (c) 2016, https://github.com/nebula-im
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

#include "mediatesvr/mediate_handler.h"

#include "proto/cc/seqsvr.pb.h"
#include "nebula/net/zproto/api_message_box.h"
#include "base/message_handler_util.h"
#include "base/router_table.h"

// REGISTER_HTTP_HANDLER(UpdateRouteTable, "/mediate/router/update",
// UpdateRouteTable);
REGISTER_HTTP_HANDLER(UpdateRouteTable, "/123", UpdateRouteTable);
REGISTER_HTTP_HANDLER(RemoveAllocSvr, "/456", RemoveAllocSvr);

// 初始化路由表
void UpdateRouteTable(const proxygen::HTTPMessage& headers,
                      folly::IOBufQueue* body, proxygen::ResponseBuilder* r) {
  zproto::UpdateRouteTableReq update_route_table_req;

  LOG(INFO) << "headers:" << sizeof(headers);
  LOG(INFO) << "client ip:" << headers.getClientIP();

  LOG(INFO) << "client port:" << headers.getClientPort();
  LOG(INFO) << "getDstIP: " << headers.getDstIP();
  LOG(INFO) << "getDstPort:" << headers.getDstPort();
  LOG(INFO) << "getMethodString:" << headers.getMethodString();
  LOG(INFO) << "getURL:" << headers.getURL();
  LOG(INFO) << "getPath:" << headers.getPath();
  LOG(INFO) << "R:" << r;
  update_ip_list(ipvec, headers.getClientIP());

  RouteTable table;
  RouteTable::MakeRouteTable(table, ipvec);
  LOG(INFO) << "ipvec.size():" << ipvec.size();
  table.SerializeToRouter(update_route_table_req.mutable_router());

  ZRpcClientCall<zproto::UpdateRouteTableRsp>(
      "store_client", MakeRpcRequest(update_route_table_req),
      [&](std::shared_ptr<ApiRpcOk<zproto::UpdateRouteTableRsp>> rpc_ok,
          ProtoRpcResponsePtr rpc_error) -> int {
        if (rpc_error) {
          LOG(ERROR) << "LoadMaxSeqsDataReq - rpc_error: "
                     << rpc_error->ToString();
          // OnLoad("");
        } else {
          LOG(INFO) << "LoadMaxSeqsDataReq - load_max_seqs_data_rsp: "
                    << rpc_ok->ToString();
          // OnLoad((*load_max_seqs_data_rsp)->max_seqs());
        }
        return 0;
      });

  std::string json("{\"status\": \"OK\"}\n");
  std::unique_ptr<folly::IOBuf> json_string =
      folly::IOBuf::copyBuffer(json.c_str(), json.length());
  r->header("Content-Type", "application/json;charset=utf-8")
      .body(std::move(json_string));
}

// AllocSvr加入和移除集群
void AddAllocSvr(const proxygen::HTTPMessage& headers, folly::IOBufQueue*,
                 proxygen::ResponseBuilder* r) {}

void RemoveAllocSvr(const proxygen::HTTPMessage& headers, folly::IOBufQueue*,
                    proxygen::ResponseBuilder* r) {
  zproto::UpdateRouteTableReq update_route_table_req;

  if (ipvec.empty()) {
    ipvec.push_back(headers.getClientIP());
  } else {
    std::vector<std::string>::iterator it =
        find(ipvec.begin(), ipvec.end(), headers.getClientIP());
    if (it == ipvec.end()) ipvec.push_back(headers.getClientIP());
  }

  // LOG(INFO) << "getDstIP: " << headers.getDstIP();
  // LOG(INFO) << "getDstPort:" << headers.getDstPort();
  // LOG(INFO) << "getMethodString:" << headers.getMethodString();
  // LOG(INFO) << "getURL:" << headers.getURL();
  // LOG(INFO) << "getPath:" << headers.getPath();

  remove_ip_node(ipvec, headers.getClientIP());

  RouteTable table;
  RouteTable::MakeRouteTable(table, ipvec);
  LOG(INFO) << "ipvec.size():" << ipvec.size();
  table.SerializeToRouter(update_route_table_req.mutable_router());

  ZRpcClientCall<zproto::UpdateRouteTableRsp>(
      "store_client", MakeRpcRequest(update_route_table_req),
      [&](std::shared_ptr<ApiRpcOk<zproto::UpdateRouteTableRsp>> rpc_ok,
          ProtoRpcResponsePtr rpc_error) -> int {
        if (rpc_error) {
          LOG(ERROR) << "LoadMaxSeqsDataReq - rpc_error: "
                     << rpc_error->ToString();
          // OnLoad("");
        } else {
          LOG(INFO) << "LoadMaxSeqsDataReq - load_max_seqs_data_rsp: "
                    << rpc_ok->ToString();
          // OnLoad((*load_max_seqs_data_rsp)->max_seqs());
        }
        return 0;
      });

  std::string json("{\"status\": \"OK\"}\n");
  std::unique_ptr<folly::IOBuf> json_string =
      folly::IOBuf::copyBuffer(json.c_str(), json.length());
  r->header("Content-Type", "application/json;charset=utf-8")
      .body(std::move(json_string));
}

static bool update_ip_list(std::vector<std::string>& ipvec, std::string upIp) {
  if (upIp.empty()) upIp = "127.0.0.1";
  if (ipvec.empty()) {
    ipvec.push_back(upIp);
  } else {
    std::vector<std::string>::iterator it =
        find(ipvec.begin(), ipvec.end(), upIp);
    if (it == ipvec.end()) ipvec.push_back(upIp);
  }
  return true;
}

static bool remove_ip_node(std::vector<std::string>& ipvec, std::string dwIp) {
  if (dwIp.empty()) dwIp = "127.0.0.1";
  if (!ipvec.empty()) {
    for (auto it = ipvec.begin(); it != ipvec.end();) {
      if (*it == dwIp)
        it = ipvec.erase(it);
      else
        ++it;
      }
  }
}