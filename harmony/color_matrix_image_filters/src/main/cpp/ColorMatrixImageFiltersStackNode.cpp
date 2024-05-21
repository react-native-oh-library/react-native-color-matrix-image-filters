#include "ColorMatrixImageFiltersStackNode.h"

#include <glog/logging.h>
#include <memory>
#include "RNOH/arkui/NativeNodeApi.h"

namespace rnoh {

ColorMatrixImageFiltersStackNode::ColorMatrixImageFiltersStackNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(
          ArkUI_NodeType::ARKUI_NODE_STACK)),
      m_stackNodeDelegate(nullptr) {
  maybeThrow(NativeNodeApi::getInstance()->registerNodeEvent(
      m_nodeHandle, NODE_ON_CLICK, 0, this));
}

void ColorMatrixImageFiltersStackNode::insertChild(ArkUINode& child, std::size_t index) {
  maybeThrow(NativeNodeApi::getInstance()->insertChildAt(
      m_nodeHandle, child.getArkUINodeHandle(), static_cast<int32_t>(index)));
}

void ColorMatrixImageFiltersStackNode::removeChild(ArkUINode& child) {
  maybeThrow(NativeNodeApi::getInstance()->removeChild(
      m_nodeHandle, child.getArkUINodeHandle()));
}

void ColorMatrixImageFiltersStackNode::setStackNodeDelegate(ColorMatrixImageFiltersStackNodeDelegate* stackNodeDelegate) {
  m_stackNodeDelegate = stackNodeDelegate;
}

void ColorMatrixImageFiltersStackNode::onNodeEvent(
    ArkUI_NodeEventType eventType,
    EventArgs& eventArgs) {
  if (eventType == ArkUI_NodeEventType::NODE_ON_CLICK &&
      eventArgs[3].i32 != 2) {
    onClick();
  }
}

void ColorMatrixImageFiltersStackNode::onClick() {
  if (m_stackNodeDelegate != nullptr) {
    m_stackNodeDelegate->onClick();
  }
}

ColorMatrixImageFiltersStackNode&
ColorMatrixImageFiltersStackNode::setMargin(float left, float top, float right, float bottom) {
  ArkUI_NumberValue value[] = {
      {.f32 = top}, {.f32 = right}, {.f32 = bottom}, {.f32 = left}};
  ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
  maybeThrow(NativeNodeApi::getInstance()->setAttribute(
      m_nodeHandle, NODE_MARGIN, &item));
  return *this;
}

ColorMatrixImageFiltersStackNode::~ColorMatrixImageFiltersStackNode() {
  NativeNodeApi::getInstance()->unregisterNodeEvent(
      m_nodeHandle, NODE_ON_CLICK);
}

ColorMatrixImageFiltersStackNode& ColorMatrixImageFiltersStackNode::setAlign(int32_t align) {
  ArkUI_NumberValue value[] = {{.i32 = align}};
  ArkUI_AttributeItem item = {.value = value, .size = 1};
  maybeThrow(NativeNodeApi::getInstance()->setAttribute(
      m_nodeHandle, NODE_STACK_ALIGN_CONTENT, &item));
  return *this;
}
} // namespace rnoh
