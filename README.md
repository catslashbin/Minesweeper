# Minesweeper

> Group 34: Catslashbin & Tianzeds

## 编译运行

We have tested the game on Ubuntu 22.04 & macOS 13.0.

Win version is not tested, but should act well after some deployments.

### Linux

1. 安装 Basic C++ Toolkit
   ```bash
   sudo apt-get install gcc build-essential make cmake
   ```
2. Install game deps
   ```bash
   sudo apt-get libsfml-dev libspdlog-dev
   ```
3. Build the game
   ```bash
   sh ./build.sh
   ```
4. Run Minesweeper
   ```
   cd build
   ./Minesweeper
   ```

### macOS

1. 从官网下载 SFML，并参阅 [官方教程](https://www.sfml-dev.org/tutorials/2.5/start-osx.php) 完成安装。

2. 安装 x86_64 版本的 Homebrew，并安装 x86_64 版本的 spdlog。（如果为 M1 芯片，参阅 [介绍](https://medium.com/mkdir-awesome/how-to-install-x86-64-homebrew-packages-on-apple-m1-macbook-54ba295230f#)）

3. 使用如下命令编译并运行。
   ```bash
   ./build-macos.sh
   ./build/Minesweeper
   ```

## 设计结构

### 项目结构

我们采用 C++ 跨平台轻量级 UI 库 `SFML` 实现了扫雷游戏。  
游戏结构参考了游戏引擎的实现，主要分为 资源管理，场景调度，组件实现，核心逻辑 四个部分。

#### 资源管理

我们实现了一个资源池用于管理所有游戏资源，防止资源被反复从硬盘读入内存。  
采用伪单例模式实现。见 `ui/utils/res_pool`。

#### 场景调度

游戏实现了4个场景 (Scene)：菜单场景、游戏场景、自定义设置场景与测试场景。

- 场景基类 `ui/scene.hpp`
- 调度实现见 `ui/game.hpp`

场景调度负责管理游戏的各个场景，包括场景的创建、销毁、切换操作。  
在本项目采用了场景管理器 (Game) 来实现场景调度的功能。管理器同时负责统一更新、绘制组件。

#### 组件实现

组件是游戏中的基本元素，继承自 `SFML::Shape` 或 `SFML::Drawable`。  
在本项目实现了一些常用的组件：可点击组件 (Clickable)、圆角矩形 (Rounded) 等。  
组件实现主要依赖于 SFML 库提供的图形界面功能。

同时由于 SFML 不提供按钮组件，项目实现 `ClickableShape<T>` 模板类包装器用于封装任何 `SFML::Shape`
的子类为可点击对象。`Clickable` 类实现提供了事件回调函数，将由场景管理器统一调用。

#### 核心逻辑

游戏的核心逻辑主要包括扫区域的生成、雷的布置、游戏状态的管理、游戏操作的处理等等。  
在本项目中将核心逻辑封装在 `core` 目录。游戏核心包括扫雷逻辑的实现、游戏状态的管理、游戏操作的处理。`core.hpp` 为核心层的
C++ 的接口封装，方便其他模块调用。

### 文件结构

```
· 
├── build.sh                           # 构建脚本
├── CMakeLists.txt                     # CMake 配置文件
├── README.md                          # 项目说明文档
├── src                                # 源代码目录
│   ├── cli.c                          # 命令行界面实现
│   ├── core                           # 游戏核心实现目录，OJ 与 GUI 版本公用
│   │   ├── core.c                     # 游戏核心实现 C 文件
│   │   ├── core.h                     # 游戏核心实现头文件
│   │   └── core.hpp                   # C++ 的核心层接口封装
│   ├── main.cpp                       # GUI 版游戏入口
│   ├── test.c                         # CLI 版游戏入口
│   └── ui                             # 用户界面实现目录
│       ├── assets                     # 资源文件目录
│       │   ├── *.png                  # 图片资源
│       │   └── *.ttf                  # 字体资源
│       ├── components                 # 组件实现目录
│       │   ├── clickable.cpp          # 可点击对象实现
│       │   ├── clickable.hpp          # 可点击对象基类头文件
│       │   ├── mine_cell.cpp          # 扫雷格子实现
│       │   ├── mine_cell.hpp          # 扫雷格子类头文件
│       │   ├── mine_field.cpp         # 扫雷区域实现
│       │   ├── mine_field.hpp         # 扫雷区域类头文件
│       │   ├── rounded.cpp            # 圆角矩形实现
│       │   ├── rounded.hpp            # 圆角矩形头文件
│       │   ├── text_field.cpp         # 文本框实现
│       │   └── text_field.hpp         # 文本框头文件
│       ├── game.cpp                   # 场景调度实现
│       ├── game.hpp                   # 场景调度头文件
│       ├── scene.cpp                  # 场景管理实现
│       ├── scene.hpp                  # 场景管理头文件
│       ├── scenes                     # 各个场景实现目录
│       │   ├── custom_scene.cpp       # 自定义场景实现
│       │   ├── custom_scene.hpp       # 自定义场景头文件
│       │   ├── field_scene.cpp        # 游戏场景实现
│       │   ├── field_scene.hpp        # 游戏场景头文件
│       │   ├── menu_scene.cpp         # 菜单场景实现
│       │   └── menu_scene.hpp         # 菜单场景头文件
│       └── utils                      # 工具类目录
│           ├── consts.hpp             # 常量定义头文件
│           ├── difficulty.hpp         # 难度设置头文件
│           ├── res_pool.cpp           # 资源池实现
│           └── res_pool.hpp           # 资源池头文件
└── test                               # 测试代码目录
    ├── test_main.cpp                  # 测试入口
    ├── test_scene.cpp                 # 场景测试实现
    └── test_scene.hpp                 # 场景测试头文件
```