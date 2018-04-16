#pragma once
#include <deque>
#include "Aspect.h"
#include "EntityManager.h"
#include "SubscriptionManager.h"
#include <json.hpp>
/*
** A Wrapper for an entity ID
** Lightweight so its ok to pass it around
** Adds convinient way to access components.
*/

namespace ECS {

	class Entity
	{
	public:

		Entity();
		Entity(int id);

		static Entity create();
		static Entity create(nlohmann::json);
		static void destroy(Entity e);

		template<class T>
		T& get() const;

		template<class T>
		void add(T&& component);

		template<class T, class... Args>
		void emplace(Args&& ... args);

		template<class T>
		void remove();

		template<class T>
		bool has() const;

		bool has(Aspect compare) const;

		void clear();

		Aspect& getAspect();

		const Aspect& getAspect() const;

		bool operator==(const Entity& rhs) const;

		int getId() const
		{
			return id;
		}

		static EntityManager entityManager;
	private:
		int id;

	};

	Entity operator"" _entity(const char* s, std::size_t n);


	template<class T>
	T& Entity::get() const
	{
		return T::componentMapper.get(id);
	}

	template<class T>
	void Entity::add(T && component)
	{
		T::componentMapper.put(id, component);
		getAspect().set<T>();
		SubscriptionManager::bitTouched(id, T::componentId);
	}

	template<class T, class ...Args>
	void Entity::emplace(Args && ... args)
	{
		T::componentMapper.emplace(id, std::forward<Args>(args)...);
		getAspect().set<T>();
		SubscriptionManager::bitTouched(id, T::componentId);
	}

	template<class T>
	inline void Entity::remove()
	{
		T::componentMapper.erase(id);
		getAspect().unset<T>();
		SubscriptionManager::bitTouched(id, T::componentId);
	}

	template<class T>
	bool Entity::has() const
	{
		return getAspect().has<T>();
	}

}