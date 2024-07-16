#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include <memory>

namespace esc {

    class Entity {
    public:
        int id;
        explicit Entity(int id) : id(id) {}
    };

    class system {
    public:
        system() : nextEntityId(0) {}

        Entity createEntity() {
            Entity entity(nextEntityId++);
            entities.push_back(entity);
            return entity;
        }

        template<typename T>
        std::vector<T> get() {
            std::vector<T> components;
            for (auto& component : componentsMap[typeid(T)]) {
                components.push_back(*static_cast<T*>(component.get()));
            }
            return components;
        }

        template<typename T>
        void add(Entity entity, T component) {
            if (componentsMap.find(typeid(T)) == componentsMap.end()) {
                componentsMap[typeid(T)] = std::vector<std::shared_ptr<void>>();
            }
            componentsMap[typeid(T)].push_back(std::make_shared<T>(component));
        }

    private:
        int nextEntityId;
        std::vector<Entity> entities;
        std::unordered_map<std::type_index, std::vector<std::shared_ptr<void>>> componentsMap;
    };

    template<typename T>
    class manager {
    public:
        explicit manager(system& sys) : sys(sys) {}

        void addComponent(Entity entity, T component) {
            sys.addComponent(entity, component);
        }

    private:
        system& sys;
    };

}