#ifndef SEQAPI_SEQAPI_COMMAND_HANDLER_H_
#define SEQAPI_SEQAPI_COMMAND_HANDLER_H_

#include <vector>
#include <folly/Range.h>

int DoClientCommand(const std::vector<folly::StringPiece>& command_lines);

#endif