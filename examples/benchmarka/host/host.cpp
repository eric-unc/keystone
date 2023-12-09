#include "edge/edge_call.h"
#include "host/keystone.h"

#include <chrono>
#include <iostream>
#include <thread>

using namespace Keystone;

#define NUM_THREADS 8

char *program_path;
char *runtime_path;

void enclave_thread(int threadId){
  Enclave enclave;
  Params params;

  params.setFreeMemSize(1024 * 1024);
  params.setUntrustedMem(DEFAULT_UNTRUSTED_PTR, 1024 * 1024);

  enclave.init(program_path, runtime_path, params);

  enclave.registerOcallDispatch(incoming_call_dispatch);
  edge_call_init_internals(
      (uintptr_t)enclave.getSharedBuffer(), enclave.getSharedBufferSize());

  enclave.run();
}

int main(int argc, char** argv){
  program_path = argv[1];
  runtime_path = argv[2];

  std::thread threads[NUM_THREADS];

  auto startTime = std::chrono::high_resolution_clock::now();

  for(int i = 0; i < NUM_THREADS; i++){
    threads[i] = std::thread(enclave_thread, i);
  }

  for(int i = 0; i < NUM_THREADS; i++){
    threads[i].join();
  }

  auto endTime = std::chrono::high_resolution_clock::now();

  auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

  std::cout << "Elapsed Time: " << elapsedTime.count() << " ms" << std::endl;

  return 0;
}
