WARNING! Project was moved to Perforce Server. You can log to it at ec2-35-164-134-176.us-west-2.compute.amazonaws.com:1666 using guest account.

# Tropical Engine - OpenGL4 C++ 3D Game Engine #

Author: Adam "Fartuess" Beczyński

"TropicalEngineComponentArchitecture" - Current Project

WARNING! Due to use of Git-LFS Project can't be downloaded in form of a zip, but has to be pulled using git with git-lfs extension (some git clients have built in git-lfs support)

### Languages technologies and libraries used ###
* C++
* OpenGL4
* GLSL
* Qt5
* Open Asset Importer
* FBX SDK
* GLEW
* GLM
* OpenExr

### Features ###
#### Architecture and Gameplay Scripting ####
* Component architecture
* Easy gameplay coding with IUpdate'able interface
* Input Management System which allows creating abstract input actions and binding physical keys to them.
* Level and asset serialization
* Importing models using Open Asset Importer or FBX SDK.
* Importing levels from FBX allows creating them in 3D applications like Maya, 3ds Max or Blender.

#### Shaders and Materials ####
* Flexible system of managing shaders and materials
* Shaders builders allow creating shaders from modules. Shader builder can create shaders for multiple passes from one set of modules.
* Various lighting models (Phong, Blinn-Phong, Cook-Torrance, Strauss, Isotropic Ward, Anisotropic Ward)
* Bump mapping (normal mapping)
* Steep Parralax Mapping
* Alpha testing (aka masked translucency)
* Adaptive tessalation
* Vertex displacement and vector displacement.
* Directional lights, Point lights, Spot lights and ambient lights.
* LUT postprocessing
* Simple early Reflection Probes implementation.

#### Interface ####
* Qt interface
* Custom style of interface
* Custom window frame
