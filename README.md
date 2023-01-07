# DinoDungeon

[ダウンロード](https://github.com/AtropsCooper/demogame-cpp/releases)

## 遊び方

WASDで移動できます。

マウスで照準・射撃を行います。

ESCキーを押すと、ゲームが一時停止し、メニューが表示されます。

## ライブラリ

以下のライブラリを利用しています。

* [SDL](https://github.com/libsdl-org/SDL)
* [SDL_mixer](https://github.com/libsdl-org/SDL_mixer)
* [SDL_ttf](https://github.com/libsdl-org/SDL_ttf)
* [SDL_image](https://github.com/libsdl-org/SDL_image)

# Building the Game

Windows 10 と macOS Montery では、以下の手順を従ってビルド可能です。

他の OS でのビルドも可能ですが、サポートはできません。

## Windows MinGW でビルド

パックマネージャー [chocolatey](https://chocolatey.org/) の利用を推奨します。
以下は、chocolateyが利用可能な環境でのガイドです。

### ビルド環境取得

```powershell
choco install make mingw -y
```

### ライブラリをインストール

まず、[ライブラリ](#ライブラリ)の mingw 版をダウンロードしてください。
そして、`x86_64-w64-mingw32`フォルダにあるすべてのファイルを`<path_of_chocolatey>\lib\mingw\tools\install\mingw64`にコピーしてください。

### ソースコード取得

```powershell
git clone https://github.com/AtropsCooper/demogame-cpp
```

### ビルド

```powershell
cd demogame-cpp
make
```

ビルドされたゲームは`build/bin/DinoDungeon.exe`となります。

## macOS

### ライブラリ取得

```bash
brew update
brew install sdl2 sdl_image sdl_ttf sdl_mixer
```

### ソースコード取得

```bash
git clone https://github.com/AtropsCooper/demogame-cpp
```

### ビルド

```bash
cd demogame-cpp
make -f Makefile.OSX
```

ビルドされたゲームは`build/bin/DinoDungeon.app`となります。
