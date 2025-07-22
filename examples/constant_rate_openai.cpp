#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "client_backend/openai/openai_client.h"

using namespace triton::perfanalyzer::clientbackend::openai;

std::string
LoadFile(const std::string& path)
{
  std::ifstream in(path);
  return std::string(
      (std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
}

int
main(int argc, char** argv)
{
  const std::string url = "http://localhost:5000";
  const std::string endpoint = "v1/chat/completions";
  std::string request_body = LoadFile("examples/inputs.json");

  ChatCompletionClient client(url, endpoint, true);

  auto on_response = [](InferResult* result) {
    std::vector<uint8_t> buf;
    if (result->RawData("", buf).IsOk()) {
      std::cout << std::string(buf.begin(), buf.end()) << std::endl;
    }
    delete result;
  };

  const double rate = 8.0;  // requests per second
  const size_t request_count = 64;
  auto period = std::chrono::duration<double>(1.0 / rate);

  for (size_t i = 0; i < request_count; ++i) {
    client.AsyncInfer(on_response, request_body, std::to_string(i), {});
    std::this_thread::sleep_for(period);
  }

  // Allow time for all responses to complete
  std::this_thread::sleep_for(std::chrono::seconds(5));
  return 0;
}
