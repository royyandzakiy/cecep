#include <CLI/CLI.hpp>
#include <array>
#include <cpp-subprocess/subprocess.hpp>
#include <cstdio>
#include <fmt/base.h>
#include <fmt/color.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <map>
#include <string>
#include <vector>

namespace sp = subprocess;

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
	std::map<std::string, std::string> url_map{{"full", "https://github.com/royyandzakiy/cpp-project-template"},
											   {"min", "https://github.com/royyandzakiy/cpp-project-template-min"}};
	std::string selected_dest_folder{}, selected_template_type{};

	// run CLI
	CLI::App app{"Cecep C++ Project Generator"};
	argv = app.ensure_utf8(argv);
	app.add_option("dest,-d,--dest", selected_dest_folder, "The folder destination")
		->default_val("my_project")
		->capture_default_str();
	app.add_option("type,-t,--type", selected_template_type, "The type of template")
		->default_val("full")
		->check(CLI::IsMember({"full", "min"})) // Validate input
		->capture_default_str();

	CLI11_PARSE(app, argc, argv);

	if (!url_map.contains(selected_template_type)) {
		fmt::println(stderr, "Template '{}' not found", selected_template_type);
		return 1;
	}

	const auto &url = url_map.at(selected_template_type);
	fmt::println("Generating project from template: {} -> {}", selected_template_type, url);
	fmt::println("Destination: {}", selected_dest_folder);

	// menu: show cpp standard
	// auto cpp_std = select_cpp_standard();
	// fmt::println("std: {}", cpp_std);

	// run git clone, change folder name
	auto p = sp::Popen({"git", "clone", url, selected_dest_folder}, sp::output{sp::PIPE}, sp::error{sp::PIPE});
	auto rc = p.wait();
	if (rc != 0)
		fmt::println(stderr, "Git clone error code: {}", rc);

	return 0;
}
