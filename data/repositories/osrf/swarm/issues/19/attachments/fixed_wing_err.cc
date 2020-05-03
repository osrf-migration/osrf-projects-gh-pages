#include "fixed_wing_err.hh"

using namespace std;
using namespace gt_swarm;

GZ_REGISTER_MODEL_PLUGIN(Fixed_Wing_Err_Plugin)

//////////////////////////////////////////////////
Fixed_Wing_Err_Plugin::Fixed_Wing_Err_Plugin()
  : Plugin_Base()
{
}

void Fixed_Wing_Err_Plugin::Load(sdf::ElementPtr _sdf) {
    // get initial pose estimate
    this->load_helper(_sdf, false);
}

void Fixed_Wing_Err_Plugin::Update(const gazebo::common::UpdateInfo &_info) {
    // update pose estimate
    this->update_helper(_info, true, false);

    // calculate control
    const double vel_fwd = 10;
    double roll  = this->est.get_pose().Rot().Euler().X();
    double pitch = this->est.get_pose().Rot().Euler().Y();
    double yaw   = this->est.get_pose().Rot().Euler().Z();
    double v_roll, v_pitch;

    if (simTs < 30) {
        // takeoff (for some reason this sometimes has a yaw component)
        v_roll = -roll;
        v_pitch = (IGN_DTOR(-45) - pitch);
    } else if (simTs < 45) {
        // stabilize (the plane may pitch here)
        v_roll = -roll;
        v_pitch = -pitch;
    } else {
        // try to turn but end up turning random directions (the instability
        // may or may not take a while to emerge)
        cout << roll << ", " << pitch << ", " << yaw << endl;
        v_roll = (IGN_DTOR(20) - roll);
    }

    this->SetLinearVelocity(ignition::math::Vector3d(vel_fwd,0,0));
    this->SetAngularVelocity(ignition::math::Vector3d(v_roll, v_pitch, 0));

}
