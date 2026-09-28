# DEVELOPMENT

- delete .git for all types
- add github workflow to publish release version
    - add git tags
- seperate mapping into .json/.toml

---

- interactive mode to produce toml: proj name, cpp std, testing, library/exec, conan/vcpkg
- can modify toml on the fly then reflected in the app (error if part cannot be found)
- toml to provide substitutions
- draw general design: toml - cecep - templates {min,full} - ...
- connect sanitizer to debug app
- activate clang tidy
