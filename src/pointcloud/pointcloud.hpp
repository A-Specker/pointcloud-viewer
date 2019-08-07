#ifndef POINTCLOUDVIEWER_POINTCLOUD_HPP_
#define POINTCLOUDVIEWER_POINTCLOUD_HPP_

#include <pointcloud/buffer.hpp>
#include <pointcloud/kdtree_index.hpp>
#include <geometry/aabb.hpp>

#include <QVector>
#include <QString>
#include <QVariant>
#include <QSet>

/*
Stores the whole point cloud consisting out of the
- coordinate_color -- coordinates and colors
- user_data -- all property data
*/
class PointCloud final
{
public:
  enum class column_t
  {
    COORDINATES,
    COLOR,
    USER_DATA,
  };
  typedef column_t COLUMN;

  // the value field is new!
  // new the size is 24 byte (8+12+3+1)
  struct vertex_t
  {
    float64_t value;
    glm::vec3 coordinate;
    glm::u8vec3 color;
    padding<uint8_t> _padding = padding<uint8_t>();
  };

  struct UserData
  {
    QVector<QString> names;
    QVector<QVariant> values;
  };

  struct Shader
  {
    QSet<QString> used_properties;
    QString coordinate_expression;
    QString color_expression;
    QString node_data;

    QStringList ordered_properties() const;

    void export_to_file(QString filename) const;
    static Shader import_from_file(QString filename);
  };

  Buffer coordinate_color, user_data;
  KDTreeIndex kdtree_index;
  Shader shader;
  aabb_t aabb;
  size_t num_points;
  bool is_valid;

  size_t user_data_stride;
  QVector<QString> user_data_names;
  QVector<size_t> user_data_offset;
  QVector<data_type::base_type_t> user_data_types;

  PointCloud();
  PointCloud(PointCloud&& other);
  PointCloud& operator=(PointCloud&& other);

  constexpr static const size_t stride = sizeof(vertex_t);
  static_assert(stride == sizeof(vertex_t), "size mismatch");

  UserData all_values_of_point(size_t point_index) const;
  vertex_t vertex(size_t point_index) const;

  const vertex_t* begin() const;
  const vertex_t* end() const;

  void clear();
  void resize(size_t num_points);

  void set_user_data_format(size_t user_data_stride, QVector<QString> user_data_names, QVector<size_t> user_data_offset, QVector<data_type::base_type_t> user_data_types);

  void build_kd_tree(std::function<bool(size_t, size_t)> feedback);
  bool can_build_kdtree() const;
  bool has_build_kdtree() const;



  float64_t get_value(int idx);
  glm::vec3 get_coords(int idx);
  glm::u8vec3 get_color(int idx);

  void set_value(int idx, float64_t val);
  void set_coords(int idx, std::vector<float64_t> coords);
  void set_color(int idx, std::vector<int> col);

  void set_coords(int idx, glm::vec3 coords);
  void set_color(int idx, glm::u8vec3 col);

};

QDebug operator<<(QDebug debug, const PointCloud::UserData& userData);

Q_DECLARE_METATYPE(PointCloud::Shader);

#endif // POINTCLOUDVIEWER_POINTCLOUD_HPP_
