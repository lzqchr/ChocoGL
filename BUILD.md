# 使用 CMake 构建 ChocoGL

## 环境要求

- Visual Studio 2022，并安装“使用 C++ 的桌面开发”工作负载。
- CMake 3.20 或更新版本。
- 如果希望 CMake 一起构建 C# 脚本程序集，需要安装 .NET Framework 4.7.2 Targeting Pack。
- 初始化 Git 子模块：

```powershell
git submodule update --init --recursive
```

## 使用 Visual Studio 生成器

这是 Windows 下推荐的构建方式：

```powershell
cmake --preset vs2022
cmake --build --preset vs2022-debug
```

构建完成后，从下面的位置运行编辑器：

```text
bin/Debug-windows-x86_64/CoCo/CoCo.exe
```

## 使用 Ninja 生成器

请在 x64 Visual Studio Developer Shell 中使用 Ninja，确保 `cl.exe` 已经在环境变量里：

```powershell
cmake --preset ninja-debug
cmake --build --preset ninja-debug
```

## C# 脚本程序集

CMake 会尝试构建 `ChocoGL-ScriptCore.csproj` 和 `ExampleApp.csproj`，并将输出放到：

```text
CoCo/assets/scripts
```

如果当前环境没有 MSBuild 或 .NET Framework Targeting Pack，可以关闭这一步：

```powershell
cmake --preset vs2022 -DCHOCOGL_BUILD_CSHARP=OFF
```

C++ 构建仍会在链接后把 `CoCo/assets`、`assimp` 和 `mono` 运行时 DLL 复制到 `CoCo` 的输出目录。

## Release 构建

当前仓库只包含 Debug 版本的 PhysX 静态库。Release 和 Dist 配置需要在下面目录补齐匹配的 PhysX Release 库：

```text
ChocoGL/vendor/PhysX/lib/Release
```

当这些库存在时，CMake 会自动暴露 Release 和 Dist 配置。
