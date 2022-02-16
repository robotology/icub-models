/**
 * @file icub_models.cpp
 * @authors Giulio Romualdi
 * @copyright 2022 Istituto Italiano di Tecnologia Released under the terms of the Creative Commons Attribution Share Alike 4.0 International
 */

#include <iCubModels/iCubModels.h>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace iCubModels
{
namespace
{

namespace py = ::pybind11;
PYBIND11_MODULE(bindings, m)
{
    m.doc() = "Python bindings for the icub-models.";

    m.def("get_models_path", &iCubModels::getModelsPath,
          "Get the folder where the models are installed.")
     .def("get_robot_names", &iCubModels::getRobotNames,
          "Return a set containing the names of the robots installed.")
     .def("get_model_file", &iCubModels::getModelFile, py::arg("model_name"),
          "Return the path of the model given its name. If the 'model_name' is not in the list "
          "of the installed robot an empty path is returned.");
}

} // namespace
} // namespace iCubModels
