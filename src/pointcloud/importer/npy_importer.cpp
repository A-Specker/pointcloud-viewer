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
    float64_t eps = 0.01;
    // cases: val is 2: predicted too much, 3 it forgot smthing, else default blue
    if (val>2-eps && val<2+eps){
        out[0] = 0;
        out[1] = 255;
        out[2] = 0;
    }
    else if(val>3-eps && val<3+eps) {
        out[0] = 255;
        out[1] = 0;
        out[2] = 0;
    }
    else {
        out[0] = 0;
        out[1] = 0;
        out[2] = 255;
    }
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
    std::vector<float64_t > data; // TODO: hier waere was dynamisches schoener, oder wenigstens nicht 64...
    npy::LoadArrayFromNumpy(input_file, shape, data);

    int dim = voxel_dim(data.size());

    pointcloud.aabb = aabb_t::invalid();
    size_t num_points = data.size();
    this->pointcloud.resize(num_points);

    Buffer voxel_data;
    voxel_data.resize(sizeof(float64_t)*data.size());

    float thresh = VOXEL_THRESH;

    float f_inf = std::numeric_limits<float64_t>::infinity();
    glm::vec3 inf(f_inf, f_inf, f_inf);


    uint8_t* coordinates = pointcloud.coordinate_color.data();
    for(size_t i=0; i<num_points; ++i)
    {
        PointCloud::vertex_t vertex;

        std::vector<float64_t > coords = NpyImporter::map_idx_to_coords(i, dim);
        std::vector<int> cols = NpyImporter::val_to_heatmap(data[i]);

        vertex.value = data[i];
        if(vertex.value < thresh){
            vertex.coordinate.x = f_inf;
            vertex.coordinate.y = f_inf;
            vertex.coordinate.z = f_inf;
        }
        else {
            vertex.coordinate.x = coords[0];
            vertex.coordinate.y = coords[1];
            vertex.coordinate.z = coords[2];
        }
        vertex.color.r = cols[0];
        vertex.color.g = cols[1];
        vertex.color.b = cols[2];

        if(i==0){
//            std::cout << "vertex_t: " <<sizeof(PointCloud::vertex_t) << std::endl;
//            std::cout << "float64_t: " <<sizeof(float64_t) << std::endl;
//            std::cout << " glm::vec3: " <<sizeof( glm::vec3) << std::endl;
//            std::cout << "glm::u8vec3: " <<sizeof(glm::u8vec3) << std::endl;
//            std::cout << "padding<uint8_t>: " <<sizeof(padding<uint8_t>) << std::endl;

//            std::vector<int> ret(3);
//
//            std::cout << "ret: " <<sizeof(ret) << std::endl;
//            std::cout << "int: " <<sizeof(int) << std::endl;

        }

        write_value_to_buffer<PointCloud::vertex_t>(coordinates, vertex);
        coordinates += PointCloud::stride;

    }
    return true;
}



