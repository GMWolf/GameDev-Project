#include "stdafx.h"
#include "CppUnitTest.h"
#include <Entity.h>
#include <ComponentMapper.h>
#include <Component.h>
#include <sstream>
#include <iterator>
#include "../json/json.hpp"
#include "Event.h"
#include "EntityEvents.h"
#include "ECS.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace ECS;
COMPONENT(component1, 16, 0) {
	component1()
	{
	};

	component1(int x, int y) : x(x), y(y) {
	}

	bool operator==(const component1& rhs) const {
		return ((x == rhs.x) && (y == rhs.y));
	}

	int x = -5;
	int y = -25;

	void load(const nlohmann::json& j)
	{
		x = j.at("x").get<int>();
		y = j.at("y").get<int>();
	}
};



COMPONENT(component2, 16, 1) {
	component2() {
	};
	component2(int foo, int bar) : foo(foo), bar(bar) {
	}

	int foo = -10;
	int bar = -25;

	void load(const nlohmann::json& j)
	{
		foo = j.at("foo").get<int>();
		bar = j.at("bar").get<int>();
	}
};



COMPONENT(component3, 16, 2) {
	component3() {};
	int huhu;
	float whaa;

	void load(const nlohmann::json& j)
	{
		huhu = j.at("huhu").get<int>();
		whaa = j.at("whaa").get<float>();
	}
};

namespace ECSTest
{		

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(unique_Component_IDs)
		{

			

			int c1id = component1::componentId;
			int c2id = component2::componentId;
			int c3id = component3::componentId;
			Logger::WriteMessage(std::string("comp 1 id: " + std::to_string(c1id)).c_str());
			Logger::WriteMessage(std::string("comp 2 id: " + std::to_string(c2id)).c_str());
			Logger::WriteMessage(std::string("comp 3 id: " + std::to_string(c3id)).c_str());
			Assert::AreNotEqual(c1id, c2id);
			Assert::AreNotEqual(c1id, c3id);
			Assert::AreNotEqual(c2id, c3id);

			std::ostringstream oss;
			oss << baseComponentMapper::mappers()->size() << " ";
			for (int i = 0; i < baseComponentMapper::mappers()->size(); i++) {
				oss << baseComponentMapper::mappers()->at(i) << " ";
			}
			oss << &component1::componentMapper << " " << &component2::componentMapper << " " << &component3::componentMapper;

			Logger::WriteMessage(oss.str().c_str());
		}

		TEST_METHOD(put_and_retreive_components) {
			Entity e = Entity::create();
			e.add(component1(1, 2));

			component1 c = e.get<component1>();
			Logger::WriteMessage(std::string("c.x " + std::to_string(c.x)).c_str());
			Logger::WriteMessage(std::string("c.y " + std::to_string(c.y)).c_str());

			Assert::AreEqual(1, c.x);
			Assert::AreEqual(2, c.y);

			Entity::destroy(e);
		}

		TEST_METHOD(Entity_Unique_Component) {
			Entity a = Entity::create();
			Entity b = Entity::create();

			a.add(component1(1, 2));
			b.add(component1(4, 5));

			Assert::AreNotEqual(a.get<component1>().x, b.get<component1>().x);
			Assert::AreNotEqual(a.get<component1>().y, b.get<component1>().y);

			Entity::destroy(a);
			Entity::destroy(b);
		}

		TEST_METHOD(Component_have_unique_store) {
			Entity a = Entity::create();

			a.add(component1(10, 11));
			a.add(component2(6, 89));
			
			Assert::AreEqual(10, a.get<component1>().x);
			Assert::AreEqual(89, a.get<component2>().bar);

			Entity::destroy(a);
		}

		TEST_METHOD(modify_component) {
			Entity e = Entity::create();

			e.add(component1(100, 5));

			e.get<component1>().x = 42;

			Assert::AreEqual(42, e.get<component1>().x);

			Entity::destroy(e);
		}

		TEST_METHOD(aspect_building) {
			Aspect aspect = Aspect::getAspect<component1, component3>();

			Assert::IsTrue(aspect.has<component1>());
			Assert::IsTrue(aspect.has<component3>());
			Assert::IsFalse(aspect.has<component2>());
		}

		TEST_METHOD(Entity_match_aspect) {
			Aspect aspect = Aspect::getAspect<component2, component3>();

			Entity e1 = Entity::create();

			Assert::IsFalse(e1.has(aspect));
			e1.add(component2(1, 1));
			Assert::IsFalse(e1.has(aspect));
			e1.add(component3());
			Assert::IsTrue(e1.has(aspect));
			e1.add(component1(1,1));
			Assert::IsTrue(e1.has(aspect));

			Entity::destroy(e1);
		}

		TEST_METHOD(entity_subscription) {
			Aspect aspect = Aspect::getAspect<component1, component3>();

			EntitySubscription& sub = SubscriptionManager::getSubscription(aspect);

			Entity e1 = Entity::create();
			Entity e2 = Entity::create();

			std::ostringstream oss;

			oss << sub.entities.size();
			Logger::WriteMessage(oss.str().c_str());
			
			Assert::IsTrue(sub.entities.empty());

			e1.add(component1(0, 0));
			SubscriptionManager::update();

			Assert::IsTrue(sub.entities.empty());
			
			e1.add(component3());
			SubscriptionManager::update();
			
			Logger::WriteMessage("ok");
			Logger::WriteMessage(std::to_string(sub.entities.size()).c_str());

			Assert::IsTrue(std::vector<int>{e1.getId()} == sub.entities);

			e1.add(component2(1,1));
			SubscriptionManager::update();
			Assert::IsTrue(std::vector<int>{e1.getId()} == sub.entities);

			e2.add(component1(0, 0));
			e2.add(component3());
			SubscriptionManager::update();

			Assert::IsTrue(std::vector<int>{e1.getId(), e2.getId()} == sub.entities);

			e1.remove<component1>();
			SubscriptionManager::update();

			Assert::IsTrue(std::vector<int>{e2.getId()} ==  sub.entities);
			Assert::IsFalse(sub.entities.empty());


			Entity::destroy(e1);
			Entity::destroy(e2);

			SubscriptionManager::update();
			Entity::entityManager.update();

			Assert::IsTrue(sub.entities.empty());
		}

		TEST_METHOD(multiple_subscriptions) {
			EntitySubscription& sub12 = SubscriptionManager::getSubscription(Aspect::getAspect<component1, component2>());
			EntitySubscription& sub2 = SubscriptionManager::getSubscription(Aspect::getAspect<component2>());

			int i = 0;
			for (std::vector<EntitySubscription*>& subs : SubscriptionManager::bitSubscriptions) {
				Logger::WriteMessage(("bit " + std::to_string(i++)).c_str());
				for (EntitySubscription* sub : subs) {
					std::ostringstream oss;
					oss << sub;
					Logger::WriteMessage(oss.str().c_str());
				}
			}

			Logger::WriteMessage(std::to_string(sub12.entities.size()).c_str());
			Assert::IsTrue(sub12.entities.empty());
			Assert::IsTrue(sub2.entities.empty());

			Entity e1 = Entity::create();
			Entity e2 = Entity::create();

			e1.add(component2(0,0));
			SubscriptionManager::update();
			Assert::IsTrue(sub12.entities.empty());
			std::ostringstream oss1;

			oss1 << "foo:";
			for(auto e : sub2.entities)
			{
				oss1 << e << " , ";
			}
			Logger::WriteMessage(oss1.str().c_str());
			Assert::IsTrue(sub2.entities == std::vector<int>{e1.getId()});

		}

		TEST_METHOD(ecs_names)
		{
			Assert::IsTrue("component1" == component1::componentName);
			Assert::IsTrue("component2" == component2::componentName);
			Assert::IsTrue("component3" == component3::componentName);
		}


		class component1Loader : public ComponentLoader {
		public:
			void load(nlohmann::json& j, void* c) override {
				component1* c1 = static_cast<component1*>(c);
				c1->x = j.at("x").get<int>();
				c1->y = j.at("y").get<int>();
			}
		};

		class component2Loader : public component1Loader {
		public:
			void load(nlohmann::json& j, void* c) override {
				component2* c2 = static_cast<component2*>(c);
				c2->foo = j.at("foo").get<int>();
				c2->bar = j.at("bar").get<int>();
			}
		};

		TEST_METHOD(ecs_json)
		{

			ECS::registerLoader<component1>(new component1Loader);
			ECS::registerLoader<component2>(new component2Loader);
			Entity e = R"(
				{
					"component1" : {
						"x" : 6,
						"y" : 409
					},
					"component2" : {
						"foo" : -34,
						"bar" : 88
					}
				}
			)"_entity;


			Assert::IsTrue(e.has(Aspect::getAspect<component1>()));
			Assert::IsTrue(e.has(Aspect::getAspect<component2>()));
			Assert::IsTrue(e.get<component1>().x == 6);
			Assert::IsTrue(e.get<component1>().y == 409);
			Assert::IsTrue(e.get<component2>().foo == -34);
			Assert::IsTrue(e.get<component2>().bar == 88);

			Entity::destroy(e);
		}

		EVENT(event1)
		{
			event1(int x, int y) : x(x), y(y)
			{
			};
			int x;
			int y;
		};

		TEST_METHOD(events)
		{
			EventQueue<event1> queue;

			Assert::IsTrue(queue.events.empty());

			event1::Emit(1, 2);

			Assert::IsTrue(queue.events.size() == 1);
			Assert::IsTrue(queue.events.back().x = 1);
			Assert::IsTrue(queue.events.back().y = 2);

			event1::Emit(4, 6);
			Assert::IsTrue(queue.events.size() == 2);
			Assert::IsTrue(queue.events.front().x = 1);
			Assert::IsTrue(queue.events.front().y = 2);
			queue.events.pop();
			Assert::IsTrue(queue.events.size() == 1);
			Assert::IsTrue(queue.events.front().x = 4);
			Assert::IsTrue(queue.events.front().y = 5);
		}

		TEST_METHOD(entity_events)
		{
			EventQueue<EntityInserted<component1, component3>> inqueue;
			EventQueue<EntityRemoved<component1, component3>> outqueue;
			
			Logger::WriteMessage(std::to_string(inqueue.events.size()).c_str());
			Assert::IsTrue(inqueue.events.empty());

			Entity e = Entity::create();
			e.add(component1(1, 2));
			
			SubscriptionManager::update();
			Assert::IsTrue(inqueue.events.empty());

			e.add(component3());
			SubscriptionManager::update();
			
			Assert::IsTrue(inqueue.events.size() == 1);
			
			e.add(component2(3, 1));
			SubscriptionManager::update();
			Assert::IsTrue(inqueue.events.size() == 1);
		
			Assert::IsTrue(outqueue.events.empty());
			
			e.remove<component3>();
			SubscriptionManager::update();
			Assert::IsTrue(outqueue.events.size() == 1);
			e.remove<component1>();
			Assert::IsTrue(outqueue.events.size() == 1);

			Entity::destroy(e);
		}
		

	};
}