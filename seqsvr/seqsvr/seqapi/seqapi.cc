#include "seqapi/seqapi.h"

#include <iostream>

#include "proto/cc/seqsvr.pb.h"
#include "nebula/net/zproto/api_message_box.h"

#include "nebula/net/rpc/zrpc_service_util.h"
#include "nebula/net/net_engine_manager.h"
#include "nebula/base/readline_gets.h"
// #include "nebula/nebula/base/readline_gets.h"

#include "seqapi/seqapi_command_handler.h"  //maybe error
// #include "seqsvr/seqapi/seqapi_command_handler.h"

#include "nebula/base/logger/glog_util.h"
#include "nebula/base/initializer.h"
// #include "nebula/nebula/base/logger/glog_util.h"

bool Seqapi::Initialize() {
  RegisterService("alloc_client", "rpc_client", "zrpc");

  return BaseServer::Initialize();
}

bool Seqapi::Run() {
  try {
    nebula::NetEngineManager::GetInstance()->Start();
  } catch (std::exception& e) {
    LOG(ERROR) << "Run - catch exception: " << e.what();
    return false;
  } catch (...) {
    LOG(ERROR) << "Run - catch  a invalid exception";
    return false;
  }

  BaseDaemon::Run();
  DoCommandLineLoop();
  // DoCommandLineLoop(userid);

  nebula::NetEngineManager::GetInstance()->Stop();
  return true;
}

// void Seqapi::DoCommandLineLoop(std::string& userid) {
void Seqapi::DoCommandLineLoop() {
  try {
    while (true) {
      auto line = ReadlineGets("nebula-im> ");
      // sleep(3) std::string line("fetch_next_seq 112233");
      // std::string line = cmdline;
      // if (userid.empty()) {
      //   LOG(ERROR) << "USER ID INPUT empty ";
      // }
      // std::string line("fetch_next_seq ");
      if (line.empty()) {
        continue;
      }
      // line = line + userid;

      std::vector<folly::StringPiece> cmds;
      folly::split(" ", line, cmds);

      if (-2 == DoClientCommand(cmds)) {
        break;
      }
    }
  } catch (const std::exception& e) {
    std::cout << "DoCommandLineLoop - " << folly::exceptionStr(e) << std::endl;
  }
}

int main(int argc, char* argv[]) { return nebula::DoMain<Seqapi>(argc, argv); }

// extern "C" int mycmd() {
int mycmd() {
  // int cmd() {
  // nebula::DoMain<Seqapi>(size, cmdline);
  // nebula::LogInitializer::Initialize("seqapi");
  int argc = 1;
  char* argv[1];
  argv[0] = {"seqapi"};
  // return nebula::DoMain<Seqapi>(argc, argv);
  // Seqapi a;
  std::cout << "mycmd() " << std::endl;
  return 0;
}
