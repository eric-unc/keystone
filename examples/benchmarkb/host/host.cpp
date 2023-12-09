#include "edge/edge_call.h"
#include "host/keystone.h"

#include <chrono>
#include <iostream>

using namespace Keystone;

int
main(int argc, char** argv) {
  auto startTime = std::chrono::high_resolution_clock::now();

  Enclave enclave;
  Params params;

  // TODO: adjusting this would be a good idea
  params.setFreeMemSize(1024 * 1024);
  params.setUntrustedMem(DEFAULT_UNTRUSTED_PTR, 1024 * 1024);

  enclave.init(argv[1], argv[2], params);

  enclave.registerOcallDispatch(incoming_call_dispatch);
  edge_call_init_internals(
      (uintptr_t)enclave.getSharedBuffer(), enclave.getSharedBufferSize());

  enclave.run();

  auto endTime = std::chrono::high_resolution_clock::now();

  auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

  std::cout << "Elapsed Time: " << elapsedTime.count() << " ms" << std::endl;

  return 0;
}
