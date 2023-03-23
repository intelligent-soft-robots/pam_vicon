// SPDX-License-Identifier: BSD-3-Clause

/**
 * @file Python bindings of the relevant C++ classes/functions.
 * @copyright 2022, Max Planck Gesellschaft.  All rights reserved.
 */
#include <sstream>

#include <pybind11/eigen.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <o80/pybind11_helper.hpp>
#include <serialization_utils/cereal_json.hpp>

#include <pam_vicon/o80.hpp>

PYBIND11_MODULE(o80, m)
{
    namespace py = pybind11;

    py::module::import("vicon_transformer");

    py::class_<pam_vicon::FixedSizeViconFrame>(m, "FixedSizeViconFrame")
        .def(py::init<>())
        .def_readwrite("frame_number",
                       &pam_vicon::FixedSizeViconFrame::frame_number)
        .def_readwrite("frame_rate",
                       &pam_vicon::FixedSizeViconFrame::frame_rate)
        .def_readwrite("latency", &pam_vicon::FixedSizeViconFrame::latency)
        .def_readwrite("time_stamp",
                       &pam_vicon::FixedSizeViconFrame::time_stamp)
        .def_readwrite("subjects", &pam_vicon::FixedSizeViconFrame::subjects)
        .def(
            "__str__",
            [](const pam_vicon::FixedSizeViconFrame& vf)
            {
                std::stringstream stream;
                stream << vf;
                return stream.str();
            },
            py::call_guard<py::gil_scoped_release>());
    m.def("to_json",
          &serialization_utils::to_json<pam_vicon::FixedSizeViconFrame>);
    m.def("from_json",
          &serialization_utils::from_json<pam_vicon::FixedSizeViconFrame>);

    py::enum_<pam_vicon::Subjects>(m, "Subjects")
        .value("PING_BASE", pam_vicon::Subjects::PING_BASE)
        .value("BALL_LAUNCHER_FRONT", pam_vicon::Subjects::BALL_LAUNCHER_FRONT)
        .value("BALL_LAUNCHER_HEAD", pam_vicon::Subjects::BALL_LAUNCHER_HEAD)
        .value("TABLE_CORNER_1", pam_vicon::Subjects::TABLE_CORNER_1)
        .value("TABLE_CORNER_2", pam_vicon::Subjects::TABLE_CORNER_2)
        .value("TABLE_CORNER_3", pam_vicon::Subjects::TABLE_CORNER_3)
        .value("TABLE_CORNER_4", pam_vicon::Subjects::TABLE_CORNER_4)
        .value("LED_STICK", pam_vicon::Subjects::LED_STICK)
        .value("ROBOT1_BASE", pam_vicon::Subjects::ROBOT1_BASE)
        .value("ROBOT1_UPPER_ARM", pam_vicon::Subjects::ROBOT1_UPPER_ARM)
        .value("ROBOT1_RACKET", pam_vicon::Subjects::ROBOT1_RACKET);

    m.def("map_subject_name_to_index", &pam_vicon::map_subject_name_to_index);
    m.def("get_subject_names", &pam_vicon::get_subject_names);

    o80::create_python_bindings<pam_vicon::o80Standalone,
                                o80::NO_EXTENDED_STATE>(m);
    o80::create_standalone_python_bindings<
        pam_vicon::o80Driver,
        pam_vicon::o80Standalone,
        // argument for the driver
        std::shared_ptr<vicon_transformer::Receiver>,
        // argument for the driver (origin subject name)
        const std::string&>(m);
}
