#ifndef __IS_CAMERA_GATEWAY_HPP__
#define __IS_CAMERA_GATEWAY_HPP__

#include <chrono>
#include <memory>

#include <google/protobuf/empty.pb.h>
#include <is/msgs/camera.pb.h>
#include <is/msgs/common.pb.h>
#include <is/msgs/utils.hpp>
#include <is/wire/core.hpp>
#include <is/wire/core/status.hpp>
#include <is/wire/rpc.hpp>
#include <is/wire/rpc/log-interceptor.hpp>
#include "is/camera-drivers/interface/camera-driver.hpp"

#define is_assert_set(failable)                    \
  do {                                             \
    auto status = failable;                        \
    if (status.code() != is::wire::StatusCode::OK) \
      return status;                               \
  } while (0)

#define is_assert_get(failable, releaser)                                                                    \
  do {                                                                                                       \
    auto status = failable;                                                                                  \
    if (status.code() != is::wire::StatusCode::OK && status.code() != is::wire::StatusCode::UNIMPLEMENTED) { \
      return status;                                                                                         \
    }                                                                                                        \
    if (status.code() == is::wire::StatusCode::UNIMPLEMENTED) {                                              \
      releaser;                                                                                              \
    }                                                                                                        \
  } while (0)

namespace is {
namespace camera {

using namespace is::common;
using namespace is::vision;

struct CameraGateway {
  CameraGateway(CameraDriver* impl);
  void run(std::string const& uri, unsigned int const& id, std::string const& zipkin_host, uint32_t const& zipkin_port,
           is::vision::CameraConfig const& initial_config);

 private:
  Status set_configuration(CameraConfig const& config);
  Status get_configuration(FieldSelector const& field_selector, CameraConfig* camera_config);

  CameraDriver* driver;
};

}  // namespace camera
}  // namespace is

#endif  // __IS_GW_CAMERA_HPP__