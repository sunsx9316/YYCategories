# CLAUDE.md

本文件为 Claude Code (claude.ai/code) 在此仓库中工作时提供指导。

## 项目概述

YYCategories 是一组实用的 Foundation 和 UIKit 的 Objective-C Category 扩展，是 [YYKit](https://github.com/ibireme/YYKit) 组件套件的一部分。它为系统类提供便捷方法，使用无前缀的 Category 命名方式，调用体验上接近系统原生 API。

最低部署目标：iOS 12.0+ / macOS 10.13+ / tvOS 12.0+（SPM），iOS 6.0+ / tvOS 12.0+（CocoaPods）。

## 构建命令

仓库中没有 Xcode 项目文件。构建验证通过 SPM 或 CocoaPods 集成到宿主工程中进行。

```bash
# SPM 构建 (iOS)
swift build --triple arm64-apple-ios

# SPM 构建 (macOS)
swift build --triple arm64-apple-macos

# SPM 构建 (tvOS)
swift build --triple arm64-apple-tvos

# CocoaPods 校验
pod lib lint YYCategories.podspec --allow-warnings
```

本项目没有测试用例。

## 架构

代码按三个功能分组组织在 `YYCategories/` 目录下：

- **Foundation/** — 对以下 Foundation 类的 Category 扩展：`NSObject`、`NSString`、`NSData`、`NSArray`、`NSDictionary`、`NSDate`、`NSNumber`、`NSTimer`、`NSThread`、`NSBundle`、`NSNotificationCenter`、`NSKeyedUnarchiver`，以及跨平台的 `YYColor`（iOS 上映射为 `UIColor`，macOS 上映射为 `NSColor`）
- **UIKit/** — 对以下 UIKit 类的 Category 扩展：`UIView`、`UIImage`、`UIControl`、`UIScrollView`、`UITableView`、`UITextField`、`UIScreen`、`UIDevice`、`UIApplication`、`UIFont`、`UIBarButtonItem`、`UIGestureRecognizer`、`UIBezierPath`
- **Quartz/** — `CALayer+YYAdd` Category 和 `YYCGUtilities`（CGGeometry 辅助工具）

### 关键文件

- `YYCategories/YYCategories.h` — umbrella header，统一导入所有头文件；通过 `TARGET_OS_IPHONE` 宏在 iOS 平台上条件引入 UIKit/Quartz 部分
- `YYCategories/YYCategoriesMacro.h` — 整个库共用的宏定义：
  - `weakify`/`strongify` — block 中防止循环引用的弱引用/强引用模式
  - `YYSYNTH_DUMMY_CLASS` — 在静态库中强制加载 Category，无需使用 `-all_load` 或 `-force_load`
  - `YYSYNTH_DYNAMIC_PROPERTY_OBJECT` / `YYSYNTH_DYNAMIC_PROPERTY_CTYPE` — 在 Category 中为已存在的类添加关联对象（associated object）属性
  - Dispatch 辅助函数（`dispatch_async_on_main_queue`、`dispatch_sync_on_main_queue`）
  - `YYBenchmark` — 代码块性能计时
- `YYCategories/include/` — 所有公开头文件的符号链接，用于 SPM 的 `publicHeadersPath`

### 特殊编译说明

- `NSObject+YYAddForARC.m` 和 `NSThread+YYAdd.m` 需要 `-fno-objc-arc` 编译标志（这两个文件使用手动内存管理）。CocoaPods 通过 `no-arc` subspec 处理此问题；SPM 则直接从编译中排除这两个文件。
- `YYColor+YYAdd` 使用 `YYColor` 宏实现跨平台颜色支持（iOS/tvOS 为 `UIColor`，macOS 为 `NSColor`）。
- `UIBarButtonItem+YYAdd` 在 tvOS 上不可用（`UIBarButtonItem` 在 tvOS SDK 中不存在），源码已通过 `#if !TARGET_OS_TV` 排除。SPM 中此文件在所有平台编译但内容为空；CocoaPods 中通过 `s.tvos.exclude_files` 排除。

### 多平台支持

该库同时支持 iOS、macOS 和 tvOS：
- Foundation 部分的 Category 在所有平台上均可用
- UIKit 和 Quartz 部分在 iOS 和 tvOS 上可用（由 `TARGET_OS_IPHONE` 宏保护），macOS 上不可用
- `YYColor` 宏根据平台自动映射为 `UIColor`（iOS/tvOS）或 `NSColor`（macOS）
- `UIBarButtonItem+YYAdd` 仅在 iOS 上可用，tvOS 上已排除
- `include/` 目录及其符号链接是专门为 SPM 兼容性创建的
