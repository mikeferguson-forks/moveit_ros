/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2012, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/* Author: Ioan Sucan */

#ifndef MOVEIT_KINEMATICS_PLUGIN_LOADER_
#define MOVEIT_KINEMATICS_PLUGIN_LOADER_

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <planning_models/kinematic_model.h>
#include <kinematics_base/kinematics_base.h>

namespace kinematics_plugin_loader
{

/// function type that allocates an Kinematics solver for a particular group
typedef boost::function<boost::shared_ptr<kinematics::KinematicsBase>(const planning_models::KinematicModel::JointModelGroup*)> KinematicsLoaderFn;

class KinematicsPluginLoader
{
public:

  /// Take as optional argument the name of the parameter under which the robot description can be found
  KinematicsPluginLoader(const std::string &robot_description = "robot_description") : robot_description_(robot_description)
  {
  }
  
  KinematicsLoaderFn getLoaderFunction(void);

  const std::vector<std::string>& getKnownGroups(void) const
  {
    return groups_;
  }

  bool isGroupKnown(const std::string& name) const;
  void status(void) const;
  
private:

  std::string robot_description_;  
  class KinematicsLoaderImpl;
  boost::shared_ptr<KinematicsLoaderImpl> loader_;
  std::vector<std::string> groups_;
};
}

#endif