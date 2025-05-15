[![pipeline status](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/badges/master/pipeline.svg)](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/commits/master)


SurveyLib
=========

The SurveyLib is a computation library used by almost all survey application at CERN.

#### Table of Content ####

[Purpose](#purpose)

[Download](#download)

[Documentation](#documentation)
- [User guide](#user-guide)
- [Doxygen](#doxygen)
- [Other](#other)

[Build instructions](#build-instructions)
- [Requirements](#requirements)
- [Generate project](#generate-project)
- [Build](#build)
- [Tests](#tests)

[Contribute](#contribute)
- [Jira](#jira)
- [Pull requests](#pull-requests)
- [Automatic tests](#automatic-tests)

Purpose
-------

The SurveyLib holds the computation part of all survey software. It defines the points, matrices and all sorts of operations to perform on it (and way more!). It is generally included in other projects as a Git submodule and linked as a static library. Though, it also provides a subset of its features in a dynamic library, usable with both Linux and Windows.

Download
--------

You can download the last version of the dynamic library of the surveyLib here:
- Linux (64 bits): [libSpatialObjDLL.so](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/jobs/artifacts/master/raw/libSpatialObjDLL.so?job=linux_release)
- Windows (64 bits): [SpatialObjDLL.dll](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/jobs/artifacts/master/raw/SpatialObjDLL.dll?job=windows64_release)
- Windows (32 bits): [SpatialObjDLL.dll](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/jobs/artifacts/master/raw/SpatialObjDLL.dll?job=windows32_release)

You can download the last version of the dynamic library of CSGeo here:
- Linux (64 bits): [libCSGeoDLL.so](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/jobs/artifacts/master/raw/libCSGeoDLL.so?job=linux_release)
- Windows (64 bits): [CSGeoDLL.dll](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/jobs/artifacts/master/raw/CSGeoDLL.dll?job=windows64_release)
- Windows (32 bits): [CSGeoDLL.dll](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/jobs/artifacts/master/raw/CSGeoDLL.dll?job=windows32_release)


Documentation
-------------

### User guide ###

The SurveyLib mainly targets the developers as it is meant to be integrated and used by other software. Though you can find a draft of a user documentation here: <https://confluence.cern.ch/display/SUS/SurveyLib+User+Guide>.

### Doxygen ###

The Doxygen documentation is meant for developers only. Follow the [Build instructions](#build-instructions) to set up your projects. Then you can build the `doc` target to create the Doxygen documentation. You will need [Doxygen](https://www.stack.nl/~dimitri/doxygen/download.html#srcbin) and [GraphViz](http://www.graphviz.org/download/#executable-packages) installed and configured.

Once built, you can open the file `build/html/index.html` as an entry point to the documentation.

### Other ###

You can find further documentation in the folder [Documentation](./Documentation).

Build instructions
------------------

Before starting, you can have a look at the documentation about [Getting started with C++](https://confluence.cern.ch/pages/viewpage.action?pageId=22153013) for the CERN survey applications.

### Requirements ###

The SurveyLib can be built on Windows or Linux. To do so, you need at least:
- a C++14 compiler
- CMake 3.6+
- Eigen
- TUT

For Windows, you can follow the steps in the aforementioned [Getting started with C++](https://confluence.cern.ch/pages/viewpage.action?pageId=22153013) documentation.

For Linux, you have an example of the needed steps in the dockerfiles of the [sus_ci_cppworker](https://gitlab.cern.ch/apc/common/docker-image-susoft-cpp) project (the Docker image used to automatically run the tests on GitLab-CI).
Note that the `devtoolset` trick is only necessary on the CC7 (Cern CentOS 7) as it doesn't provide a C++14 compiler by default.

### Generate project ###

We use CMake to generate projects, thus it is possible to generate projects for MSVC, Eclipse, or simple Unix makefiles. See the [CMake Generators documentation](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) page.

First of all, ensure that you have all the submodules initialized with:

```bash 
$ git submodule update --init
```

To generate the project, you need to create a subdirectory named `build/`, and then run CMake inside:

```bash
$ mkdir build && cd build/
$ cmake -G "Visual Studio 16 2019" -A x64 ../source # Use another generator here if you wish
```

In order to use a custom ext_libs.txt file defining the dependencies, please use:
```bash
$ cmake -G "Visual Studio 16 2019" -A x64 -DEXT_LIBS_TXT_PATH="C:/susoft/SUSoftCMakeCommon/ext_libs.txt" ../source # Use another file defining the dependencies
```

### Build ###

Once generated, you can open your project in the `build/` subfolder. If you use MSVC, you can open the file `build/SurveyLib.sln`.

you can see that CMake has generated several targets, among others:
- `ALL_BUILD` builds all except the doxygen documentation
- `RUN_TESTS` runs all tests provided they were build before
- `ZERO_CHECK` reruns CMake and automatically updates your project
- `CSGeoDLL` builds CSGeoDLL
- `Logs` builds Logs static library
- `LSAlgorithms` builds LSAlgorithms static library
- `Plugins` builds Plugins static library used by SurveyPad and its plugins
- `ProjectFramework` builds ProjectFramework static library used by CSGeoDLL
- `SpatialObjDLL` builds the SurveyLib dynamic library
- `SpatialObjects` builds SpatialObjects static library used by CSGeoDLL
- `Tools` builds Tools static library
- `doc` builds the Doxygen documentation
- `UnitTests` builds the tests, the only runnable project (by default the startup project in MSVC)

### Tests ###

To build the tests, build the target `UnitTests` and run it. We Use TUT to generate unit tests. Note that the tests are automatically performed on Gitlab-CI for each contribution. You can see the results in the [CI page](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/pipelines).

Contribute
----------

SurveyLib is a private CERN repository, thus it doesn't accept contributions from outside CERN.

To report an issue (bug, or feature request), follow the [Jira](#jira) subsection. For development, please read on.

### Jira ###

Any request, bug or development should have a Jira issue. You can create an issue on the [dedicated Jira board](https://its.cern.ch/jira/browse/SUS). This is mandatory for both the users and the developers.

### Pull requests ###

The most up-to-date stable branch is `master`. As a stable branch, you **must not** commit directly in it. You need to create a specific branch for your on-going development and commit there. As we use CMake, if you add a file, don't forget to add it in one of the `CMakeFile.txt`!

Once you have finished your work, you should create a Pull Request (PR, or Merge Request) from your branch to `master`. The description of your PR should include a link to the corresponding task in Jira.

Once your PR has been reviewed by another developer and accepted, it can be merged into master. Note that, for the sake of a nice Git history, your branch needs to be up to date with `master`. If it is not the case, you will have to rebase, either automatically from GitLab if there are no conflicts, or manually otherwise.

### Automatic tests ###

Automatic tests are performed each time you push a commit. These tests include compilation of `ALL_BUILD` target, and running the `UnitTests` target, all on Linux 64 bits, Windows 32 and 64 bits. If the tests don't pass, your PR will not be merged.

Once the PR has been accepted and merged into `master`, GitLab-CI will automatically build the dynamic library.

## Licensing

SurveyLib is licensed under the [Mozilla Public License 2.0](LICENSE).

This project complies with the [REUSE specification](https://reuse.software/), which standardizes license documentation and attribution.

### Third-Party Dependencies

| Library           | License                              | Source                                       |
|-------------------|---------------------------------------|----------------------------------------------|
| Eigen             | MPL-2.0                               | https://gitlab.com/libeigen/eigen            |
| TUT               | Boost Software License 1.0            | https://github.com/martinmoene/tut           |
| RapidJSON         | MIT                                   | https://github.com/Tencent/rapidjson         |
| Reframe           | Custom (redistributable, free only)   | https://www.swisstopo.admin.ch               |
| `counted_ptr.h` | Custom Permissive License (1999) | http://snowball.digitalspace.net/cpp/        |

All third-party license texts are stored in the [`LICENSES/`](LICENSES/) directory.

