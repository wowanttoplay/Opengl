# Opengl
主要使用opengl和c++完成了的一些demo，PBR分支实现了IBL下的PBR效果，实现方法看scene.cc即可。shadow分支实现硬阴影、PCL、PCSS，用来对比阴影效果，rayTracing分支用来实现实时光追。
之所以分为多个分支，而不是一个里面多个开关，，是因为这个项目是为了自己实验一些效果，目前不想花太多时间在易用等方面。光追完成后，会重新写一遍，目前的代码太集中，没有好好规划

#PBR效果



#阴影效果对比

使用分支shadow,快捷键是B->hard shadow, N->PCL, M->PCSS

<img src="/Users/virgil/Opengl/README.assets/截屏2021-10-10 上午12.32.20.png" alt="截屏2021-10-10 上午12.32.20" style="zoom:50%;" />

<img src="/Users/virgil/Opengl/README.assets/截屏2021-10-10 上午12.32.29.png" alt="截屏2021-10-10 上午12.32.29" style="zoom:50%;" />

<img src="/Users/virgil/Opengl/README.assets/截屏2021-10-10 上午12.32.38.png" alt="截屏2021-10-10 上午12.32.38" style="zoom:50%;" />

# 实时光追

