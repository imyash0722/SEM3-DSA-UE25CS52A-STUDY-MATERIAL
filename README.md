# DSA Study Website - UE25CS52A

This repository contains a complete static study website for **Data Structures & Applications (UE25CS52A)** built with [Zensical](https://zensical.org/) (Material for MkDocs theme).

## 🌐 Live Site
**https://imyash0722.github.io/SEM3-DSA-UE25CS52A-STUDY-MATERIAL/**

## 📚 Content Coverage

| Unit | Topics |
|------|--------|
| **Unit 1** | Functions, Pointers, Arrays, Structures, Dynamic Memory, ADTs, Linked Lists, Stacks, Stack Applications |
| **Unit 2** | Circular Lists, Doubly Linked Lists, Queues (LL & Array), Priority Queues (5 implementations), Deques |
| **Unit 3** | BST (Dynamic + Array), Expression Trees, Threaded Trees, Heaps, AVL Trees, Splay Trees, Graphs |
| **Unit 4** | Graph Representations & Traversals, Connected Components, Path Finding, Hash Tables, Tries, Suffix Trees |

## 🛠️ Tech Stack

- **Static Site Generator**: [Zensical](https://zensical.org/) (Material for MkDocs)
- **Theme**: Material for MkDocs (Zensical fork)
- **Hosting**: GitHub Pages
- **CI/CD**: GitHub Actions

## 🚀 Quick Start

### Prerequisites
```bash
# Python 3.11+
python -m pip install --upgrade pip
pip install zensical
```

### Local Development & Offline Viewing
```bash
# Easy One-Click Offline Launcher (Windows / Linux / macOS):
cd site
./launch_offline.sh    # On Linux / macOS
launch_offline.bat     # On Windows (or double click in File Explorer)

# Or manual build:
cd site
pip install -r requirements.txt
zensical build --config-file zensical.yml
```

### Project Structure
```
├── site/                           # Self-contained website folder
│   ├── dist/                       # Built static site (HTML/CSS/JS, deployed to gh-pages)
│   ├── docs/                       # Markdown source documentation
│   ├── overrides/                  # Theme overrides (dark/light toggle, custom layout)
│   ├── zensical.yml                # Zensical site configuration
│   ├── requirements.txt            # Python dependencies (zensical)
│   ├── launch_offline.py/.sh/.bat  # One-click offline server launchers
│   └── scripts/                    # Deployment scripts
├── model/                          # Local AI model benchmarks (Qwen 2.5 Coder)
├── organized/                      # Semester 3 DSA Course materials & labs
├── .github/workflows/deploy.yml    # GitHub Actions deployment workflow
└── README.md
```

## 📝 Adding Content

### 1. Create/Edit Markdown in `notes/`
```bash
# Edit or create files in notes/
# e.g., notes/unit4_graphs_hashing_tries.md
```

### 2. Copy to `docs/` (Zensical source)
```bash
cp notes/unit4_*.md docs/
```

### 3. Update `zensical.yml` nav
```yaml
nav:
  - Home: index.md
  - "Unit 4: Graphs, Hashing, Tries, Suffix Trees":
      - "Unit 4 Overview": unit4_graphs_hashing_tries.md
      - "Example Programs": unit4_example_programs.md
```

### 4. Build & Test Locally
```bash
zensical build --config-file zensical.yml
# Check site/ folder
```

### 5. Deploy
```bash
git add -A
git commit -m "Add: Unit 4 content"
git push origin main
# GitHub Actions workflow auto-deploys to GitHub Pages
```

## 🔧 Configuration

### Zensical Config (`zensical.yml`)
Key settings:
- `site_name`: Display name
- `theme.palette`: Primary/accent colors (indigo)
- `theme.features`: Navigation, search, code copy, dark mode
- `extra_javascript`: Custom JS for theme toggle
- `markdown_extensions`: Tasklists, code highlighting, tabs, TOC

### Theme Override (`overrides/assets/javascripts/theme-toggle.js`)
Adds dark/light mode toggle button to header (fixes Zensical missing toggle).

### Dark/Light Toggle
The theme toggle is injected via custom JavaScript since Zensical doesn't include it by default.

## 📦 Requirements
```txt
# requirements.txt
zensical
```

## 🔄 CI/CD Pipeline

The `.github/workflows/deploy.yml`:
1. Triggers on push to `main` branch
2. Checks out code
3. Sets up Python 3.11
4. Installs dependencies from `requirements.txt`
5. Runs `zensical build --config-file zensical.yml`
6. Uploads `site/` artifact
7. Deploys to GitHub Pages

## 🎯 Features

- ✅ Dark/Light mode toggle
- ✅ Full-text search
- ✅ Code copy buttons
- ✅ Interactive tasklists (checkboxes)
- ✅ Navigation tabs per unit
- ✅ Auto-expanding sections
- ✅ Table of contents (right sidebar)
- ✅ Mobile responsive
- ✅ Syntax highlighting with line numbers
- ✅ Tabbed content blocks
- ✅ Admonitions (notes, warnings, tips)

## 📖 Source Materials

Based on:
- **Primary Textbook**: "Data Structures using C/C++" by Tenenbaum, Augenstein, Langsum (Pearson, 2nd ed., 2015)
- **Reference**: "Data Structures and Program Design in C" by Kruse et al. (Pearson, 2nd ed., 2019)
- **Course**: UE25CS52A - Data Structures & Applications
- **Instructor**: Prof. N S Kumar (nskumar@pes.edu)

## 📄 License

Educational use only. Course materials property of respective instructors.

---

## 🔗 Links

- **Repository**: https://github.com/imyash0722/SEM3-DSA-UE25CS52A-STUDY-MATERIAL
- **Live Site**: https://imyash0722.github.io/SEM3-DSA-UE25CS52A-STUDY-MATERIAL/
- **Zensical Docs**: https://zensical.org/
- **Material for MkDocs**: https://squidfunk.github.io/mkdocs-material/