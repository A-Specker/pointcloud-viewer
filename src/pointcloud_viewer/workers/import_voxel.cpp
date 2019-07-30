//spx

#include "import_voxel.h"
#include <external/libnpy/npy.hpp>

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

int voxel_dim(size_t total_size){
    double l = std::cbrt(total_size);
    if (!(round(l) == l)){
        throw std::runtime_error("Every Dimension of voxel has to be the same.");
    }
    return (int)l;
}

QSharedPointer<PointCloud> import_voxel_cloud(QWidget* parent, QString filepath){
    QFileInfo file(filepath);
    const std::string filepath_std = file.absoluteFilePath().toStdString();

    std::vector<unsigned long> shape;
    std::vector<float64_t > data; // TODO: hier waere was dynamisches schoener
    npy::LoadArrayFromNumpy(filepath_std, shape, data);

    int dim = voxel_dim(data.size());
    std::cout << dim << std::endl;


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


