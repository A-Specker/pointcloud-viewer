#include <pointcloud/importer/npy_importer.h>
#include <fstream>
#include <external/libnpy/npy.hpp>
#include <core_library/types.hpp>

#include <QDebug>

#include <fstream>

NpyImporter::NpyImporter(const std::string& input_file)
        : AbstractPointCloudImporter(input_file) {
}

std::vector<float64_t> NpyImporter::map_idx_to_coords(size_t idx, size_t dim) {
    std::vector<float64_t> out(3);
    out[0] = (idx % dim) * VOX_SCALE;
    out[1] = ((idx / dim) % dim) * VOX_SCALE;
    out[2] = (idx / (dim * dim)) * VOX_SCALE;
    return out;
}

std::vector<int> NpyImporter::val_to_heatmap(float64_t val){
    std::vector<int> out(3);
    out[0] = (val * 255);
    out[1] = (1.0f-val) * 255;
    out[2] = 0;
    return out;
}

int NpyImporter::voxel_dim(size_t total_size){
    double l = std::cbrt(total_size);
    if (!(round(l) == l)){
//        QMessageBox::warning(parent, "Voxel Dimesnion", QString("Cant split Voxel data in 3 even Dimensions"));
        throw QString("Cant split Voxel data in 3 even Dimensions");
    }
    return (int)l;
}

bool NpyImporter::import_implementation()
{
    std::vector<unsigned long> shape;
    std::vector<float64_t > data; // TODO: hier waere was dynamisches schoener
    npy::LoadArrayFromNumpy(input_file, shape, data);

    int dim = voxel_dim(data.size());

    pointcloud.aabb = aabb_t::invalid();
    size_t num_points = data.size();
    this->pointcloud.resize(num_points);

    Buffer voxel_data;
    std::cout << "1" << std::endl;
    voxel_data.resize(sizeof(float64_t)*data.size());
    std::cout << sizeof(float64_t) << std::endl;

    uint8_t* coordinates = pointcloud.coordinate_color.data();
    for(size_t i=0; i<num_points; ++i)
    {
        PointCloud::vertex_t vertex;

        std::vector<float64_t > coords = NpyImporter::map_idx_to_coords(i, dim);
        std::vector<int> cols = NpyImporter::val_to_heatmap(data[i]);

        vertex.coordinate.x = coords[0];
        vertex.coordinate.y = coords[1];
        vertex.coordinate.z = coords[2];
        vertex.color.r = cols[0];
        vertex.color.g = cols[1];
        vertex.color.b = cols[2];
        vertex.value = data[i];

//        std::cout << sizeof(data[i]) << std::endl;

        write_value_to_buffer<PointCloud::vertex_t>(coordinates, vertex);
        coordinates += PointCloud::stride;
//        std::cout <<  coords[0] << " " <<  coords[1] << " " <<  coords[2] << std::endl;

    }
    return true;
}


