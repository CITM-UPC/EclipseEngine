# EclipseEngine
A 3D game engine made from scratch by 4 university students for the Game Engines subject.

![demo2](https://github.com/user-attachments/assets/5090b320-c296-4dca-992d-bb50cdcd8e89)

## The Team
This team is composed by:
- **Marc San José**: [https://github.com/marcsjm19](https://github.com/marcsjm19)
- **Miguel Tamaño**: [https://github.com/migon25](https://github.com/migon25)
- **Oscar Escofet**: [https://github.com/OscarEFO](https://github.com/OscarEFO)
- **Marc Gallardo**: [https://github.com/Marchusky](https://github.com/Marchusky)

## New Features 
- **Street Enviroment Scene is automatically loaded when starting the engine**
- **Transformation and Game Object Hierarchy**
  - The user can use the inspector to modify a game object; drop any mesh or texture...
- **Improved Resource Management**
  - Assets window that shows all assets.
  - The user can drop/import new files and the assets panel.
  - Asset files can be renamed and deleted through the panel.
 ![AssetsPanel](https://github.com/user-attachments/assets/40e300e9-ca6c-48b4-97a0-27056d7cb263)
![AssetsPanel2](https://github.com/user-attachments/assets/4e399d2e-4bee-4c55-9188-a94968b30d34)

## Extra Features 
- Change use of **shader** rendering settings:
  - "O" for **default** render.
  - "P" for **position** shader.![PositionTest](https://github.com/user-attachments/assets/88b10285-f49c-42ce-96c1-178a66add9f6)

  - "I" for **depth** shader.![DepthTest2](https://github.com/user-attachments/assets/15c04910-e1dc-49be-ae50-681baae193fc)

  - "U" for **normals** shader. ![NormalsTest2](https://github.com/user-attachments/assets/1fcbba51-976c-42af-8c3a-a1a8fc72956f)

- Functional transformation **buttons** in the viewport:
  - **Translate**
  - **Rotation**
  - **Scale**
  - Switch between **Local & Global** transforms.
  - ![TransformButtons](https://github.com/user-attachments/assets/89dc7aa6-ecd9-4fe8-a9d6-fc96088851a0)

- Game Objects **AABB** visual.
- Outlining Selected objects.
- Viewport and Game Panel separated.
- Panels are dockable and can be separated outside the window.


## Key Functionalities
- **File Handling**:
  - Supports drag-and-drop of **FBX** files from any location on the hard drive.
  - Accepts **DDS/PNG** files for texture application to selected GameObjects.

- **GameObject Structure**:
  - Each loaded mesh creates a **GameObject** with three display-only components: **Transform**, **Mesh**, and **Texture**.

- **Camera Controls**:
  - **Right-click + WASDQE**: FPS-like movement and free look.
  - **Mouse Wheel**: Zoom in and out.
  - **Mouse Wheel click**: Pan camera.
  - **Alt + Left Click**: Orbit the object.
  - Holding **SHIFT**: Increases movement speed.

- **Editor Windows**:
  - **Console**:
    - Logs the geometry loading process from ASSIMP and external library initialization.
  - **Configuration**:
    - Graph for FPS display.
    - Adjustable settings for window.
  - **Hierarchy**:
    - Lists all GameObjects; allows selection of GameObjects.
  - **Inspector**:
    - Displays component details of the selected GameObject:
      - **Transform**: Position, rotation, and scale (read-only).
      - **Texture**: Shows texture.

- **General Menu**:
  - Options to quit the engine, visit the GitHub page, and view engine information (“About”).
  - Ability to turn panels on/off.

## How to Use the Engine
1. Drag and drop **FBX** files from asset panel and **DDS/PNG** textures into the viewport panel.
2. Use the **camera controls** for navigating the scene only inside viewport panel.
3. Access **Editor Windows** for GameObject management and detailed information.
4. Edit and transform the **FBX** files using the move, rotate or scale options.
5. Import **FBX file** into **custom file format** to the **"Library/"** folder.
