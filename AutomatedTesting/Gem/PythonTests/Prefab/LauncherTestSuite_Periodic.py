"""
Copyright (c) Contributors to the Open 3D Engine Project.
For complete copyright and license terms please see the LICENSE at the root of this distribution.

SPDX-License-Identifier: Apache-2.0 OR MIT
"""

import pytest

from .tests.launcher_utils import run_launcher_tests
import ly_remote_console.remote_console_commands as rc


@pytest.fixture
def remote_console_instance(request):
    console = rc.RemoteConsole()

    def teardown():
        if console.connected:
            console.stop()

    request.addfinalizer(teardown)
    return console


@pytest.mark.SUITE_periodic
@pytest.mark.parametrize("project", ["AutomatedTesting"])
class TestLauncherAutomation(object):

    def test_Launcher_MultipleLevelLoads(self, launcher, remote_console_instance):
        levels = ["levels/Prefab/Base/Base.spawnable",
                  "levels/Prefab/QuitOnSuccessfulSpawn/QuitOnSuccessfulSpawn.spawnable"]
        run_launcher_tests(launcher, levels, remote_console_instance, null_renderer=True)

    @pytest.mark.parametrize(launcher_platform, ['windows_dedicated'])
    def test_DedicatedLauncher_Launches(self, launcher, remote_console_instance, launcher_platform):
        levels = ["levels/Prefab/Base/Base.spawnable"]
        run_launcher_tests(launcher, levels, remote_console_instance)

