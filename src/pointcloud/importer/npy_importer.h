//spx

#ifndef POINTCLOUD_VIEWER_NPY_IMPORTER_H
#define POINTCLOUD_VIEWER_NPY_IMPORTER_H
#include <pointcloud/importer/abstract_importer.hpp>
#include <pointcloud/buffer.hpp>
//#include <pointcloud_viewer/mainwindow.hpp>
#include <QVector>
#include <pointcloud_viewer/voxel_thresh.h>
/**
Implementation for loading npy files
*/

class NpyImporter final : public AbstractPointCloudImporter
{
public:
    NpyImporter(const std::string& input_file);

protected:
    const float VOX_SCALE = 0.1f;
    bool import_implementation() override;
    static int voxel_dim(size_t total_size);

private:
    std::streamsize current_progress = 0;
    std::vector<float64_t> map_idx_to_coords(size_t idx, size_t dim);
    std::vector<int> val_to_heatmap(float64_t val);
};
#endif //POINTCLOUD_VIEWER_NPY_IMPORTER_H
