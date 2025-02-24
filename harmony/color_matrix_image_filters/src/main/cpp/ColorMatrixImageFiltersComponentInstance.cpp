/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "ColorMatrixImageFiltersComponentInstance.h"
#include "Props.h"
#include "RNOH/arkui/NativeNodeApi.h"
namespace rnoh {

    ColorMatrixImageFiltersComponentInstance::ColorMatrixImageFiltersComponentInstance(Context context)
        : CppComponentInstance(std::move(context)) {
    }

    void ColorMatrixImageFiltersComponentInstance::onChildInserted(ComponentInstance::Shared const &childComponentInstance, std::size_t index) {
        CppComponentInstance::onChildInserted(childComponentInstance, index);        
        m_colorMatrixImageFiltersNode.insertChild(childComponentInstance->getLocalRootArkUINode(), index);
    }

    ColorMatrixImageFiltersStackNode &ColorMatrixImageFiltersComponentInstance::getLocalRootArkUINode() { return m_colorMatrixImageFiltersNode; }

    void ColorMatrixImageFiltersComponentInstance::onChildRemoved(ComponentInstance::Shared const &childComponentInstance) {
        CppComponentInstance::onChildRemoved(childComponentInstance);
        m_colorMatrixImageFiltersNode.removeChild(childComponentInstance->getLocalRootArkUINode());
    }

    void ColorMatrixImageFiltersComponentInstance::onPropsChanged(SharedConcreteProps const &props) {
        CppComponentInstance::onPropsChanged(props);
        if(auto colorMatrixImageFiltersProps= std::dynamic_pointer_cast<const facebook::react::CMIFColorMatrixImageFilterProps>(props)){
             this->m_matrix = colorMatrixImageFiltersProps->matrix;
        }
    }

void ColorMatrixImageFiltersComponentInstance::finalizeUpdates() {
    std::vector<ComponentInstance::Shared> childNodes = findImageNode(getChildren());
    for (auto childNode : childNodes) {
        std::vector<ArkUI_NumberValue> value = {};
        for (auto matrix : this->m_matrix) {
            value.push_back({.f32 = static_cast<float>(matrix)});
        }
        ArkUI_AttributeItem item = {value.data(), static_cast<int32_t>(value.size())};
        NativeNodeApi::getInstance()->setAttribute(childNode->getLocalRootArkUINode().getArkUINodeHandle(),
                                                   NODE_IMAGE_COLOR_FILTER, &item);
    }
}

std::vector<ComponentInstance::Shared>
ColorMatrixImageFiltersComponentInstance::findImageNode(const std::vector<ComponentInstance::Shared> &childNodes) {
    std::vector<ComponentInstance::Shared> result;
    for (const auto &childNode : childNodes) {
        if (OH_ArkUI_NodeUtils_GetNodeType(childNode->getLocalRootArkUINode().getArkUINodeHandle()) ==
            ARKUI_NODE_IMAGE) {
            result.push_back(childNode);
        }
        auto nodeResults = findImageNode(childNode->getChildren());
        result.insert(result.end(), nodeResults.begin(), nodeResults.end());
    }
    return result;
}

} // namespace rnoh/
