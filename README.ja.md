# neuro-eye

[English](./README.md) | [Japanese](./README.ja.md)  

||||||
|-|-|-|-|-|
| 元 | 二値化 | 平滑化 | 輪郭強調 | 輪郭位置(左右) |
| フレーム間差分 | 移動輪郭(左右) | 移動方向(左右) | 移動方向(上下) | 移動方向(上下左右) |

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

1. ビルド用ディレクトリの作成

```sh
mkdir build
cd build
```

2. cmake  

```sh
cmake ..
```

3. ビルド

```sh
cmake --build .
```

(Windows用リリースビルドコマンド)  

```sh
cmake --build . --config Release
```
