#include "terrain_debug.hh"

using namespace swarm;
using namespace std;

GZ_REGISTER_MODEL_PLUGIN(Terrain_Debug_Plugin)

//////////////////////////////////////////////////
Terrain_Debug_Plugin::Terrain_Debug_Plugin()
  : RobotPlugin()
{
}

void Terrain_Debug_Plugin::Load(sdf::ElementPtr _sdf) {
    // divide the world into 1000x1000 chucks
    double min_lat, max_lat, min_lon, max_lon;

    // get lat/lon bounds
    this->SearchArea(min_lat, max_lat, min_lon, max_lon);
    double step_lon = (max_lon - min_lon) / 500.0;
    double step_lat = (max_lat - min_lat) / 500.0;

    double elevation;
    swarm::RobotPlugin::TerrainType terrain_type;

    ofstream elevation_file("elevation.csv");
    ofstream terrain_file("terrain.csv");

    elevation_file << ", ";
    terrain_file << ", ";

    for (double lon = min_lon; lon < max_lon; lon += step_lon) {
        elevation_file << to_string(lon) << ((lon + step_lon < max_lon) ? ", " : "\n");
        terrain_file   << to_string(lon) << ((lon + step_lon < max_lon) ? ", " : "\n");
    }

    for (double lat = min_lat; lat < max_lat; lat += step_lat) {
        elevation_file << to_string(lat) << ", ";
        terrain_file << to_string(lat) << ", ";

        for (double lon = min_lon; lon < max_lon; lon += step_lon) {

            MapQuery(lat, lon, elevation, terrain_type);
            elevation_file << elevation << ((lon + step_lon < max_lon) ? ", " : "\n");
            terrain_file   << terrain_type << ((lon + step_lon < max_lon) ? ", " : "\n");

        }
    }
    std::cout << "done!\n";

    elevation_file.close();
    terrain_file.close();
}

void Terrain_Debug_Plugin::Update(const gazebo::common::UpdateInfo &_info) {
}
