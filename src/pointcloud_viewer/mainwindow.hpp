#ifndef POINTCLOUDVIEWER_MAINWINDOW_HPP_
#define POINTCLOUDVIEWER_MAINWINDOW_HPP_

#include <QMainWindow>
#include <QListView>
#include <QUrl>
#include <QDropEvent>

#include <pointcloud_viewer/viewport.hpp>
#include <pointcloud_viewer/pointcloud_inspector.hpp>
#include <pointcloud_viewer/flythrough/flythrough.hpp>
#include <pointcloud_viewer/workers/offline_renderer.hpp>

class KeypointList;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
  bool noninteractive = false;

  MainWindow();
  ~MainWindow();

private:
  Viewport viewport;
  Flythrough flythrough;
  PointCloudInspector pointDataInspector;

  RenderSettings renderSettings = RenderSettings::defaultSettings();

  KeypointList* keypointList;

  void handleApplicationArguments();
  void initMenuBar();
  void initDocks();

  QDockWidget* initAnimationDock();
  QDockWidget* initRenderDock();
  QDockWidget* initDataInspectionDock();

  void importPointcloudLayer();
  void openAboutDialog();

  void exportCameraPath();
  void importCameraPath();
  void jumpToKeypoint(const QModelIndex& modelIndex);

  void offline_render_with_ui();
  bool offline_render();

protected:
  void dropEvent(QDropEvent *ev);

  void dragEnterEvent(QDragEnterEvent *ev);
};


#endif // POINTCLOUDVIEWER_MAINWINDOW_HPP_
