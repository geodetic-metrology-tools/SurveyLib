[![pipeline status](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/badges/master/pipeline.svg)](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/commits/master)

# SurveyLib

**SurveyLib** is the core computation library used by nearly all survey and alignment software at **CERN**.  
It provides geometric and adjustment algorithms for high-precision geodetic and metrological computations.

[[_TOC_]]

---

## Purpose

SurveyLib defines the **mathematical and geometric foundations** of SU software, including **LGC2**, **SurveyPad**, and **CSGeo**.  
It contains point and matrix structures, least-squares adjustment algorithms, coordinate transformations, and statistical tools.

SurveyLib is typically linked as a **static or dynamic library** in other projects but can also be built standalone for development or testing.

**Legacy Notice:**
SurveyLib integrates code developed over more than 40 years of survey and alignment computation.
Some functions and methods preserve older programming styles or mathematical formalisms for backward compatibility.
Contributors are encouraged to propose modern replacements or simplifications where possible — while maintaining compatibility with dependent projects.

---

## Download

You can download the last version of the dynamic library of surveyLib or CSGEO by checking the [Releases](https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib/-/releases) in gitlab (CERN internal)

---

## Documentation

### Developer Documentation

SurveyLib is intended for **developers** integrating it into other software.  
Documentation and usage notes are available here:

- **[CERN Confluence Page](https://confluence.cern.ch/display/SUS/SurveyLib+User+Guide)** (internal)  

### Doxygen API Reference

To generate the Doxygen documentation locally:

```bash
cmake --build . --target doc
```

You need:
- [Doxygen](https://www.doxygen.nl/download.html)
- [GraphViz](https://graphviz.org/download/)

Then open:
```
build/html/index.html
```

> The Doxygen coverage is partial. Expanding and improving documentation is welcome as a contribution

### Other

You can find further documentation in the folder [Documentation](./Documentation).

## Build Instructions

SurveyLib builds on **Windows** and **Linux** with **CMake**.

CERN internal developers can refer to the detailed Confluence guide for the full setup and environment configuration:  
**[Getting Started with C++ for Survey Applications (CERN internal)](https://confluence.cern.ch/pages/viewpage.action?pageId=22153013)**

External contributors can follow the summarized instructions below.

### Prerequisites

The following tools and dependencies are required:

| Component | Version / Example | Purpose |
|------------|------------------|----------|
| **C++ Compiler** | C++14-compliant (MSVC v142, GCC ≥ 7.0, Clang ≥ 5.0) | Core compilation |
| **CMake** | [≥ 3.10 (recommended 3.20+)](https://cmake.org/download/) | Project configuration |
| **NSIS** | [3.05](https://nsis.sourceforge.io/Main_Page) | Windows installer generation |
| **Eigen** | [3.4.0](https://eigen.tuxfamily.org/) | Matrix and numerical computations |
| **TUT** | [2016-12-19](https://mrzechonek.github.io/tut-framework/) | Unit testing framework |
| **Git** | [Latest stable](https://gitforwindows.org/) | Source control and submodules |
| **Reframe** | [2016](https://www.swisstopo.admin.ch/en/geodetic-software-resources-dll-jar) | SwissTopo transformations (Windows-only, optional) |
| **Doxygen** | [≥ 1.8.18](https://www.doxygen.nl/download.html) | Developer documentation generation (optional) |
| **GraphViz** | [≥ 2.38](https://graphviz.org/download/) | Visualization in Doxygen (optional) |

### Clone and Configure

```bash
git clone https://github.com/geodetic-metrology-tools/SurveyLib.git
cd SurveyLib
git submodule update --init
```

### Generate project 

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

In order to use a custom `ext_libs.txt` file defining the dependencies, please use:
```bash
$ cmake -G "Visual Studio 16 2019" -A x64 -DEXT_LIBS_TXT_PATH="C:/susoft/SUSoftCMakeCommon/ext_libs.txt" ../source # Use another file defining the dependencies
```

### Build 

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

## Contributing

All contributions are **warmly welcomed** — whether from CERN personnel, collaborators from other institutes, or independent developers interested in large-scale or geodetic metrology software.

### How to Report Issues

- **CERN contributors:**  
  Report or track issues on the [CERN Jira board](https://its.cern.ch/jira/browse/SUS).  
  All internal developments and bug reports must have a corresponding Jira issue.

- **External contributors:**  
  Open a [GitHub Issue](https://github.com/geodetic-metrology-tools/SurveyLib/issues) to:  
  - Report bugs  
  - Suggest improvements or new features  
  - Discuss documentation or CI/CD integration  

> Maintainers will ensure smooth coordination between the internal and public issue-tracking systems.
> Future plans include publishing a consolidated project roadmap, milestone tracker, and CI/CD activity dashboard.

### How to Contribute Code

This repository follows the standard **fork → pull request → review → merge** workflow.
See the [`CONTRIBUTING.md`](./CONTRIBUTING.md) for details about how to contribute for **CERN personnel** and **externals**.

---

## Licensing

SurveyLib source code is licensed under the [GNU General Public License v3.0 or later](LICENSE).

Documentation and metadata (such as configuration and non-code files) are licensed under the [Creative Commons Attribution 4.0 International (CC-BY-4.0)](https://creativecommons.org/licenses/by/4.0/).  
This distinction is defined in [`REUSE.toml`](REUSE.toml).

This project complies with the [REUSE specification](https://reuse.software/), which standardizes license documentation and attribution.

### Third-Party Dependencies

| Library           | License                              | Source                                       |
|-------------------|---------------------------------------|----------------------------------------------|
| Eigen             | MPL-2.0                               | https://gitlab.com/libeigen/eigen            |
| TUT               | BSD 2-Clause "Simplified" License     | https://github.com/mrzechonek/tut-framework  |
| RapidJSON         | MIT                                   | https://github.com/Tencent/rapidjson         |
| Reframe           | Creative Commons Attribution No Derivatives 4.0 International | https://www.swisstopo.admin.ch/en/geodetic-software-resources-dll-jar |
| `counted_ptr.h`   | Custom Permissive License (1999)      | http://snowball.digitalspace.net/cpp/        |

All third-party license texts are stored in the [`LICENSES/`](LICENSES/) directory.  
For an overview of licensing across the project, see [`NOTICE.md`](NOTICE.md).
