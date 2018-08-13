#include <array>

#include <tut/tut.hpp>
#include <tut/tut_macros.hpp>

#include "ShareablePoints/ShareableExtraInfos.hpp"
#include "ShareablePoints/ShareableFrame.hpp"
#include "ShareablePoints/ShareableParams.hpp"
#include "ShareablePoints/ShareablePoint.hpp"
#include "ShareablePoints/ShareablePointsList.hpp"
#include "ShareablePoints/ShareablePosition.hpp"

#include "TCoordSysFactory.h"

namespace tut
{
	struct shareablepointsdata {};

	typedef test_group<shareablepointsdata> tg;
	tg plugins_shpoints_test_group("Test ShareablePoints package.");
	typedef tg::object testobject;
}

namespace tut
{
	/* ************************************************** *
	 *           TESTS OF SHAREABLEPOSITION               *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<1>()
	{
		set_test_name("ShareablePosition: Test of constructors");

		const ShareablePosition p1{}, p2 = { 0, 1, 2, 10, 11, 12, true, false, true };
		ensure_equals(p1.x, 0);
		ensure_equals(p1.y, 0);
		ensure_equals(p1.z, 0);
		ensure_equals(p1.sigmax, 0);
		ensure_equals(p1.sigmay, 0);
		ensure_equals(p1.sigmaz, 0);
		ensure_not(p1.isfreex);
		ensure_not(p1.isfreey);
		ensure_not(p1.isfreez);

		ensure_equals(p2.x, 0);
		ensure_equals(p2.y, 1);
		ensure_equals(p2.z, 2);
		ensure_equals(p2.sigmax, 10);
		ensure_equals(p2.sigmay, 11);
		ensure_equals(p2.sigmaz, 12);
		ensure(p2.isfreex);
		ensure_not(p2.isfreey);
		ensure(p2.isfreez);
	}

	template<>
	template<>
	void testobject::test<2>()
	{
		set_test_name("ShareablePosition: Test of comparison operators");

		const ShareablePosition p = { 0, 1, 2, 10, 11, 12, true, false, true };
		ShareablePosition test = p;
		ensure(p == test);
		ensure_not(p != test);
		test.z++;
		ensure_not(test == p);
		ensure(test != p);
	}
	
	template<>
	template<>
	void testobject::test<3>()
	{
		set_test_name("ShareablePosition: Test of operators");

		// unary operator-
		{
			const ShareablePosition p = { 0, 1, 2, 10, 11, 12, true, false, true };
			const ShareablePosition p2 = -p;
			ensure_equals(p2.x, 0);
			ensure_equals(p2.y, -1);
			ensure_equals(p2.z, -2);
			ensure_equals(p2.sigmax, 10);
			ensure_equals(p2.sigmay, 11);
			ensure_equals(p2.sigmaz, 12);
			ensure(p2.isfreex);
			ensure_not(p2.isfreey);
			ensure(p2.isfreez);
		}
		// operator+
		{
			const ShareablePosition p = { 0, 1, 2, 3, 3, 3, true, false, true };
			const ShareablePosition p2 = p + ShareablePosition{ 100, 101, 102, 4, 4, 4 };
			ensure_equals(p2.x, 100);
			ensure_equals(p2.y, 102);
			ensure_equals(p2.z, 104);
			ensure_equals(p2.sigmax, 5);
			ensure_equals(p2.sigmay, 5);
			ensure_equals(p2.sigmaz, 5);
			ensure(p2.isfreex);
			ensure_not(p2.isfreey);
			ensure(p2.isfreez);
		}
		// operator-
		{
			const ShareablePosition p = { 0, 1, 2, 4, 4, 4, true, false, true };
			const ShareablePosition p2 = p - ShareablePosition{ 100, 101, 102, 3, 3, 3 };
			ensure_equals(p2.x, -100);
			ensure_equals(p2.y, -100);
			ensure_equals(p2.z, -100);
			ensure_equals(p2.sigmax, 5);
			ensure_equals(p2.sigmay, 5);
			ensure_equals(p2.sigmaz, 5);
			ensure(p2.isfreex);
			ensure_not(p2.isfreey);
			ensure(p2.isfreez);
		}
		// operator*
		{
			const ShareablePosition p = { 0, 1, 2, 4, 4, 4, true, false, true };
			const ShareablePosition p2 = p * 4;
			ensure(p2 == (4 * p));
			ensure_equals(p2.x, 0);
			ensure_equals(p2.y, 4);
			ensure_equals(p2.z, 8);
			ensure_equals(p2.sigmax, 4);
			ensure_equals(p2.sigmay, 4);
			ensure_equals(p2.sigmaz, 4);
			ensure(p2.isfreex);
			ensure_not(p2.isfreey);
			ensure(p2.isfreez);
		}
		// operator/
		{
			const ShareablePosition p = { 0, 1, 2, 4, 4, 4, true, false, true };
			const ShareablePosition p2 = p / -2;
			ensure_equals(p2.x, 0);
			ensure_equals(p2.y, -0.5);
			ensure_equals(p2.z, -1);
			ensure_equals(p2.sigmax, 4);
			ensure_equals(p2.sigmay, 4);
			ensure_equals(p2.sigmaz, 4);
			ensure(p2.isfreex);
			ensure_not(p2.isfreey);
			ensure(p2.isfreez);
		}
		// operator+=
		{
			ShareablePosition p = { 0, 1, 2, 3, 4, 3, true, false, true };
			p += ShareablePosition{ 12, 11, 10, 4, 3, 4 };
			ensure_equals(p.x, 12);
			ensure_equals(p.y, 12);
			ensure_equals(p.z, 12);
			ensure_equals(p.sigmax, 5);
			ensure_equals(p.sigmay, 5);
			ensure_equals(p.sigmaz, 5);
			ensure(p.isfreex);
			ensure_not(p.isfreey);
			ensure(p.isfreez);
		}
		// operator-=
		{
			ShareablePosition p = { 0, 1, 2, 4, 3, 4, true, false, true };
			p -= ShareablePosition{ 12, 11, 10, 3, 4, 3 };
			ensure_equals(p.x, -12);
			ensure_equals(p.y, -10);
			ensure_equals(p.z, -8);
			ensure_equals(p.sigmax, 5);
			ensure_equals(p.sigmay, 5);
			ensure_equals(p.sigmaz, 5);
			ensure(p.isfreex);
			ensure_not(p.isfreey);
			ensure(p.isfreez);
		}
		// operator*=
		{
			ShareablePosition p = { 0, 1, 2, 4, 4, 4, true, false, true };
			p *= 4;
			ensure_equals(p.x, 0);
			ensure_equals(p.y, 4);
			ensure_equals(p.z, 8);
			ensure_equals(p.sigmax, 4);
			ensure_equals(p.sigmay, 4);
			ensure_equals(p.sigmaz, 4);
			ensure(p.isfreex);
			ensure_not(p.isfreey);
			ensure(p.isfreez);
		}
		// operator/=
		{
			ShareablePosition p = { 0, 1, 2, 4, 4, 4, true, false, true };
			p /= -2;
			ensure_equals(p.x, 0);
			ensure_equals(p.y, -0.5);
			ensure_equals(p.z, -1);
			ensure_equals(p.sigmax, 4);
			ensure_equals(p.sigmay, 4);
			ensure_equals(p.sigmaz, 4);
			ensure(p.isfreex);
			ensure_not(p.isfreey);
			ensure(p.isfreez);
		}
	}

	template<>
	template<>
	void testobject::test<4>()
	{
		set_test_name("ShareablePosition: Test of constexpr");

		// constructor
		{
			constexpr ShareablePosition p = { 1, -2, 3 };
			std::array<int, static_cast<size_t>(p.x)> arr; // if not constexpr, doesn't compile
			ensure_equals(arr.size(), 1);
		}
		// unary operator-
		{
			constexpr ShareablePosition p = { 1, -2, 3 };
			std::array<int, static_cast<size_t>((-p).y)> arr; // if not constexpr, doesn't compile
			ensure_equals(arr.size(), 2);
		}
		// operator*
		{
			constexpr ShareablePosition p = 10 * ShareablePosition{ 1, -2, 3 };
			std::array<int, static_cast<size_t>(p.x)> arr1; // if not constexpr, doesn't compile
			ensure_equals(arr1.size(), 10);
			std::array<int, static_cast<size_t>((p * 0.5).z)> arr2; // if not constexpr, doesn't compile
			ensure_equals(arr2.size(), 15);
		}
		// operator/
		{
			constexpr ShareablePosition p = ShareablePosition{ 1, -2, 3 } / -2;
			std::array<int, static_cast<size_t>(p.y)> arr; // if not constexpr, doesn't compile
			ensure_equals(arr.size(), 1);
		}
	}

	template<>
	template<>
	void testobject::test<5>()
	{
		set_test_name("ShareablePosition: Test of to_string()");

		const ShareablePosition p = { 1, -2, 3 , 10, 12, 13, true, false, true };
		const std::string out = p.to_string(2);
		ensure_equals(out, "x: 1.00 (+- 10.00),	*y: -2.00 (+- 12.00),	z: 3.00 (+- 13.00)");
	}

	/* ************************************************** *
	 *           TESTS OF SHAREABLEEXTRAINFO              *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<10>()
	{
		set_test_name("ShareableExtraInfo: Test of constructors");

		{
			ShareableExtraInfos sei;
			ensure(sei.empty());
			ensure_equals(sei.size(), 0);
		}
		{
			ShareableExtraInfos sei {
				{ "lil", "lol" },
				{ "lul", "lal" },
				{ "lel", "lyl" }
			};
			ensure_not(sei.empty());
			ensure_equals(sei.size(), 3);
			ensure_equals(sei["lil"], "lol");
			ensure_equals(sei["lul"], "lal");
			ensure_equals(sei["lel"], "lyl");
		}
	}

	template<>
	template<>
	void testobject::test<11>()
	{
		set_test_name("ShareableExtraInfo: Test of methods");

		ShareableExtraInfos sei;
		ensure(sei.empty());
		ensure_equals(sei.size(), 0);

		sei.addExtraInfo("key", "value");
		ensure_not(sei.empty());
		ensure_equals(sei.size(), 1);
		ensure(sei.has("key"));
		ensure_not(sei.has("lol"));
		ensure_equals(sei.at("key"), "value");
		ensure_equals(sei["key"], "value");
		sei.addExtraInfo("key", "new value");
		ensure_equals(sei["key"], "new value");

		sei.at("key") = "lol";
		ensure_equals(sei["key"], "lol");
		sei["key"] = "value";
		ensure_equals(sei.at("key"), "value");
		ensure_equals(sei["lil"], "");
		sei["new"] = "hohoho";
		ensure_equals(sei["new"], "hohoho");
		ensure_THROW(sei.at("lol"), std::out_of_range);
		ensure_equals(sei.size(), 3);

		sei.clear();
		ensure(sei.empty());
		ensure_equals(sei.size(), 0);
	}

	/* ************************************************** *
	 *             TESTS OF SHAREABLEPARAMS               *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<20>()
	{
		set_test_name("ShareableParams: Test of constructor");

		{
			const ShareableParams p;
			ensure_equals(p.precision, 6);
			ensure_equals(p.coordsys, TCoordSysFactory::ECoordSys::k3DCartesian);
			ensure(p.extraInfos.empty());
		}
		{
			const ShareableParams p = { 2, ShareableParams::ECoordSys::kGeodetic };
			ensure_equals(p.precision, 2);
			ensure_equals(p.coordsys, TCoordSysFactory::ECoordSys::kGeodetic);
			ensure(p.extraInfos.empty());
		}
	}

	template<>
	template<>
	void testobject::test<21>()
	{
		set_test_name("ShareableParams: Test of coordsys / string convertors");

		ensure_equals(ShareableParams::coordsysToString(ShareableParams::ECoordSys::k2DCartesian), "k2DCartesian");
		ensure_equals(ShareableParams::coordsysToString(ShareableParams::ECoordSys::k2DPlusH), "k2DPlusH");
		ensure_equals(ShareableParams::coordsysToString(ShareableParams::ECoordSys::k3DCartesian), "k3DCartesian");
		ensure_equals(ShareableParams::coordsysToString(ShareableParams::ECoordSys::kGeodetic), "kGeodetic");
		ensure_equals(ShareableParams::coordsysToString(ShareableParams::ECoordSys::kGeodeticSphere), "kGeodeticSphere");
		ensure_equals(ShareableParams::coordsysToString(ShareableParams::ECoordSys::unknown), "unknown");

		ensure_equals(ShareableParams::coordsysFromString("k2DCartesian"), ShareableParams::ECoordSys::k2DCartesian);
		ensure_equals(ShareableParams::coordsysFromString("k2DPlusH"), ShareableParams::ECoordSys::k2DPlusH);
		ensure_equals(ShareableParams::coordsysFromString("k3DCartesian"), ShareableParams::ECoordSys::k3DCartesian);
		ensure_equals(ShareableParams::coordsysFromString("kGeodetic"), ShareableParams::ECoordSys::kGeodetic);
		ensure_equals(ShareableParams::coordsysFromString("kGeodeticSphere"), ShareableParams::ECoordSys::kGeodeticSphere);
		ensure_equals(ShareableParams::coordsysFromString("unknown"), ShareableParams::ECoordSys::unknown);
		ensure_equals(ShareableParams::coordsysFromString("lol"), ShareableParams::ECoordSys::unknown);
		ensure_equals(ShareableParams::coordsysFromString(""), ShareableParams::ECoordSys::unknown);
	}

	/* ************************************************** *
	 *             TESTS OF SHAREABLEPOINT                *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<30>()
	{
		set_test_name("ShareablePoint: Test of constructor");

		{
			const ShareablePoint p;
			ensure(p.parent == nullptr);
			ensure_equals(p.name, "");
			ensure(p.position == ShareablePosition{ 0 });
			ensure_equals(p.inlineComment, "");
			ensure_equals(p.headerComment, "");
			ensure(p.extraInfos.empty());
			ensure(p.active);
		}
		{
			const ShareablePoint p{ "name", {1, 2, 3}, "inline", "header" };
			ensure(p.parent == nullptr);
			ensure_equals(p.name, "name");
			ensure(p.position == ShareablePosition{ 1, 2, 3 });
			ensure_equals(p.inlineComment, "inline");
			ensure_equals(p.headerComment, "header");
			ensure(p.extraInfos.empty());
			ensure(p.active);
		}
	}

	/* ************************************************** *
	 *              TESTS OF SHAREABLEFRAME               *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<40>()
	{
		set_test_name("ShareableFrame: Test of getters & setters");

		auto params = std::make_shared<ShareableParams>();
		ShareableFrame frame(params, "titre!");
		ensure_equals(&frame.getParams(), params.get());
		ensure_equals(frame.getName(), "titre!");
		ensure_equals(frame.sizeFrames(), 0);
		ensure_equals(frame.sizePoints(), 0);
		ensure(frame.getTranslation() == ShareablePosition{ 0 });
		ensure(frame.getRotation() == ShareablePosition{ 0 });
		ensure(frame.getScale() == 1);
		ensure_not(frame.isFreeScale());
		ensure(frame.getParentFrame() == nullptr);

		frame.setName("lol");
		frame.setTranslation({ 1, 2, 3 });
		frame.setRotation({ 4, 5, 6 });
		frame.setScale(-12);
		frame.isFreeScale(true);
		ensure_equals(frame.getName(), "lol");
		ensure(frame.getTranslation() == ShareablePosition{ 1, 2, 3 });
		ensure(frame.getRotation() == ShareablePosition{ 4, 5, 6 });
		ensure(frame.getScale() == -12);
		ensure(frame.isFreeScale());
	}

	template<>
	template<>
	void testobject::test<41>()
	{
		set_test_name("ShareableFrame: Test of frames management");

		auto params = std::make_shared<ShareableParams>();
		ShareableFrame frame(params, "root");

		frame.add(new ShareableFrame(params, "child1")); // append
		frame.addFrame().setName("child3"); // append
		frame.add(new ShareableFrame(params, "child0"), 0); // add as first child
		frame.addFrame(2).setName("child2"); // add at position 2
		ensure_equals(frame.sizeFrames(), 4);
		for (size_t i = 0; i < frame.sizeFrames(); i++)
		{
			ensure_equals(frame.getFrame(i).getParentFrame(), &frame);
			ensure_equals(frame.getFrame(i).getName(), "child" + std::to_string(i));
			ensure_equals(&frame.getFrame(i).getParams(), params.get());
		}

		auto& child2 = frame.getFrame(2);
		auto& grandchild = child2.addFrame(); // add a child to the second child of frame
		ensure_equals(grandchild.getParentFrame(), &child2);
		ensure_equals(frame.sizeFrames(), 4);

		auto newparams = std::make_shared<ShareableParams>();
		child2.setParams(newparams); // change params for the whole tree
		ensure_equals(&frame.getParams(), newparams.get());
		ensure_equals(&grandchild.getParams(), newparams.get());
		for (const auto& f : frame.getFrames())
			ensure_equals(&f->getParams(), newparams.get());

		auto ptr = frame.removeFrame(child2); // remove the second child (which has grandchild attached)
		ensure_equals(frame.sizeFrames(), 3);
		ensure(child2.getParentFrame() == nullptr);
		child2.setParams(params); // grandchild.params = params
		frame.add(&grandchild); // remove grandchild from child 2 and append it in frame
		ensure_equals(child2.sizeFrames(), 0);
		ensure_equals(grandchild.getParentFrame(), &frame);
		ensure_equals(&grandchild.getParams(), newparams.get());
		ensure_equals(frame.sizeFrames(), 4);

		ptr = frame.removeFrame(1);
		ensure_equals(frame.sizeFrames(), 3);
		ensure(ptr->getParentFrame() == nullptr);
		ensure_equals(ptr->getName(), "child1");
		frame.clearFrames();
		ensure_equals(frame.sizeFrames(), 0);
	}

	template<>
	template<>
	void testobject::test<42>()
	{
		set_test_name("ShareableFrame: Test of points management");

		auto params = std::make_shared<ShareableParams>();
		ShareableFrame frame(params, "root");

		frame.add(new ShareablePoint{ "child1" }); // append
		frame.addPoint().name = "child3"; // append
		frame.add(new ShareablePoint{ "child0" }, 0); // add as first child
		frame.addPoint(2).name = "child2"; // add at position 2
		ensure_equals(frame.sizePoints(), 4);
		for (size_t i = 0; i < frame.sizePoints(); i++)
		{
			ensure_equals(frame.getPoint(i).parent, &frame);
			ensure_equals(frame.getPoint(i).name, "child" + std::to_string(i));
		}

		auto& child2 = frame.getPoint(2);
		auto ptr = frame.removePoint(child2); // remove the second child (which has grandchild attached)
		ensure_equals(frame.sizePoints(), 3);
		ensure(child2.parent == nullptr);

		ptr = frame.removePoint(1);
		ensure_equals(frame.sizePoints(), 2);
		ensure(ptr->parent == nullptr);
		ensure_equals(ptr->name, "child1");
		frame.clearPoints();
		ensure_equals(frame.sizePoints(), 0);
	}

	template<>
	template<>
	void testobject::test<43>()
	{
		set_test_name("ShareableFrame: Test of getAllPoints()");

		// we create a tree like this (leaves have "*" prefix):
		// root ______ *p0
		//      \_____ *p1
		//       \____ child1 ______ *p2
		//        \___ child2 ______ *p3
		//         \__ child3 ______ *p4
		//                    \_____ *p5
		//                     \____ grandchild ______ *p6

		auto params = std::make_shared<ShareableParams>();
		ShareableFrame frame(params, "root");

		frame.addPoint().name = "p0";
		frame.addPoint().name = "p1";
		frame.addFrame().addPoint().name = "p2";
		frame.addFrame().addPoint().name = "p3";
		auto& child3 = frame.addFrame();
		child3.addPoint().name = "p4";
		child3.addPoint().name = "p5";
		child3.addFrame().addPoint().name = "p6";
		ensure_equals(frame.sizeFrames(), 3);
		ensure_equals(frame.sizePoints(), 2);
		ensure_equals(child3.sizeFrames(), 1);
		ensure_equals(child3.sizePoints(), 2);

		auto points = frame.getAllPoints();
		ensure_equals(points.size(), 7);
		for (size_t i = 0; i < points.size(); i++)
			ensure_equals(points[i]->name, "p" + std::to_string(i));
	}

	/* ************************************************** *
	 *           TESTS OF SHAREABLEPOINTSLIST             *
	 * ************************************************** */

	template<>
	template<>
	void testobject::test<50>()
	{
		set_test_name("ShareablePointsList: Test of all");

		ShareablePointsList spl("list");
		ensure_equals(spl.getTitle(), "list");
		ensure(spl.getRootFrame().getParentFrame() == nullptr);

		auto& frame = spl.getRootFrame().addFrame();
		ensure_equals(frame.getParentFrame(), &spl.getRootFrame());
		spl.setRootFrame(&frame);
		ensure(frame.getParentFrame() == nullptr);
		ensure_equals(&frame.getParams(), &spl.getParams());
		ensure_equals(&spl.getRootFrame(), &frame);
	}
}
