//*****************************************************************************
// Copyright 2017-2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//*****************************************************************************

#include <memory>

#include "ngraph/node.hpp"

#include "ngraph/op/add.hpp"
#include "ngraph/op/constant.hpp"
#include "ngraph/op/exp.hpp"
#include "ngraph/op/log.hpp"

#include "utils/broadcasting.hpp"

#include "softplus.hpp"

namespace ngraph
{
    namespace onnx_import
    {
        namespace op
        {
            NodeVector softplus(const Node& node)
            {
                auto data = node.get_ng_inputs().at(0);

                std::shared_ptr<ngraph::Node> one_node = std::make_shared<ngraph::op::Constant>(
                    data->get_element_type(), Shape{}, std::vector<double>{1});
                one_node = make_broadcast_node(one_node, data->get_shape());

                return {std::make_shared<ngraph::op::Log>(std::make_shared<ngraph::op::Exp>(data) +
                                                          one_node)};
            }

        } // namespace op

    } // namespace onnx_import

} // namespace ngraph
