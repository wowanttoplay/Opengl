<!--
 * @Author: your name
 * @Date: 2022-01-03 18:06:35
 * @LastEditTime: 2022-01-05 01:30:12
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /shader/Users/virgil/Opengl/README.md
-->

# Opengl

摘要：本仓库中存在多个分支，各个分支含义如下：

- develop:目前的主线，其余分支因为架构问题，已经抛弃，目前在 develop 继续开发。该分支目前规范了 log、debug 的工具类，还能够继续开发一些效果。但目前在 develop 上也发现做延迟渲染的时候不太舒适，material、geometry 这些概念还在耦合，还需要加 gtest 来保证代码质量。[后续还是需要再重构一次，推荐看一下 three.js，目前觉得这个库不错]

- master:最初期的代码，基于 blinnPhong 着色模型实现的渲染，做了一些反射、折射的效果[后续已经不会再修改，将来删除]
- PBR:该分支内主要是基于 PBR 着色模型来渲染，实现了 IBL 和一些泛光等效果[内部的代码还没迁移到 develop 中，暂时不会删除]
- shadow:该分支主要实现了一些阴影的效果，但是因为一些情况没考虑，效果不太好[已经废弃，将来删除]

## 一些已经实现的效果

### PBR 效果（开启泛光）

按 K 键可以开启泛光
![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.59.56.png)

### 阴影效果对比(在 develop 分支，没有做开关，需要自己在 shader 内修改)

#### 硬阴影

![PBR](https://github.com/wowanttoplay/Opengl/blob/develop/asset/hardShadow.png)

#### PCF 阴影

![PCF](https://github.com/wowanttoplay/Opengl/blob/develop/asset/PCF.png)

#### PCSS 阴影

![PCSS](https://github.com/wowanttoplay/Opengl/blob/develop/asset/PCSS.png)

#### 带 AO 的阴影（调了参数让 ao 显眼一些，所以显得亮）

![AO](https://github.com/wowanttoplay/Opengl/blob/develop/asset/ao.png)

### 实时光追

## 代码开发(scene 与 camera 耦合了，geometry 和 material 耦合了，渲染耦合在了 object 里，不太好，后续重构)

```
// 创建一个场景、一个相机、一个物体，并将物体放入场景中渲染
auto scene = make_shared<Scene>(width, height, resource_dir); // init scene
auto camera = make_shared<Camera>(scene, glm::vec3(0, 6.0f, 13.0f)); // init camera
scene->setCamera(camera); // set camera

scene->openShadow(true); // 开启阴影
scene->debugShadow(true); // 开启阴影调试，可关闭

scene->openAo(true); // 开启ao效果，开启后会变成延迟渲染
scene->debugAo(true); // 开启ao调试，可关闭

shared_ptr<Plane> ground = std::make_shared<Plane>(scene, glm::vec3(40.0f), glm::vec3(0.0f, -0.002f, 0.0f)); // create a plane object
ground->setColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f)); // set color,这部分将来提取为material
scene->pushObject(ground); // push object
```
