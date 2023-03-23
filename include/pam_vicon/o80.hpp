// SPDX-License-Identifier: BSD-3-Clause

/**
 * @file
 * @brief PAM-Vicon specific settings for the o80 driver.
 * @copyright 2023 Max Planck Gesellschaft.  All rights reserved.
 */
#pragma once

#include <array>
#include <cstddef>
#include <map>
#include <string>

#include <vicon_transformer/errors.hpp>
#include <vicon_transformer/o80_driver.hpp>
#include <vicon_transformer/o80_standalone.hpp>

namespace pam_vicon
{
//! Number of subjects in the PAM Vicon setup.
constexpr std::size_t NUM_SUBJECTS = 11;

/**
 * @brief Enumeration of Vicon subjects.
 *
 * The values of the enum entries are used as indices for arrays with subject
 * data.
 */
enum Subjects
{
    PING_BASE = 0,
    BALL_LAUNCHER_FRONT,
    BALL_LAUNCHER_HEAD,
    TABLE_CORNER_1,
    TABLE_CORNER_2,
    TABLE_CORNER_3,
    TABLE_CORNER_4,
    LED_STICK,
    ROBOT1_BASE,
    ROBOT1_UPPER_ARM,
    ROBOT1_RACKET
};

//! Maps subject name to @ref Subjects entry.
const std::map<std::string, size_t> _subject_name_to_index = {
    {"Pamy_ceiling", Subjects::PING_BASE},
    {"Ballmaschine Frontmarker", Subjects::BALL_LAUNCHER_FRONT},
    {"Abschusskopf Marker v2", Subjects::BALL_LAUNCHER_HEAD},
    {"Eckteil 1", Subjects::TABLE_CORNER_1},
    {"Eckteil 2", Subjects::TABLE_CORNER_2},
    {"Eckteil 3", Subjects::TABLE_CORNER_3},
    {"Eckteil 4", Subjects::TABLE_CORNER_4},
    {"rll_led_stick", Subjects::LED_STICK},
    {"pamy1_base", Subjects::ROBOT1_BASE},
    {"pamy1_upper_arm", Subjects::ROBOT1_UPPER_ARM},
    {"pamy1_racket", Subjects::ROBOT1_RACKET},
};

/**
 * @brief Maps subject name to index.
 *
 * @param name Name of the subject.
 *
 * @return Index at which this subject is expected in subject arrays.
 */
inline size_t map_subject_name_to_index(const std::string &name)
{
    try
    {
        return _subject_name_to_index.at(name);
    }
    catch (const std::out_of_range &)
    {
        // throw a more explicit exception
        throw vicon_transformer::UnknownSubjectError(name);
    }
}

/**
 * @brief Get list of subject names.
 *
 * The names are ordered according to @ref Subjects, i.e.
 *
 * .. code-block:: C++
 *
 *    auto names = get_subject_names();
 *    names[Subjects::BALL_LAUNCHER]
 *
 * gives the name of the ball launcher marker.
 *
 * @return Array that maps subject index to its name.
 */
inline std::array<std::string, NUM_SUBJECTS> get_subject_names()
{
    std::array<std::string, NUM_SUBJECTS> names;

    for (auto &[name, index] : _subject_name_to_index)
    {
        names[index] = name;
    }

    return names;
}

//! FixedSizeViconFrame for the PAM Vicon setup.
typedef vicon_transformer::FixedSizeViconFrame<NUM_SUBJECTS>
    FixedSizeViconFrame;
//! o80Driver for the PAM Vicon setup
typedef vicon_transformer::o80Driver<NUM_SUBJECTS, map_subject_name_to_index>
    o80Driver;
//! o80Standalone for the PAM Vicon setup
typedef vicon_transformer::o80Standalone<o80Driver> o80Standalone;

}  // namespace pam_vicon
