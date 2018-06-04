#pragma once

#include <is/msgs/common.pb.h>
#include <is/msgs/wire.pb.h>
#include <is/msgs/utils.hpp>
#include <is/wire/core/logger.hpp>
#include <string>
#include <tuple>
#include "SpinGenApi/SpinnakerGenApi.h"
#include "Spinnaker.h"

namespace is {
namespace camera {

using namespace is::wire;
using namespace is::common;
namespace spn {
using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
}  // namespace spn

template <typename T>
struct OpRange {
  T min;
  T max;
  T to_ratio(T const& value) { return (value - min) / (max - min); }
  T to_value(T const& ratio) { return ratio * (max - min) + min; }
};  

Status internal_error(StatusCode code, std::string const& why);
Status writeability_error(std::string const& name);
Status readability_error(std::string const& name);
bool is_writable(spn::INode* node);
bool is_readable(spn::INode* node);

Status set_op_bool(spn::INodeMap& node_map, std::string const& name, bool value);
Status get_op_bool(spn::INodeMap& node_map, std::string const& name, bool* value);

Status set_op_enum(spn::INodeMap& node_map, std::string const& name, std::string const& value);
Status get_op_enum(spn::INodeMap& node_map, std::string const& name, std::string* valule);

Status set_op_int(spn::INodeMap& node_map, std::string const& name, int64_t value);
Status get_op_int(spn::INodeMap& node_map, std::string const& name, int64_t* value);
Status minmax_op_int(spn::INodeMap& node_map, std::string const& name, OpRange<int64_t>* range);

Status set_op_float(spn::INodeMap& node_map, std::string const& name, float value);
Status get_op_float(spn::INodeMap& node_map, std::string const& name, float* value);
Status minmax_op_float(spn::INodeMap& node_map, std::string const& name, OpRange<float>* range);

Status set_op_str(spn::INodeMap& node_map, std::string const& name, std::string const& value);
Status get_op_str(spn::INodeMap& node_map, std::string const& name, std::string* value);

Status execute_op(spn::INodeMap& node_map, std::string const& name);

}  // namespace camera
}  // namespace is