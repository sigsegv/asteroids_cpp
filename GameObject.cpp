#include "GameObject.hpp"
#include <cassert>
#include <algorithm>
#include <functional>
#include "Game.hpp"

GameObject::GameObject() :
	mParent(nullptr),
	mMarkedForRemoval(false)
{
}

GameObject::~GameObject()
{
	if (kinematicBody.get())
	{
		Game::instance->kinematicSystem.removeBody(*kinematicBody);
	}
	if (collider.get())
	{
		Game::instance->collisionSystem.removeCollider(*collider);
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

sf::Transform GameObject::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;
	for (const GameObject* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}
	return transform;
}

sf::Vector2f GameObject::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

float GameObject::getWorldRotation() const
{
	float angle = 0.0;
	for (const GameObject* node = this; node != nullptr; node = node->mParent)
	{
		angle += node->getRotation();
	}
	return angle;
}

bool GameObject::isMarkedForRemoval() const
{
	return mMarkedForRemoval;
}

void GameObject::markForRemoval()
{
	mMarkedForRemoval = true;
}

void GameObject::cleanup()
{
	if (mChildren.empty()) return;
	auto beginCleanup = std::remove_if(mChildren.begin(), mChildren.end(), std::mem_fn(&GameObject::isMarkedForRemoval));
	mChildren.erase(beginCleanup, mChildren.end());
	std::for_each(mChildren.begin(), mChildren.end(), std::mem_fn(&GameObject::cleanup));
}

void GameObject::onCollision(const Collision& /*other*/)
{
}

void GameObject::updateCurrent(float /*elapsedSeconds*/)
{
}
