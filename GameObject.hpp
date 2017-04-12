#pragma once

#include <memory>
#include <list>
#include "Scab.hpp"
#include "KinematicBody.hpp"
#include "CircleCollider.hpp"

/**
	* Object in SceneGraph
	*/
class GameObject : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
{
public:
	using Ptr = std::unique_ptr<GameObject>;

	GameObject();
	virtual ~GameObject();

	void attachNode(Ptr child);
	Ptr detachNode(const GameObject& child);
	void update(float elapsedSeconds);
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	float getWorldRotation() const;
	bool isMarkedForRemoval() const;
	void markForRemoval();
	void cleanup();

	virtual void onCollision(const Collision& collision);

	KinematicBody::Ptr kinematicBody;
	CircleCollider::Ptr collider;
protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	virtual void updateCurrent(float elapsedSeconds);

	GameObject* mParent;
	bool mMarkedForRemoval;
	std::list<Ptr> mChildren;
private:
};
