# What is Rt
Rt is a Ray Tracer, this is a pedagocial project from 42 school, the project has
to be in "C" language, at the 42 norm: https://cdn.intra.42.fr/pdf/pdf/317/norme.fr.pdf

The project subject is available here: https://cdn.intra.42.fr/pdf/pdf/33/rt.fr.pdf

# Keys
| Key           | Purpose                                   |
|:--------------|:------------------------------------------|
| arrow left    | rotate camera left                        |
| arrow right   | rotate camera right                       |
| arrow up      | rotate camera up                          |
| arrow down    | rotate camera down                        |
| q             | roll camera left                          |
| e             | roll cammera right                        |
| ctrl / c      | move camera down                          |
| space         | move camera up                            |
| w/a/s/d       | move camera                               |
| i             | toggle interface                          |
| x             | display the current scene to stout in sda |
| l             | dispay debug on stdout (current tree)     |
| 1             | red filter                                |
| 2             | green filter                              |
| 3             | blue filter                               |
| 4             | purple filter                             |
| 5             | yellow filter                             |
| 6             | cyan filter                               |
| 7             | sepia filter                              |
| m             | switch to next camera                     |
| shift         | move faster (wasdeq...)                   |
| r             | reset camera                              |
| y             | save current camera                       |
| p             | force rebuild of current scene            |
| f             | toggle full screen                        |
| t             | display current used textures             |
| o             | display camera matrix                     |

# Formats
There is two supported formats for this project: the first one developed was
". Very quicly we needed a more flexible format: the .sda files
### Yolo
yolo" files, those are simple files, each object is described in one line and
parameters are separated with a simple space
### Sda
for "Scene Describe Archive" are a more complex files format, having defaults
parameters, and non mandatory values

# Command line parameters
| Parameter           | Utility                                        |
|:--------------------|:-----------------------------------------------|
| -f                  | start in full screen                           |
| -s 1020x1080        | specify resolution                             |
| -e scene.yolo       | convert a .yolo scene to a .sda one            |
| -b scene target.bmp | render the image into a file instead of window |
| -h                  | display help then quit                         |

# Capabilities
- Reflections (on all object)
- Refraction
- Textures
- Transparency
- Normal mapping
- Multiple lighting

# Screenshoot
![Image](https://github.com/Chr0nos/rt/blob/master/screenshoots/earth.png "image")


# Compile
## Archlinux
```shell
sudo pacman -S extra/sdl2 extra/sdl2_ttf extra/sdl2_image make clang
make
```

## Ubuntu
```shell
sudo apt install libsdl2-ttf-dev libsdl2-dev build-essential libsdl2-2.0-0 libsdl2-ttf-2.0-0 libsdl2-image-2.0-0 libsdl2-image-dev clang
make
```
