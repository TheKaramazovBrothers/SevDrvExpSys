#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "PrmVarTable.h"
#include "PrmConfigService.h"
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
    void InitServoCtlTask();
private slots:
    void OnNavgTreeItemClicked(QTreeWidgetItem * item);

    void onWritePrmButtonclicked(bool checked = false);
    void onLoadPrmButtonclicked(bool checked = false);
    void onSavePrmButtonclicked(bool checked = false);
private:
    Ui::MainWindow *ui;
    PlotUnitGraph   *uiPlot;
    QWidget         *wPlot;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
private:
    SevPrmVarRamTable      *m_ram_obj_tbl;
    SevPrmFlashTable       *m_flash_obj_tbl;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
private:
    QAction         *m_actnDisNet;
    QAction         *m_actnConnect;
    QAction         *m_actnDownload;
    QAction         *m_actnUpload;
    QAction         *m_actnConfig;
    QAction         *m_actnSave;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
    QTreeWidget *    treewidgetNav;
    ConfigService *  m_prm_service;
//××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××××
};

#endif // MAINWINDOW_H
