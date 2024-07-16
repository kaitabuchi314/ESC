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

    class system;

    template<typename T>
    class manager {
    public:
        explicit manager(system& sys) : sys(sys) {
        }

        void addComponent(Entity entity, T component) {
            components.push_back(component);
        }

        std::vector<T>& getComponents() {
            return components;
        }

        // Copy constructor
        manager(const manager& other, system& sys) : sys(sys), components(other.components) {
        }

    private:
        system& sys;
        std::vector<T> components;
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
        void registerManager(manager<T>* mgr) {
            managers[typeid(T)] = mgr;
        }

        template<typename T>
        std::vector<T> get() {
            if (managers.find(typeid(T)) != managers.end()) {
                auto mgr = static_cast<manager<T>*>(managers[typeid(T)]);
                return mgr->getComponents();
            }
            return {};
        }

        // Copy constructor
        system(const system& other) : nextEntityId(other.nextEntityId), entities(other.entities) {
            for (const auto& pair : other.managers) {
                copyManager(pair.first, pair.second);
            }
        }

        // Copy assignment operator
        system& operator=(const system& other) {
            if (this == &other) {
                return *this;
            }

            nextEntityId = other.nextEntityId;
            entities = other.entities;
            managers.clear();

            for (const auto& pair : other.managers) {
                copyManager(pair.first, pair.second);
            }

            return *this;
        }

    private:
        int nextEntityId;
        std::vector<Entity> entities;
        std::unordered_map<std::type_index, void*> managers;

        void copyManager(const std::type_index& type, void* mgr) {
            if (type == typeid(FruitComponent)) {
                auto originalMgr = static_cast<manager<FruitComponent>*>(mgr);
                auto newMgr = new manager<FruitComponent>(*originalMgr, *this);
                managers[type] = newMgr;
            }
            else if (type == typeid(PizzaComponent)) {
                auto originalMgr = static_cast<manager<PizzaComponent>*>(mgr);
                auto newMgr = new manager<PizzaComponent>(*originalMgr, *this);
                managers[type] = newMgr;
            }
            // Add more else if blocks here for other component types as needed
        }
    };

}