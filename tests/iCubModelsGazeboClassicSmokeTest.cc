// SPDX-FileCopyrightText: Fondazione Istituto Italiano di Tecnologia (IIT)
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <gazebo/test/ServerFixture.hh>
#include <gazebo/test/helper_physics_generator.hh>

#include <yarp/dev/Drivers.h>
#include <yarp/dev/IControlMode.h>
#include <yarp/dev/IEncoders.h>
#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/IVelocityControl.h>
#include <yarp/dev/PolyDriver.h>

class iCubModelsGazeboClassicSmokeTest : public gazebo::ServerFixture,
                                         public testing::WithParamInterface<const char*>
{
  struct ModelTestHelperOptions
  {
  };

  public: gazebo::event::ConnectionPtr updateConnection;

  public: void ModelTest(const std::string &_physicsEngine);
  public: void ModelTestHelper(const std::string &_physicsEngine,
                               const ModelTestHelperOptions& options);
};

void iCubModelsGazeboClassicSmokeTest::ModelTestHelper(const std::string &_physicsEngine,
                                                       const ModelTestHelperOptions& options)
{
  // Load an empty world
  bool worldPaused = false;
  Load("worlds/empty.world", worldPaused, _physicsEngine);

  gazebo::physics::WorldPtr world = gazebo::physics::get_world("default");
  ASSERT_TRUE(world != NULL);

  // Verify physics engine type
  gazebo::physics::PhysicsEnginePtr physics = world->Physics();
  ASSERT_TRUE(physics != NULL);
  EXPECT_EQ(physics->GetType(), _physicsEngine);

  gzdbg << "iCubModelsGazeboClassicSmokeTest: testing with physics engine " << _physicsEngine << std::endl;

  // Load models under test
  std::vector<std::string> modelsToTest;
  modelsToTest.push_back("iCubGazeboV2_5_fixed");
  modelsToTest.push_back("iCubGazeboV3_fixed");

  for(auto modelUnderTest: modelsToTest)
  {
    gzdbg << "iCubModelsGazeboClassicSmokeTest: Spawning " << modelUnderTest << std::endl;
    SpawnModel("model://" + modelUnderTest);
    gazebo::common::Time::MSleep(2000);
    gzdbg << "iCubModelsGazeboClassicSmokeTest: Spawned " << modelUnderTest << std::endl;


    gzdbg << "iCubModelsGazeboClassicSmokeTest: Unloading " << modelUnderTest << std::endl;
    RemoveModel(modelUnderTest);
  }

  // Unload the simulation
  Unload();
}

/////////////////////////////////////////////////////////////////////
void iCubModelsGazeboClassicSmokeTest::ModelTest(const std::string &_physicsEngine)
{
  // Make sure that the YARP network does not require yarpserver running
  //yarp::os::NetworkBase::setLocalMode(true);

  // Defined by CMake
  std::string modelDirOne = PROJECT_BINARY_DIR;
  std::string modelDirTwo = std::string(PROJECT_BINARY_DIR) + std::string("/iCub/robots");
  gazebo::common::SystemPaths::Instance()->AddModelPaths(modelDirOne);
  gazebo::common::SystemPaths::Instance()->AddModelPaths(modelDirTwo);

  ModelTestHelperOptions options;
  this->ModelTestHelper(_physicsEngine, options);
}

TEST_P(iCubModelsGazeboClassicSmokeTest, ModelTest)
{
  ModelTest(GetParam());
}

INSTANTIATE_TEST_CASE_P(PhysicsEngines, iCubModelsGazeboClassicSmokeTest, PHYSICS_ENGINE_VALUES);

/////////////////////////////////////////////////
/// Main
int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
