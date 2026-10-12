# Syntaktis Hex Editor

## Dependencies
- Dear ImGui (Installed as submodule): Graphics User Interface.
- GLFW: creates window.
- OpenGL: renders GUI.

## Install GLFW and OpenGL files:
### Fedora
```
sudo dnf install glfw-devel mesa-libGL-devel
```

### Arch
```
sudo pacman -S glfw mesa
```

### Debian
```
sudo apt install libglfw3 libglfw3-dev libgl1-mesa-dev
```

## Build
```
git clone --recurse-submodules https://github.com/exercsie/Syntaktis-Hex-Editor
cd Syntaktis-Hex-Editor
make SyntaktisHexEditor
```

## Install
```
sudo cp Build/SyntaktisHexEditor /usr/local/bin
```