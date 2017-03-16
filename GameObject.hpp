#pragma once

#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "KinematicBody.hpp"

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

	virtual void update(float elapsedSeconds);

	KinematicBody::Ptr kinematicBody;
protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
	void updateCurrent(float elapsedSeconds);
private:
	GameObject* mParent;
	std::vector<Ptr> mChildren;
};
