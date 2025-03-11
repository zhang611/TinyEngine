#ifndef UNTITLED_GAME_OBJECT_H
#define UNTITLED_GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include <list>
#include <functional>

class Component;

class GameObject {
public:
    GameObject(std::string name);

    ~GameObject();

    std::string &name() { return name_; }

    void set_name(std::string name) { name_ = name; }

    // 添加组件
    Component *AddComponent(std::string component_type_name);

    // 获取组件
    Component *GetComponent(std::string component_type_name);

    // 获取所有同名组件
    std::vector<Component *> &GetComponents(std::string component_type_name);

    // 遍历所有Component
    void ForeachComponent(std::function<void(Component *component)> func);
    // 遍历所有Camera
    static void Foreach(std::function<void(GameObject *game_object)> func);

    unsigned char layer() { return layer_; }
    void set_layer(unsigned char layer) { layer_ = layer; }


private:
    std::string name_;
    std::unordered_map<std::string, std::vector<Component *>> component_type_instance_map_;

    unsigned char layer_;    // 物体分层，用于相机分层、物理碰撞分层等。

    static std::list<GameObject *> game_object_list_;   //存储所有的GameObject。
};


#endif //UNTITLED_GAME_OBJECT_H
