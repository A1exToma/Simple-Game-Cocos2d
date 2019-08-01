#include"Updater.h"
#include"Updatable.h"

void Updater::RegisterUpdatable(Updatable* updatable)
{
	toUpdate.insert(updatable);
}

void Updater::UnregisterUpdatable(Updatable* updatable)
{
	toUpdate.erase(updatable);
}

void Updater::UpdateAll(float delta)
{
	for (auto updateable : toUpdate)
		updateable->Update(delta);
}