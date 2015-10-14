#include <tut/tut.hpp>
#include <tut/tut_reporter.h>


namespace tut
{
    test_runner_singleton runner;
}

int main(int argc, char** argv)
{
    tut::reporter reporter;
    tut::runner.get().set_callback(&reporter);

	
#if 1
	try {
		if (argc == 2) {
			tut::runner.get().run_tests(argv[1]);
		}
		else {
			tut::runner.get().run_tests();
		}
	} catch (std::exception& e) {
		std::cout << "Test error: " << e.what() << std::endl;
	}
#else
	tut::runner.get().run_tests("BCAM");
#endif

    return !reporter.all_ok();
}
