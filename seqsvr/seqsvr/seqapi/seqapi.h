#ifndef SEQAPI_SEQAPI_H_
#define SEQAPI_SEQAPI_H_
#include <folly/io/async/EventBase.h>

#include "nebula/net/base_server.h"

#include <gflags/gflags.h>

class Seqapi : public nebula::BaseServer {
 public:
  Seqapi() = default;
  ~Seqapi() override = default;

 protected:
  // from baseserver
  bool Initialize() override;
  bool Run() override;
  // docommandloop
  void DoCommandLineLoop();
  // void DoClientCommand(std::string& userid);
};

// #ifdef __cplusplus
// extern "C" {
// #endif
extern "C" int mycmd();

// #ifdef __cplusplus
// }
// #endif
#endif