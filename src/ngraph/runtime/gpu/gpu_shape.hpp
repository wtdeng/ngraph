/*******************************************************************************
* Copyright 2017-2018 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#pragma once

#include <cstdio>
#include <stdexcept>
#include <vector>

#include "ngraph/axis_set.hpp"
#include "ngraph/coordinate.hpp"
#include "ngraph/shape.hpp"
#include "ngraph/strides.hpp"

namespace ngraph
{
    class Shape;
    /// \brief Shape for a tensor resident on GPU.
    class GPUShape : public std::vector<uint32_t>
    {
    public:
        GPUShape(const std::initializer_list<uint32_t>& axis_lengths)
            : std::vector<uint32_t>(axis_lengths)
        {
        }

        GPUShape(const std::vector<uint32_t>& axis_lengths)
            : std::vector<uint32_t>(axis_lengths)
        {
        }

        GPUShape(const GPUShape& axis_lengths)
            : std::vector<uint32_t>(axis_lengths)
        {
        }

        explicit GPUShape(size_t n, uint32_t initial_value = 0)
            : std::vector<uint32_t>(n, initial_value)
        {
        }

        template <class InputIterator>
        GPUShape(InputIterator first, InputIterator last)
            : std::vector<uint32_t>(first, last)
        {
        }

        GPUShape() {}
        GPUShape& operator=(const GPUShape& v)
        {
            static_cast<std::vector<uint32_t>*>(this)->operator=(v);
            return *this;
        }

        GPUShape& operator=(GPUShape&& v)
        {
            static_cast<std::vector<uint32_t>*>(this)->operator=(v);
            return *this;
        }

        GPUShape(const std::vector<size_t>& vec)
        {
            for (size_t const& size : vec)
            {
                if (size >> 32 != 0)
                {
                    throw std::runtime_error(
                        "Request exceeds the bitwidth available for GPUShapes (32)");
                }
                this->push_back(static_cast<uint32_t>(size));
            }
        }

        GPUShape(const Shape& shape)
        {
            for (size_t const& size : shape)
            {
                if (size >> 32 != 0)
                {
                    throw std::runtime_error(
                        "Request for Shape which exceeds the bitwidth available for GPUShapes "
                        "(32)");
                }
                this->push_back(static_cast<uint32_t>(size));
            }
        }

        GPUShape(const Strides& strides)
        {
            for (size_t const& size : strides)
            {
                if (size >> 32 != 0)
                {
                    throw std::runtime_error(
                        "Request for Strides which exceed the bitwidth available for GPUShapes "
                        "(32)");
                }
                this->push_back(static_cast<uint32_t>(size));
            }
        }

        GPUShape(const Coordinate& coord)
        {
            for (size_t const& size : coord)
            {
                if (size >> 32 != 0)
                {
                    throw std::runtime_error(
                        "Request for Coordinate which exceed the bitwidth available for GPUShapes "
                        "(32)");
                }
                this->push_back(static_cast<uint32_t>(size));
            }
        }
    };
}
