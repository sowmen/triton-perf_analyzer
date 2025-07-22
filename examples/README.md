<!--
# Copyright (c) 2025, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
-->
# OpenAI constant rate example

This example sends asynchronous chat completion requests to an OpenAI API
compatible server at a constant rate. It uses the same client backend that
`perf_analyzer` relies on.

## Build

First build perf_analyzer and its libraries. A minimal build can be done from
the repository root:

```bash
mkdir build
cmake -B build -S .
cmake --build build -- -j8
```

After the build finishes, compile the example:

```bash
cmake -B build/examples -S examples -DCMAKE_PREFIX_PATH=$(pwd)/build/perf_analyzer/src/perf-analyzer-build
cmake --build build/examples -- -j8
```

The `CMAKE_PREFIX_PATH` argument lets CMake locate the libraries built with
perf_analyzer.

## Run

Start your OpenAI compatible server (for example `localhost:5000`) and run the
example binary:

```bash
build/examples/constant_rate_openai
```

The program reads `examples/inputs.json` and will issue 64 requests at a rate of
8 requests per second. Responses are printed to standard output.
