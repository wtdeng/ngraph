// ----------------------------------------------------------------------------
// Copyright 2017 Nervana Systems Inc.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// ----------------------------------------------------------------------------

#pragma once

#include <exception>
#include <sstream>

#include "ngraph/descriptor/output.hpp"
#include "ngraph/pass/pass.hpp"

namespace ngraph
{
    namespace pass
    {
        template <typename LT>
        class AssignLayout : public CallGraphPass
        {
        public:
            virtual bool run_on_call_graph(std::list<std::shared_ptr<Node>>& nodes) override
            {
                for (const std::shared_ptr<Node>& node : nodes)
                {
                    try
                    {
                        for (const descriptor::Output& output : node->get_outputs())
                        {
                            auto tv = output.get_tensor_view();
                            if (nullptr == tv->get_tensor_view_layout())
                            {
                                auto layout = std::make_shared<LT>(*tv);
                                tv->set_tensor_view_layout(layout);
                            }
                        }
                    }
                    catch (const std::exception& e)
                    {
                        std::stringstream ss;
                        ss << "Error with node " << *node << ": ";
                        ss << e.what();
                        throw std::invalid_argument(ss.str());
                    }
                }
                return false;
            }
        };
    }
}