#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
    virtual ~Component() = default;
    virtual void Update() = 0; // To be overridden in each derived component
};

#endif // COMPONENT_H