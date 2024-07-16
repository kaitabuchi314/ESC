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

	sys.registerManager<FruitComponent>(&fruitManager);
	sys.registerManager<PizzaComponent>(&pizzaManager);

	esc::Entity entity = sys.createEntity();

	fruitManager.add(entity, FruitComponent { 8, 9.5f });
	pizzaManager.add(entity, PizzaComponent { 15, true });

	update(&sys);

	return 0;
}