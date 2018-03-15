#include "singleshot.h"
#include "utils.h"

SingleShot::SingleShot(ChannelManager *channelMan) :
    _channelMan(channelMan),
    activateAction("Activate SingleShot", this),
    toolBar("SingleShot Toolbar")
{
    activateAction.setToolTip("Pause When Edge Detected");
    activateAction.setText("Single Shot");
    activateAction.setCheckable(true);

    edgeOptionList.addItem("Rising");
    edgeOptionList.addItem("Falling");
    edgeOptionList.addItem("Rise or Fall");

    thresholdLevel.setToolTip("Threshold Level");
    thresholdLevel.setRange(-1e6, 1e6);

    toolBar.addWidget(&edgeOptionList);
    toolBar.addWidget(&thresholdLevel);
    toolBar.addAction(&activateAction);
    toolBar.setObjectName("singleShotToolBar");

    connect(&activateAction, SIGNAL(toggled(bool)),
            this, SLOT(onActivateToggleAction(bool)));

    QObject::connect(&edgeOptionList, SELECT<int>::OVERLOAD_OF(&QComboBox::activated),
            this, &SingleShot::onEdgeChange);

    QObject::connect(&thresholdLevel, SELECT<int>::OVERLOAD_OF(&QSpinBox::valueChanged),
            this, &SingleShot::onThresholdValueChange);
}

SingleShot::~SingleShot()
{

}

QToolBar *SingleShot::getToolBar()
{
    return &toolBar;
}

void SingleShot::checkEdgeTransition()
{
    if (!state) {
        return;
    }

    FrameBuffer *holdBuffer = _channelMan->channelBuffer(0);
    double midData = holdBuffer->sample(holdBuffer->size()/2),
           beforeMidData = holdBuffer->sample(holdBuffer->size()/2-1);
    bool triggered = false;

    switch (edgeState)
    {
    case Rising:
        if (midData > threshold && beforeMidData <= threshold) {
            triggered = true;
        }
        break;
    case Falling:
        if (midData < threshold && beforeMidData >= threshold) {
            triggered = true;
        }
        break;
    case RiseOrFall:
        if (midData > threshold && beforeMidData <= threshold) {
            triggered = true;
        }

        if (midData < threshold && beforeMidData >= threshold) {
            triggered = true;
        }

        break;
    }

    if (triggered) {
        activateAction.setChecked(false);
        emit singleShotPause();
    }
}

void SingleShot::onActivateToggleAction(bool state)
{
    this->state = state;
}

void SingleShot::onThresholdValueChange(int newThreshold)
{
    threshold = newThreshold;
}

void SingleShot::onEdgeChange(int newEdge)
{
    edgeState = newEdge;
}
