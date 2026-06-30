#include <CLI/CLI.hpp>
#include <array>
#include <cpp-subprocess/subprocess.hpp>
#include <cstdio>
#include <fmt/base.h>
#include <fmt/color.h>
#include <string>
#include <vector>

namespace sp = subprocess;

// FTXUI headers
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

std::string select_cpp_standard() {
	using namespace ftxui;
	auto screen = ScreenInteractive::FitComponent();
	std::vector<std::string> std_opt = {"C++11", "C++17", "C++20", "C++23"};
	int std_selected = 0;

	MenuOption option;
	option.on_enter = screen.ExitLoopClosure();

	auto menu = Menu(&std_opt, &std_selected, option);

	auto renderer = Renderer(menu, [&] {
		return vbox({
			text("Choose C++ standard:"),
			menu->Render(),
		});
	});

	screen.Loop(renderer);

	return std_opt.at(std_selected);
}

int main(int argc, char **argv) {
	std::string url{"https://github.com/royyandzakiy/cpp-project-template"};
	std::string dest_folder{"myproj"};

	// prepare CLI
	CLI::App app{"Cecep C++ Project Generator"};
	argv = app.ensure_utf8(argv);
	app.add_option("-d,--dest", dest_folder, "The folder destination");
	CLI11_PARSE(app, argc, argv);

	auto cpp_std = select_cpp_standard();

	// call git clone, change folder name
	auto p = sp::Popen({"git", "clone", url, dest_folder}, sp::output{sp::PIPE}, sp::error{sp::PIPE});

	auto rc = p.wait();

	if (rc != 0)
		fmt::println(stderr, "Git clone error code: {}", rc);

	fmt::println("std: {}", cpp_std);

	return 0;
}
