//spx

#ifndef POINTCLOUD_VIEWER_NPY_IMPORTER_H
#define POINTCLOUD_VIEWER_NPY_IMPORTER_H
#include <pointcloud/importer/abstract_importer.hpp>
#include <pointcloud/buffer.hpp>

#include <QVector>

/**
Implementation for loading npy files
*/
class CnpyImporter final : public AbstractPointCloudImporter
{
public:
    CnpyImporter(const std::string& input_file);

protected:
    bool import_implementation() override;

private:
    std::streamsize current_progress = 0;
};
#endif //POINTCLOUD_VIEWER_NPY_IMPORTER_H
