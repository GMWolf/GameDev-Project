#include "stdafx.h"
#include "CppUnitTest.h"
#include <Entity.h>
#include <ComponentMapper.h>
#include <Component.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ECSTest
{		

	struct component1 : public Component<component1, 16> {

		component1(int x, int y) : x(x), y(y) {
		}

		bool operator==(const component1& rhs) const {
			return ((x == rhs.x) && (y == rhs.y));
		}

		int x = -5;
		int y = -25;
	};

	COMPONENT(component2, 16) {

		component2(int foo, int bar) : foo(foo), bar(bar) {
		}

		int foo = -10;
		int bar = -25;
	};

	COMPONENT(component3, 16) {
		int huhu;
		float whaa;
	};

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
		}

		TEST_METHOD(put_and_retreive_components) {
			Entity e = Entity::Create();
			e.add(component1(1, 2));

			component1 c = e.get<component1>();
			Logger::WriteMessage(std::string("c.x " + std::to_string(c.x)).c_str());
			Logger::WriteMessage(std::string("c.y " + std::to_string(c.y)).c_str());

			Assert::AreEqual(1, c.x);
			Assert::AreEqual(2, c.y);

			Entity::Destroy(e);
		}

		TEST_METHOD(Entity_Unique_Component) {
			Entity a = Entity::Create();
			Entity b = Entity::Create();

			a.add(component1(1, 2));
			b.add(component1(4, 5));

			Assert::AreNotEqual(a.get<component1>().x, b.get<component1>().x);
			Assert::AreNotEqual(a.get<component1>().y, b.get<component1>().y);

			Entity::Destroy(a);
			Entity::Destroy(b);
		}

		TEST_METHOD(Component_have_unique_store) {
			Entity a = Entity::Create();

			a.add(component1(10, 11));
			a.add(component2(6, 89));
			
			Assert::AreEqual(10, a.get<component1>().x);
			Assert::AreEqual(89, a.get<component2>().bar);

			Entity::Destroy(a);
		}

		TEST_METHOD(modify_component) {
			Entity e = Entity::Create();

			e.add(component1(100, 5));

			e.get<component1>().x = 42;

			Assert::AreEqual(42, e.get<component1>().x);
		}

		TEST_METHOD(aspect_building) {
			Aspect aspect = Aspect::getAspect<component1, component3>();

			Assert::IsTrue(aspect.has<component1>());
			Assert::IsTrue(aspect.has<component3>());
			Assert::IsFalse(aspect.has<component2>());
		}
		

	};
}