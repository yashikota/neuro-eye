# neuro-eye

[English](./README.md) | [Japanese](./README.ja.md)  

||||||
|-|-|-|-|-|
| Original | Threshold | Blur | Highlight edge | Position edge(Left, Right) |
| Frame diff | Move edge(Left, Right) | Direction(Left, Right) | Direction(Up, Down) | Direction(Up, Down, Left, Right) |

## Dependencies

- Opencv 4.5.1
- CMake 3.27

## Usage

### Linux

```sh
./neuro-eye
```

### Windows

```sh
./Release/neuro-eye.exe
```

## Options

## Build

1. make build directory  

```sh
mkdir build
cd build
```

2. cmake  

```sh
cmake ..
```

3. build

```sh
cmake --build .
```

(Release build command for Windows)  

```sh
cmake --build . --config Release
```
