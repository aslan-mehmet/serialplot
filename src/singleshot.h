#ifndef SINGLESHOT_H
#define SINGLESHOT_H

#include <QObject>
#include <QAction>
#include <QToolBar>
#include <QComboBox>
#include <QSpinBox>

class SingleShot : public QObject
{
    Q_OBJECT
public:
    SingleShot();
    ~SingleShot();

    QToolBar *getToolBar();

private:
    bool state = false;
    enum EdgeState{Rising, Falling, RiseOrFall};
    int edgeState = 0;
    int threshold = 0;

    QAction activateAction;
    QComboBox edgeOptionList;
    QSpinBox thresholdLevel;
    QToolBar toolBar;

    void onEdgeChange(int newEdge);
    void onThresholdValueChange(int newThreshold);

private slots:
    void onActivateToggleAction(bool state);
};

#endif // SINGLESHOT_H
