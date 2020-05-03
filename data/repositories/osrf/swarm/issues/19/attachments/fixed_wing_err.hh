#ifndef __FIXED_WING_ERR_PLUGIN_HH__
#define __FIXED_WING_ERR_PLUGIN_HH__

// we are inheriting plugin_base because it contains the estimator.
#include "plugin_base.hh"

namespace gt_swarm {

class Fixed_Wing_Err_Plugin : public swarm_utils::Plugin_Base {

  public:

      Fixed_Wing_Err_Plugin();
      virtual ~Fixed_Wing_Err_Plugin() = default;
      virtual void Load(sdf::ElementPtr _sdf);
      virtual void Update(const gazebo::common::UpdateInfo &_info);

};

}

#endif // __FIXED_WING_ERR_PLUGIN_HH__
