//spx

#include "import_voxel.h"
#include <external/cnpy/cnpy.h>

#include <pointcloud_viewer/workers/import_pointcloud.hpp>
//#include <pointcloud_viewer/mainwindow.hpp>
#include <pointcloud/importer/abstract_importer.hpp>
#include <core_library/print.hpp>
#include <core_library/types.hpp>

#include <QDebug>
#include <QFileInfo>
#include <QThread>
#include <QMessageBox>
#include <QCoreApplication>
#include <QProgressDialog>
#include <QAbstractEventDispatcher>
#include <fstream>


QSharedPointer<PointCloud> import_voxel_cloud(QWidget* parent, QString filepath){
    QFileInfo file(filepath);
    const std::string filepath_std = file.absoluteFilePath().toStdString();

    cnpy::NpyArray voxels = cnpy::npy_load(filepath_std);
//    std::cout << voxels.num_vals << std::endl;
//    if(!file.exists())
//    {
//        QMessageBox::warning(parent, "Not existing file", QString("The given file <%0> does not exist!").arg(filepath));
//        return failed();
//    }
//
//    const std::string filepath_std = file.absoluteFilePath().toStdString();
//
//    if(!file.isReadable())
//    {
//        QMessageBox::warning(parent, "Can't existing file", QString("Could not open the file <%0> for reading.").arg(filepath));
//        return failed();
//    }
//
//    const QString suffix = file.suffix();
//
//    QSharedPointer<AbstractPointCloudImporter> importer = AbstractPointCloudImporter::importerForSuffix(suffix, filepath_std);
//
//    if(!importer)
//    {
//        QMessageBox::warning(parent, "Unexpected file format", QString("Unexpected file format '%0'.").arg(suffix));
//        return failed();
//    }
    return QSharedPointer<PointCloud>(new PointCloud);

}
