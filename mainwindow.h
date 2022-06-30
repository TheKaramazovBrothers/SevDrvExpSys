#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include "ui_plotunitgraph.h"
#include "plotunitgraph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void createActions();
    void initNavgTree();
private:
    Ui::MainWindow *ui;
    PlotUnitGraph   *uiPlot;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    QAction         *m_actnDisNet;
    QAction         *m_actnConnect;
    QAction         *m_actnDownload;
    QAction         *m_actnUpload;
    QAction         *m_actnConfig;
    QAction         *m_actnSave;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    QTreeWidget *    treewidgetNav;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
};

#endif // MAINWINDOW_H
