//
// Created by virgil on 2021/12/4.
//

#pragma once
#include "Shader.h"
#include "RenderObject/BaseObject.h"

class ShaderTool {
public:
    /**
     * 绑定绘制简单颜色的shader
     * @param object ，一些绑定属性的来源对象
     * @return 是否绑定成功
     */
    static bool bindSimpleColorShader(std::shared_ptr<BaseObject> object);

    /**
     * 绑定简单的phong shader
     * @param object ，一些绑定属性的来源对象
     * @return 是否绑定成功
     */
    static bool bindSimplePhong(std::shared_ptr<BaseObject> object);

    /**
     * 绑定带阴影的phong shader
     * @param object ，一些绑定属性的来源对象
     * @return 是否绑定成功
     */
    static bool bindShadowPhong(std::shared_ptr<BaseObject> object);

    /**
     * 绑定只绘制深度贴图的shader
    * @param object ，一些绑定属性的来源对象
     * @return 是否绑定成功
     */
    static bool bindSimpleShadow(std::shared_ptr<BaseObject> object, const glm::mat4& view, const glm::mat4& projection);
};

