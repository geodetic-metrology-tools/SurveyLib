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

## GitHub vs GitLab Notice

Historically, the **SurveyLib** project has been developed within **CERN’s GitLab environment** (`gitlab.cern.ch`).  

The project is now entering a **transition phase** toward a more open and collaborative model.  
Development will progressively move to **GitHub**, with future updates.
This migration aims to make the project’s source code, issue tracking, and documentation more accessible to the broader scientific and open-source communities.  
It also creates new opportunities for **community contributors** to participate in development, testing, and documentation improvements.

For the time being, the **continuous integration and deployment (CI/CD)** processes continue to run on CERN’s GitLab infrastructure.
In a later phase, the CI/CD system will also be **migrated to GitHub**, providing a unified, open workflow for building, testing, and packaging the software.  
This migration will represent a **valuable entry point for contributors**.

> During this transition, both GitLab and GitHub repositories will remain synchronized,  
> and development activity will increasingly focus on GitHub.  
> For contribution procedures, please continue reading below.

---

## Documentation

### Developer Documentation

SurveyLib is intended for **developers** integrating it into other software.  
Documentation and usage notes are available here:

- **[CERN Confluence Page](https://confluence.cern.ch/display/SUS/SurveyLib+User+Guide)** (only accessible for CERN users)  

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

### Submodules and External Dependencies

**SurveyLib** depends one submodules:

| Submodule | Purpose | Repository (Internal) | Repository (Public) |
|------------|----------|----------------------|---------------------|
| **SUSoftCMakeCommon** | Common CMake configuration, packaging setup, and compiler options | `https://gitlab.cern.ch/apc/susofts/shared/SUSoftCMakeCommon` | `https://github.com/geodetic-metrology-tools/SUSoftCMakeCommon` |

**SurveyLib**  also uses the following third-party libraries fetched automatically via CMake’s [`FetchContent`](https://cmake.org/cmake/help/latest/module/FetchContent.html):

- [**RapidJSON**](https://github.com/Tencent/rapidjson) – A fast JSON parser/generator for C++ with both SAX/DOM style API.
  _Licensed under the [MIT license](https://spdx.org/licenses/MIT.html)._

You do **not** need to install it manually.

#### Windows Environment (External Setup)

If you are developing on **Windows**, follow these summarized steps adapted from the typical setup:

1. **Install Visual Studio 2019 or later**  
   - Launch Visual Studio Installer → *Modify Installation* → *Individual Components* tab.  
   - Ensure the following components are selected:  
     - *C++ 2019 Redistributable Update*  
     - *MSVC v142 - VS 2019 C++ x64/x86 build tools*  
     - *C++ core features*  
     - *Windows 10 SDK (10.0.16299.0)* or later  

2. **Install Git for Windows**   
   - Ensure the installer adds Git to your system PATH.

3. **Install CMake**  
   - Download from [https://cmake.org/download/](https://cmake.org/download/).  
   - During installation, select *Add CMake to PATH for all users*.  

4. **Install NSIS (optional, for packaging)**  
   - Download version 3.05 from [https://nsis.sourceforge.io/Download](https://nsis.sourceforge.io/Download).

5. **Install Eigen and TUT**  
   - Clone Eigen:  
     ```bash
     git clone https://gitlab.com/libeigen/eigen.git
     cd eigen && git checkout 3.4.0
     ```  
   - Clone TUT:  
     ```bash
     git clone https://github.com/mrzechonek/tut-framework.git
     cd tut-framework && git checkout 2016-12-19
     ```  
   - Place both in a directory accessible to your project (e.g. `C:\susoft\ext\`).

6. **Install Doxygen and GraphViz (optional)**  
   - [Doxygen](https://www.doxygen.nl/download.html)  
   - [GraphViz](https://graphviz.org/download/) (add `bin/` directory to PATH)

7. **Install Reframe (optional)**
   - Download and install Reframe from [SwissTopo website](https://www.swisstopo.admin.ch/en/geodetic-software-resources-dll-jar)
   
> This setup represents the standard CERN configuration but can be adapted as needed.

### Clone and Configure the Repository

#### Clone the repository

- **from gitlab.cern.ch (if accessible):**
  ```bash
  git clone https://gitlab.cern.ch/apc/susofts/libraries/SurveyLib.git
  ```
 
- **from github:**
  ```bash
  git clone https://github.com/geodetic-metrology-tools/SurveyLib.git
  ```

Then:
```bash
cd SurveyLib
```

#### Submodule Setup


- **from gitlab.cern.ch (if accessible)**
  ```bash
  git submodule update --init
  ```

- **from github:**
  **SUSoftCMakeCommon** submodule is publicly available.  
  
  ```bash
	# Initialize submodules without fetching content yet
	git submodule init
	
	# Fix URLs for public repositories
	git config submodule.lib/SUSoftCMakeCommon.url https://github.com/geodetic-metrology-tools/SUSoftCMakeCommon.git
	
	# Fetch content from the corrected public URLs
	git submodule update --remote lib/SUSoftCMakeCommon
  ```

> The submodule **SUSoftCMakeCommon** is not need if **SurveyLib** is used as a submodule for **LGC2**

##### External Dependency Configuration

**SUSoftCMakeCommon** provides:

- Default compiler and build flags
- Doxygen setup options
- Installer and packaging configuration (`create_default_installer`)
- Helper functions for DLL copy and installer generation

External developers can adjust `"lib/SUSoftCMakeCommon/ext_libs.txt"` to define paths for locally installed dependencies:
```cmake
set(EXT_LIB_PATH "C:/dev/ext")
set(EIGEN_INCLUDE_PATH "${EXT_LIB_PATH}/eigen")
set(TUT_INCLUDE_PATH "${EXT_LIB_PATH}/tut-framework")
```

These paths can also be overridden at configuration time:
```bash
cmake -DEXT_LIBS_TXT_PATH="C:/path/to/custom/ext_libs.txt" ../source
```


### Generate project 

We use CMake to generate projects, thus it is possible to generate projects for MSVC, Eclipse, or simple Unix makefiles. See the [CMake Generators documentation](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html) page.

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

All contributions are **warmly welcomed** — whether from CERN personnel, collaborators from other institutes, or community contributors interested in large-scale or geodetic metrology software.

### How to Report Issues

- **CERN contributors/Users:**  
  Report or track issues on the [CERN Jira board](https://its.cern.ch/jira/browse/SUS).  
  All developments and bug reports must have a corresponding Jira issue.
  
- **Community contributors:**  
  Open a [GitHub Issue](https://github.com/geodetic-metrology-tools/SurveyLib/issues) to:  
  - Report bugs  
  - Suggest improvements or new features  
  - Discuss documentation or CI/CD integration  


> Maintainers will ensure smooth coordination between JIRA and GitHub issue-tracking systems. Some automation from JIRA to Github could be implemented.
> Future plans include publishing a consolidated project roadmap, milestone tracker, and CI/CD activity dashboard.

### How to Contribute Code

This repository follows the standard **fork → pull request → review → merge** workflow.
See the [`CONTRIBUTING.md`](./CONTRIBUTING.md) for details about how to contribute.

---

## Licensing

SurveyLib is licensed under the [GNU General Public License v3.0 or later (GPL-3.0-or-later)](LICENSE).

Documentation, metadata, and non-code assets (e.g., configuration or documentation files) are licensed under the [Creative Commons Attribution 4.0 International (CC-BY-4.0)](https://creativecommons.org/licenses/by/4.0/).

This distinction and file classification are defined in [`REUSE.toml`](./REUSE.toml).

### Third-Party Dependencies

| Library           | License                              | Source                                       |
|-------------------|---------------------------------------|----------------------------------------------|
| Eigen             | MPL-2.0                               | https://gitlab.com/libeigen/eigen            |
| TUT               | BSD 2-Clause "Simplified" License     | https://github.com/mrzechonek/tut-framework  |
| RapidJSON         | MIT                                   | https://github.com/Tencent/rapidjson         |
| Reframe           | Creative Commons Attribution No Derivatives 4.0 International | https://www.swisstopo.admin.ch/en/geodetic-software-resources-dll-jar |
| `counted_ptr.h`   | Custom Permissive License (1999)      | http://snowball.digitalspace.net/cpp/        |
| SUSoftCMakeCommon | GPL-3.0-or-later | [https://github.com/geodetic-metrology-tools/SUSoftCMakeCommon](https://github.com/geodetic-metrology-tools/SUSoftCMakeCommon) |

All third-party license texts are stored in the [`LICENSES/`](LICENSES/) directory.  
For an overview of licensing across the project, see [`NOTICE.md`](NOTICE.md).

### License Compliance (REUSE)

This project follows the [REUSE Specification](https://reuse.software/) to ensure proper copyright and license attribution.

To verify compliance, install the **REUSE tool** and run:

```bash
reuse lint
```

If successful, you’ll see:
```
Congratulations! Your project is REUSE compliant.
```

When adding new files:
- Add SPDX headers directly to text-based files where possible.  
- If headers are not possible (e.g., binaries, PDFs), list them in [`REUSE.toml`](./REUSE.toml).  
- Add any new third-party licenses to the [`LICENSES/`](./LICENSES/) folder.

---

Thank you for contributing to this project and helping us make **geodetic metrology software** open, reliable, and accessible to the wider community!
