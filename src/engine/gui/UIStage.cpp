#include <bits/unique_ptr.h>
#include "UIStage.h"

void UIStage::setStrategy(Strategy* strategy) {
    UIStage::strategy.reset(strategy);
}
