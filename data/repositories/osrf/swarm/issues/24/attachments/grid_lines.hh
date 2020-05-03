#ifndef __GRID_LINES_HH__
#define __GRID_LINES_HH__

#include "gazebo/physics/physics.hh"
#include "gazebo/transport/TransportTypes.hh"
#include "gazebo/msgs/MessageTypes.hh"

#include "gazebo/common/Time.hh"
#include "gazebo/common/Plugin.hh"
#include "gazebo/common/Events.hh"

#include "gazebo/rendering/DynamicLines.hh"
#include "gazebo/rendering/RenderTypes.hh"
#include "gazebo/rendering/Visual.hh"
#include "gazebo/rendering/Scene.hh"

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "swarm/Common.hh"

namespace gazebo
{
  namespace rendering
  {
    class Grid_Lines_Plugin : public VisualPlugin
    {
      public:
        /// \brief Load the visual force plugin tags
        /// \param node XML config node
        void Load( VisualPtr _parent, sdf::ElementPtr _sdf );


      private:
        
        VisualPtr visual_;                          /*! \brief for rendering lines */
        swarm::Common common;                       /*! \brief for terrain/searchArea lookups */
        event::ConnectionPtr update_connection_;    /*! \brief for callbacks */
        void UpdateChild();                         /*! \brief callback function */
        bool done;                                  /*! \brief whether or not the lines have been rendered */
        const double bin_size = 200;                /*! \brief grid cell size */
        const double line_step_size = 1;            /*! \brief how far to space sampling points in the lines */

    };
  }
}

#endif // __GRID_LINES_HH__
