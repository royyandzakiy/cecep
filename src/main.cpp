#include <CLI/CLI.hpp>
#include <cpp-subprocess/subprocess.hpp>
#include <cstdio>
#include <fmt/base.h>
#include <fmt/color.h>
#include <string>

namespace sp = subprocess;

// FTXUI headers
// #include <ftxui/component/component.hpp>
// #include <ftxui/component/screen_interactive.hpp>
// #include <ftxui/dom/elements.hpp>

int main(int argc, char **argv) {
	std::string url{"https://github.com/royyandzakiy/cpp-project-template"};
	std::string dest_folder{"myproj"};

	CLI::App app{"Cecep C++ Project Generator"};
	argv = app.ensure_utf8(argv);

	app.add_option("-d,--dest", dest_folder, "The folder destination");

	CLI11_PARSE(app, argc, argv);

	// call git clone, change folder name
	auto p = sp::Popen({"git", "clone", url, dest_folder}, sp::output{sp::PIPE}, sp::error{sp::PIPE});

	auto rc = p.wait();

	if (rc != 0)
		fmt::println(stderr, "Git clone error code: {}", rc);

	return 0;
}

// namespace fs = std::filesystem;

// // Helper: interactive selection of C++ standard
// std::string select_cpp_standard() {
// 	using namespace ftxui;

// 	auto screen = ScreenInteractive::FitComponent();

// 	std::vector<std::string> standards = {"C++11", "C++14", "C++17", "C++20", "C++23", "C++26"};
// 	int selected = 0;

// 	MenuOption option;
// 	option.on_enter = screen.ExitLoopClosure();

// 	auto menu = Menu(&standards, &selected, option);

// 	auto renderer = Renderer(menu, [&] {
// 		return vbox({
// 			text("Choose a C++ standard (↑/↓, Enter to confirm):"),
// 			menu->Render(),
// 		});
// 	});

// 	screen.Loop(renderer);

// 	return standards[selected];
// }

// int main(int argc, char **argv) {
// 	CLI::App app{"Clone a git repo and copy it to a destination with a new name"};

// 	std::string repo_url = "https://github.com/royyandzakiy/cpp-project-template";
// 	std::string dest_path;
// 	bool interactive = false;

// 	app.add_option("-u,--url", repo_url, "Git repository URL (default: template repo)");
// 	app.add_flag("-i,--interactive", interactive, "Show interactive menu to select C++ standard");
// 	app.add_option("destination", dest_path, "Destination folder (new name)")->required();

// 	CLI11_PARSE(app, argc, argv);

// 	std::string selected_standard;
// 	if (interactive) {
// 		selected_standard = select_cpp_standard();
// 		std::cout << "Selected C++ standard: " << selected_standard << "\n";
// 		// (currently does nothing else with it, as requested)
// 	}

// 	// 1. Create a temporary directory for cloning
// 	fs::path clone_dir = fs::temp_directory_path() / "cpp_template_clone";
// 	if (fs::exists(clone_dir)) {
// 		fs::remove_all(clone_dir); // clean previous
// 	}
// 	fs::create_directory(clone_dir);

// 	// 2. Run git clone using cpp-subprocess
// 	std::vector<std::string> args = {"git", "clone", repo_url, clone_dir.string()};
// 	auto proc = sp::Popen(args);
// 	auto status = proc.wait();
// 	if (status != 0) {
// 		std::cerr << "git clone failed (exit code " << status << ")\n";
// 		fs::remove_all(clone_dir);
// 		return 1;
// 	}

// 	// 3. Copy the cloned repo to the destination (with new name)
// 	fs::path dest = fs::path(dest_path);
// 	try {
// 		if (fs::exists(dest)) {
// 			fs::remove_all(dest);
// 		}
// 		fs::copy(clone_dir, dest, fs::copy_options::recursive | fs::copy_options::overwrite_existing);

// 		std::cout << "Successfully copied repo to " << dest << '\n';
// 		if (interactive) {
// 			std::cout << "(Selected standard was: " << selected_standard << ")\n";
// 		}
// 	} catch (const fs::filesystem_error &e) {
// 		std::cerr << "Copy error: " << e.what() << '\n';
// 		fs::remove_all(clone_dir);
// 		return 1;
// 	}

// 	// 4. Cleanup temporary clone
// 	fs::remove_all(clone_dir);

// 	return 0;
// }
