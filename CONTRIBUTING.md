
# Contributing to SurveyLib

Thank you for your interest in improving **SurveyLib**!  
We welcome code, documentation, and testing contributions from both CERN personnel and external collaborators.

[[_TOC_]]

---

## Developer Certificate of Origin (DCO)

This project uses the [Developer Certificate of Origin (DCO)](./DCO.txt) to certify contributions.

Each commit must include a signed-off line:

```
Signed-off-by: Your Name <your.email@example.com>
```

You can add it automatically using:
```
git commit -s
```

Commits without a valid DCO sign-off cannot be merged.

---

## Branching and Workflow

SurveyLib uses a lightweight branching model compatible with both GitLab (internal) and GitHub (public).

| Branch | Purpose |
|--------|----------|
| `master` | Stable release branch |
| `feature/*` | New features or fixes |

### Contribution Steps

1. **Fork** the repository (external contributors).  
2. **Create a branch** from `master`:  
   ```bash
   git checkout master
   git checkout -b feature/my-feature
   ```
3. **Implement your changes** and add tests.  
4. **Commit** using `git commit -s`.  
5. **Push** your branch and **open a Pull Request** to `master`.  
6. A CERN maintainer will review and merge once CI passes.

---

## Code and Licensing Requirements

### SPDX and Licensing

Each source file must include SPDX headers to ensure REUSE compliance:

**Example (C++ .cpp):**
```cpp
// SPDX-FileCopyrightText: CERN
//
// SPDX-License-Identifier: GPL-3.0-or-later
```

**Example (C++ header file):**
```cpp
/*
 * SPDX-FileCopyrightText: CERN
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */
```

### Non-code Files

Non-source files (e.g., `.png`, `.pdf`, `.txt`, `.docx`) must be declared in [`REUSE.toml`](./REUSE.toml).  
License texts for all dependencies are stored under [`LICENSES/`](./LICENSES/).

### REUSE Compliance Check

Install the **REUSE tool**:

```bash
pip install reuse
# or
sudo apt install reuse
```
For more options, see the [official installation guide](https://reuse.readthedocs.io/en/stable/readme.html#installation).

Validate before pushing:
```bash
reuse lint
```

If compliant, you will see:
```
Congratulations! Your project is REUSE compliant.
```

When adding new files:
- Prefer to add SPDX headers directly inside text-based files.  
- If headers are not possible (e.g. for images, binaries, PDFs, test data), update `REUSE.toml` to include them.  
- Always make sure external dependencies are listed in [NOTICE.md](./NOTICE.md) and their license texts are present in `LICENSES/`.

---

## Testing and CI/CD

SurveyLib includes unit tests based on **TUT**.  
You can build and run tests locally:

```bash
cmake --build . --target UnitTests
```

### Continuous Integration

| Platform | Trigger | Description |
|-----------|----------|-------------|
| **CERN GitLab** | Merge or push to protected branches | Full builds and tests |
| **GitHub (planned)** | Pull Request | Basic build and test validation |

External PRs currently do not trigger internal CI/CD pipelines.  
Maintainers manually validate and merge approved contributions.

---

## Code of Conduct

SurveyLib contributors are expected to uphold **CERN’s core values** of:

- **Respect** — Treat all contributors and users with courtesy.  
- **Collaboration** — Share knowledge and support each other’s work.  
- **Openness** — Promote transparency and reproducibility in science.

---

## Contacts and Maintainers


You may reach the maintainers via GitHub discussions or CERN internal email lists.

---

Thank you for helping make **SurveyLib** a robust, open, and scientifically reliable software platform!
