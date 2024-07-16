# ESC - The Easy, Simple, and Clean header only ECS library.
ESC is a simple and clean header only C++ library used to deal with ECS. I made this because of the lack of easy, simple and clean ECS systems. Entt/others were very verbose and complex. 

## A walkthrough of the demo.
The demo consists of one file, main.cpp. These are the contents of this file:
```
#include <string>
#include <iostream>
#include <vector>

#include <esc.h>

struct FruitComponent
{
	float yummyness;
	float sweetness;
};

struct PizzaComponent
{
	int pepperoniCount;
	bool stuffedCrust;
};

void update(esc::system* sys)
{
	std::vector<FruitComponent> fruits = sys->get<FruitComponent>();
	std::vector<PizzaComponent> pizzas = sys->get<PizzaComponent>();
	
	for (FruitComponent c : fruits)
	{
		std::cout << c.yummyness << " " << c.sweetness << std::endl;
	}

	for (PizzaComponent c : pizzas)
	{
		std::cout << c.pepperoniCount << " " << c.stuffedCrust << std::endl;
	}
}

int main()
{
	esc::system sys = esc::system();

	esc::manager<FruitComponent> fruitManager = esc::manager<FruitComponent>(sys);
	esc::manager<PizzaComponent> pizzaManager = esc::manager<PizzaComponent>(sys);

	esc::Entity entity = sys.createEntity();

	sys.add(entity, FruitComponent { 8, 9.5f });
	sys.add(entity, PizzaComponent { 15, true });

	update(&sys);

	return 0;
}
```
  The `esc::system` class is the actual ECS core. The main functions are `sys.add(entity, component)`, `sys.get<ComponentType>()`, and `sys.createEntity()`.
The Add function adds a component to an entity. The get function gets a vector of the components of a specified type.
The `esc::manager` class manages a specific component. Each component has it's own manager.
