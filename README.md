# osie

## Table of contents

- 1.0 [About](#10-about)
- 2.0 [Usage](#20-usage)
- 3.0 [Compiling](#30-compiling)
- 4.0 [Licensing](#40-licensing)

## 1.0 About

osie (OpenTTD screenshot information extractor) extracts the information
stored in OpenTTD's PNG screenshots such as the version, NewGRFs and AIs.

## 2.0 Usage

You use osie by passing it the filename of the screenshot you want to get
the information from. osie will extract the data and print this to the
console.

## 3.0 Compiling

osie requires `libpng` as a library to be compiled.
On Windows we recommend using [vcpkg](https://github.com/Microsoft/vcpkg/) to install the libraries.

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## 4.0 Licensing

osie is licensed under the GNU General Public License version 2.0. For
more information, see the file 'LICENSE'.
