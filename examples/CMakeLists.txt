add_executable(ex_copy_select copy_select/copy_select.cpp)
target_link_libraries(
  ex_copy_select
  PRIVATE fmt::fmt
          CLI11::CLI11
          ftxui::component
          cpp-subprocess::subprocess)
