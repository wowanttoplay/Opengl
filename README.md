# Opengl
主要使用opengl和c++完成了的一些demo，PBR分支实现了IBL下的PBR效果，实现方法看scene.cc即可。shadow分支实现硬阴影、PCL、PCSS，用来对比阴影效果，rayTracing分支用来实现实时光追。

#PBR效果
按K键可以开启泛光
![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.59.56.png)

#阴影效果对比

使用分支shadow,快捷键是B->hard shadow, N->PCL, M->PCSS（采样方法后续修改，现在是一个均匀采样）

![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.32.20.png)

![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.32.29.png)

![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.32.38.png)

# 全局光照
## RSM（Reflective shadow map）
利用shadowMap来实现第二次的光线反射，之所以和shadow map有关，是因为shadow map记录的实际上就是被光直接照射的pixel，这些就是次级光源

# 实时光追

