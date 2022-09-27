/*
 * Copyright 2021 The Modelbox Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <modelbox/flowunit_builder.h>

#include <utility>

namespace modelbox {

RegFlowUnitFactory::RegFlowUnitFactory(std::shared_ptr<FlowUnitBuilder> builder)
    : builder_(std::move(builder)) {
  auto desc = std::make_shared<FlowUnitDesc>();
  builder_->Probe(unit_type_, desc);
  unit_name_ = desc->GetFlowUnitName();
}

std::map<std::string, std::shared_ptr<FlowUnitDesc>>
RegFlowUnitFactory::FlowUnitProbe() {
  std::map<std::string, std::shared_ptr<FlowUnitDesc>> flowunit_desc_map;
  auto desc = std::make_shared<FlowUnitDesc>();
  std::string unit_type;
  builder_->Probe(unit_type, desc);
  flowunit_desc_map[unit_name_] = desc;
  return flowunit_desc_map;
}

std::string RegFlowUnitFactory::GetFlowUnitFactoryType() { return unit_type_; }

std::string RegFlowUnitFactory::GetFlowUnitFactoryName() { return unit_name_; }

std::shared_ptr<FlowUnit> RegFlowUnitFactory::CreateFlowUnit(
    const std::string &unit_name, const std::string &unit_type) {
  return builder_->Build();
}

}  // namespace modelbox