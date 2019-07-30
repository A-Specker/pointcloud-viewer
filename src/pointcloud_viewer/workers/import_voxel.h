//spx
#ifndef POINTCLOUD_VIEWER_IMPORT_VOXEL_H
#define POINTCLOUD_VIEWER_IMPORT_VOXEL_H

#include <pointcloud/pointcloud.hpp>
#include <QObject>

QSharedPointer<PointCloud> import_voxel_cloud(QWidget* parent, QString file);


#endif //POINTCLOUD_VIEWER_IMPORT_VOXEL_H
