🌌 **Voxel World**  
[![Build Status](https://img.shields.io/badge/build-C%2B%2B11-green)](https://github.com/example/voxel-world)

A 3D voxel terrain exploration game built with OpenGL and C++. Featuring procedural terrain generation, physics-based movement, and efficient instanced rendering.

---

## 🛠️ Features  
- **Procedural Terrain Generation**: Fractal noise-based landscape creation  
- **Dynamic Camera System**: Follows character with smooth orbital movement  
- **Physics-based Movement**: Collision detection and terrain interaction  
- **Instanced Rendering**: Optimized cube drawing with OpenGL instancing  
- **Interactive Lighting**: Dynamic light source with ambient/diffuse effects  

---

## 📚 Dependencies  

Ensure GLM is in your include path:  
```bash
git submodule add https://github.com/g-truc/glm.git
```

---

## 🧱 Build Instructions  
```bash
git clone https://github.com/xiejiongru/opengl.git
cd  opengl
mkdir build && cd build
cmake .. && make
./main
```

---

## 🕹️ Controls  
| Action        | Key           | Functionality             |
|---------------|---------------|---------------------------|
| 🔄 Rotation   | Q / E         | Turn left/right           |
| 🚶 Movement   | W / A / S / D | Forward/left/backward/right |
| 📊 View       | Mouse         | Look around (drag)        |

---

## 🏞️ Code Structure  
- **Camera.h/cpp**: Orbital camera system with yaw/pitch control  
- **Character.h/cpp**: Physics-aware movement and collision handling  
- **Terrain.h/cpp**: Procedural heightmap generation and rendering  
- **Cube.h/cpp**: Instanced cube rendering with VAO/VBO management  
- **InstancedRenderer.h/cpp**: GPU-accelerated batch drawing system  

---

## 🤝 Contribution  
Contributed by XIE Jiongru, TSI 2024, ENSG


---

## 📄 License  
MIT License  
```text
Copyright (c) 2023 Voxel World Developers  
Permission is hereby granted, free of charge, to any person obtaining a copy...
```
