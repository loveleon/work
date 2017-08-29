#include "capi.h"
extern "C" int cmd() {
  nebula::LogInitializer::Initialize("seqapi");
  Seqapi daemon;
  daemon.DoMain();
}