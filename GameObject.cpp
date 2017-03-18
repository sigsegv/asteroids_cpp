#include "GameObject.hpp"
#include <algorithm>
#include <cassert>
#include "Game.hpp"

GameObject::GameObject() :
	mParent(nullptr)
{
}

GameObject::~GameObject()
{
	if (kinematicBody.get())
	{
		Game::instance->kinematicSystem.removeBody(*kinematicBody);
	}
}

void GameObject::attachNode(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

GameObject::Ptr GameObject::detachNode(const GameObject & child)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](const Ptr& p)->bool { return p.get() == &child; });
	assert(found != mChildren.end());
	Ptr result = std::move(*found);
	mChildren.erase(found);
	result->mParent = nullptr;
	return result;
}

void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	drawCurrent(target, states);
	for (const Ptr& child : mChildren)
	{
		child->draw(target, states);
	}
}

void GameObject::drawCurrent(sf::RenderTarget &, sf::RenderStates) const
{
}

void GameObject::update(float elpasedSeconds)
{
	updateCurrent(elpasedSeconds);
	for (const Ptr& child : mChildren)
	{
		child->update(elpasedSeconds);
	}
}

void GameObject::onCollision(GameObject & /*other*/)
{
}

void GameObject::updateCurrent(float /*elapsedSeconds*/)
{
}
