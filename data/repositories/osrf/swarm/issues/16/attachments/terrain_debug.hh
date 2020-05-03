/// \file terrain_debug.hh
/// \brief the simplest possible search algorithm: pick random points to search

#ifndef __TERRAIN_DEBUG_PLUGIN_HH__
#define __TERRAIN_DEBUG_PLUGIN_HH__

#include "swarm/RobotPlugin.hh"

namespace swarm
{
  class Terrain_Debug_Plugin : public swarm::RobotPlugin
  {

    public:

        /*! \brief constructor */
        Terrain_Debug_Plugin();

        /*! \brief destructor */
        virtual ~Terrain_Debug_Plugin() = default;

        /*! \brief calls \ref Plugin_Base::Load and \ref initComms */
        virtual void Load(sdf::ElementPtr _sdf);

        /*! \brief calls \ref Plugin_Base::Load, \ref updateGoal, and \ref calcControl() */
        virtual void Update(const gazebo::common::UpdateInfo &_info);

  };

}

#endif // __TERRAIN_DEBUG_PLUGIN_HH__
