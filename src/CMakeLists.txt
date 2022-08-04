###################
# applibs target 
###################
add_library(
  applibs
  subtract.c
  cell/cell.c
  grid/grid.c
)
target_include_directories(applibs PUBLIC
  .
  cell
  grid
)

###################
# app target 
###################
add_executable(
  app
  app.c
)
target_link_libraries(app applibs)