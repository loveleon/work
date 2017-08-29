#ifdef CLIENT_MYAPI_H_
#define CLIENT_MYAPI_H_
#include <folly/io/api/EventBase.h>

#include <vector>
#include <folly/Range.h>

// int DoClientCommand(const std::vector<folly::StringPiece>& command_lines);
int InitLogApi();
#endif