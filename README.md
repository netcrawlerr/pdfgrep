# pdfgrep

a lightweight Unix-style CLI for searching text inside PDF files.

[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-064F8C?logo=cmake&logoColor=white)](https://cmake.org/)
[![Poppler](https://img.shields.io/badge/Poppler-PDF-black)](https://poppler.freedesktop.org/)
[![Linux](https://img.shields.io/badge/Platform-Linux-FCC624?logo=linux&logoColor=black)](https://www.linux.org/)

`pdfgrep` is a small command-line utility that extracts text from PDF files using Poppler and searches it for a given pattern.

## Features

**PDF Text Search** — Search for a pattern inside a PDF.
**Case-Insensitive Search** — Ignore letter casing when matching.

## Requirements

Linux, a C++20 compiler, CMake 3.20+, Ninja, `pkg-config`, and Poppler.

### Debian / Ubuntu / Kali

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build pkg-config libpoppler-cpp-dev
```

## Installation

```bash
git clone https://github.com/netcrawlerr/pdfgrep.git
cd pdfgrep

cmake --preset release
cmake --build --preset release
sudo cmake --install out/build-release
```

Verify:

```bash
pdfgrep --version
```

## Usage

```bash
pdfgrep "C++" "/path/to/Introducing C++.pdf"

case insensitive search:
pdfgrep -i "dante" "The Divine Comedy.pdf"
```

## Status

`pdfgrep` is currently an early-stage project focused on the basic PDF text-search workflow. More functionality will be added over time.

## Disclaimer

`pdfgrep` only works with text that can be extracted from a PDF. Scanned or image-only documents may not produce searchable text.

PDF text extraction is handled by **Poppler**, so results may vary depending on the structure and encoding of the source PDF.

All processing is performed locally. `pdfgrep` does not upload PDF contents.

## License

See [`LICENSE`](LICENSE).
