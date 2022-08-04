###################
# applibs target 
###################
add_library(
  applibs
  subtract.c
  cell/cell.c
  grid/grid.c
  unit/unit.c
  strategies/no-duplicates/no-duplicates.c
)
target_include_directories(applibs PUBLIC
  .
  cell
  grid
  unit
  strategies/no-duplicates
)

###################
# app target 
###################
add_executable(
  app
  app.c
)
target_link_libraries(app applibs)