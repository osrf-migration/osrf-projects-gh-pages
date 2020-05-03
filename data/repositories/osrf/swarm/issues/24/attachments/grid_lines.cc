#include "grid_lines.hh"

using namespace std;
using namespace gazebo::rendering;
using namespace ignition::math;

GZ_REGISTER_VISUAL_PLUGIN(Grid_Lines_Plugin)

void Grid_Lines_Plugin::Load( VisualPtr _parent, sdf::ElementPtr _sdf ) {
    this->visual_ = _parent;
    this->update_connection_ = event::Events::ConnectRender( boost::bind(&Grid_Lines_Plugin::UpdateChild, this));
    this->done = false;
}

void Grid_Lines_Plugin::UpdateChild() {

    // only execute this once
    if (this->done) {
        return;
    }

    // read in the SearchArea output from some other plugin
    std::ifstream file("elevation2.txt");
    if (!file.is_open()) {
        return;
    }

    DynamicLines *line;
    string str;
    line = this->visual_->CreateDynamicLine(RENDERING_LINE_STRIP);
    double prev_x = numeric_limits<double>::infinity();
    double prev_y = numeric_limits<double>::infinity();

    while (getline(file, str)) {

        // split it into 3 doubles
        std::vector<std::string> str_vec;
        boost::trim_if(str, boost::is_any_of("\t "));
        boost::split(str_vec, str, boost::is_any_of("\t "), boost::token_compress_on);

        if (str_vec.size() != 3) {
            gzerr << "elevation.txt needs 3 entries on each line [X, Y, Z]" << std::endl;
            return;
        }

        double x = stod(str_vec[0]);
        double y = stod(str_vec[1]);
        double z = stod(str_vec[2]);

        if (fabs(x - prev_x) > 1e-5 && fabs(y - prev_y) > 1e-5) {
            line->setMaterial("Gazebo/Purple");
            line->setVisibilityFlags(GZ_VISIBILITY_GUI);
            line = this->visual_->CreateDynamicLine(RENDERING_LINE_STRIP);
        }

        prev_x = x;
        prev_y = y;
        line->AddPoint(math::Vector3(x, y, z));

    }

    line->setMaterial("Gazebo/Purple");
    line->setVisibilityFlags(GZ_VISIBILITY_GUI);
    visual_->SetVisible(true);

    this->done = true;
}
