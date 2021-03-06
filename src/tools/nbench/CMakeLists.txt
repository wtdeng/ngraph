# ******************************************************************************
# Copyright 2017-2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ******************************************************************************

if (NGRAPH_CPU_ENABLE)
    set (SRC
        nbench.cpp
        ${PROJECT_SOURCE_DIR}/test/util/benchmark.cpp
    )

    add_executable(nbench ${SRC})
    add_dependencies(nbench ngraph cpu_backend)

    set(HEADER_SEARCH_DEFINES
        "NGRAPH_HEADERS_PATH=\"${NGRAPH_INCLUDE_PATH}\""
    )

    target_link_libraries(nbench ngraph cpu_backend)
    if (NGRAPH_GPU_ENABLE)
        target_link_libraries(nbench gpu_backend)
    endif()
    if (NGRAPH_INTERPRETER_ENABLE)
        target_link_libraries(nbench interpreter_backend)
    endif()

    include_directories("${PROJECT_SOURCE_DIR}/test")

    set_source_files_properties(nbench.cpp PROPERTIES COMPILE_DEFINITIONS "${HEADER_SEARCH_DEFINES}")
    install(TARGETS nbench RUNTIME DESTINATION ${NGRAPH_INSTALL_BIN})
endif()
