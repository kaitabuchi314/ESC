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