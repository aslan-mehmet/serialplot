#include "singleshot.h"
#include "utils.h"
#include <iostream>

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
     std::cout << "checkEdgeTransition" << std::endl;
}

void SingleShot::onActivateToggleAction(bool state)
{
    std::cout << "activate toggle action" << state << std::endl;
    this->state = state;
}

void SingleShot::onThresholdValueChange(int newThreshold)
{
    std::cout << "new threshold val:" << newThreshold << std::endl;
    threshold = newThreshold;
}

void SingleShot::onEdgeChange(int newEdge)
{
    std::cout << "new edge val:" << newEdge << std::endl;
    edgeState = newEdge;
}
