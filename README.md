# Opengl

注意：由于之前的代码是在边学习边写的情况下完成的，导致在后续实现其他效果的时候没法做到很方便的扩展，所以在develop分支上重新进行了整理，目前还能够比较正常的开发。现在的develop分支已经重新实现了多种阴影效果，正在进行ao和RSM的开发。推荐切换到develop分支。代码中使用了glog，assimp还有glew等库，编译时需要确保本地的环境正确，详细情况可以看cmakelist


主要使用opengl和c++完成了的一些demo，PBR分支实现了IBL下的PBR效果，实现方法看scene.cc即可。shadow分支实现硬阴影、PCL、PCSS，用来对比阴影效果，rayTracing分支用来实现实时光追。

#PBR效果
按K键可以开启泛光
![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.59.56.png)

#阴影效果对比

使用分支shadow,快捷键是B->hard shadow, N->PCL, M->PCSS

![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.32.20.png)

![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.32.29.png)

![image](https://github.com/wowanttoplay/Opengl/blob/master/README.assets/%E6%88%AA%E5%B1%8F2021-10-10%20%E4%B8%8A%E5%8D%8812.32.38.png)

# 实时光追

